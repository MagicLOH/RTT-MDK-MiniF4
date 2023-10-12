#include <rtthread.h>

#include "spi_flash.h"
#include "spi_flash_sfud.h"
#include "drv_spi.h"

#if defined(BSP_USING_SPI_FLASH)

#define CS_PIN GET_PIN(A, 4)

int rt_hw_spi_flash_init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
//    rt_hw_spi_device_attach("spi1", "spi10", GPIOA, GPIO_PIN_4);
	rt_hw_spi_device_attach("spi1", "spi10", CS_PIN);

    // probe spi device and gift a name to it (eg: W25Q64)
    if (RT_NULL == rt_sfud_flash_probe("W25Q64", "spi10"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_flash_init);


#include <fal.h>
#define BUF_SIZE 128
static int SPI_Flash_fal_test(int argc, char *argv[])
{
    if (argc != 2)
    {
        LOG_W("Usage: %s <partiton_name>", argv[0]);
        return RT_ERROR;
    }

    int ret;
    int i, j, len;
    uint8_t buf[BUF_SIZE];
    const struct fal_flash_dev *flash_dev = RT_NULL;
    const struct fal_partition *partition = RT_NULL;

    if (!argv[1])
    {
        LOG_E("Input param partition name is null!");
        return -1;
    }

    partition = fal_partition_find(argv[1]);
    if (partition == RT_NULL)
    {
        LOG_E("Find partition (%s) failed!", argv[1]);
        ret = -1;
        return ret;
    }

    flash_dev = fal_flash_device_find(partition->flash_name);
    if (flash_dev == RT_NULL)
    {
        LOG_E("Find flash device (%s) failed!", partition->flash_name);
        ret = -1;
        return ret;
    }

    LOG_I("Flash device : %s   "
          "Flash size : %dK   "
          "Partition : %s   "
          "Partition size: %dK",
          partition->flash_name,
          flash_dev->len / 1024,
          partition->name,
          partition->len / 1024);

    /* 擦除 `partition` 分区上的全部数据 */
    ret = fal_partition_erase_all(partition);
    if (ret < 0)
    {
        LOG_E("Partition (%s) erase failed!", partition->name);
        ret = -1;
        return ret;
    }
    LOG_I("Erase (%s) partition finish!", argv[1]);

    /* 循环读取整个分区的数据，并对内容进行检验 */
    for (i = 0; i < partition->len;)
    {
        rt_memset(buf, 0x00, BUF_SIZE);
        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        /* 从 Flash 读取 len 长度的数据到 buf 缓冲区 */
        ret = fal_partition_read(partition, i, buf, len);
        if (ret < 0)
        {
            LOG_E("Partition (%s) read failed!", partition->name);
            ret = -1;
            return ret;
        }
        for (j = 0; j < len; j++)
        {
            /* 校验数据内容是否为 0xFF */
            if (buf[j] != 0xFF)
            {
                LOG_E("The erase operation did not really succeed!");
                ret = -1;
                return ret;
            }
        }
        i += len;
    }

    /* 把 0 写入指定分区 */
    for (i = 0; i < partition->len;)
    {
        /* 设置写入的数据 0x00 */
        rt_memset(buf, 0x00, BUF_SIZE);
        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        /* 写入数据 */
        ret = fal_partition_write(partition, i, buf, len);
        if (ret < 0)
        {
            LOG_E("Partition (%s) write failed!", partition->name);
            ret = -1;
            return ret;
        }
        i += len;
    }
    LOG_I("Write (%s) partition finish! Write size %d(%dK).", argv[1], i, i / 1024);

    /* 从指定的分区读取数据并校验数据 */
    for (i = 0; i < partition->len;)
    {
        /* 清空读缓冲区，以 0xFF 填充 */
        rt_memset(buf, 0xFF, BUF_SIZE);
        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        /* 读取数据到 buf 缓冲区 */
        ret = fal_partition_read(partition, i, buf, len);
        if (ret < 0)
        {
            LOG_E("Partition (%s) read failed!", partition->name);
            ret = -1;
            return ret;
        }
        for (j = 0; j < len; j++)
        {
            /* 校验读取的数据是否为步骤 3 中写入的数据 0x00 */
            if (buf[j] != 0x00)
            {
                LOG_E("The write operation did not really succeed!");
                ret = -1;
                return ret;
            }
        }
        i += len;
    }

    ret = 0;
    return ret;
}
MSH_CMD_EXPORT_ALIAS(SPI_Flash_fal_test, spi_flash_test, test spi flash read write function);
#endif
