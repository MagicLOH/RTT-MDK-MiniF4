/*
 * @ProjectName:  MiniF411
 * @FileName:     fal_cfg.h
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-10     MagicLOH     Version 0.1
 */

#ifndef __FAL_CFG_H_
#define __FAL_CFG_H_

#include <rtthread.h>
#include <board.h>

// partition length
#define FLASH_SIZE_GRANULARITY_16K   (4 * 16 * 1024)
#define FLASH_SIZE_GRANULARITY_64K   (64 * 1024)
#define FLASH_SIZE_GRANULARITY_128K  (3 * 128 * 1024)

#define STM32_FLASH_START_ADRESS_16K  STM32_FLASH_START_ADRESS
#define STM32_FLASH_START_ADRESS_64K  (STM32_FLASH_START_ADRESS_16K + FLASH_SIZE_GRANULARITY_16K)
#define STM32_FLASH_START_ADRESS_128K (STM32_FLASH_START_ADRESS_64K + FLASH_SIZE_GRANULARITY_64K)

extern const struct fal_flash_dev stm32_onchip_flash_16k;
extern const struct fal_flash_dev stm32_onchip_flash_64k;
extern const struct fal_flash_dev stm32_onchip_flash_128k;

extern struct fal_flash_dev w25q64; // from fal_spi_flash_sfud_port.c
/* flash device table */
#if defined(BSP_USING_BOOTLOADER)
#define FAL_FLASH_DEV_TABLE     \
{                               \
    &stm32_onchip_flash_16k,    \
    &stm32_onchip_flash_64k,    \
    &stm32_onchip_flash_128k,   \
}
#else
#define FAL_FLASH_DEV_TABLE     \
{                               \
    &stm32_onchip_flash_16k,    \
    &stm32_onchip_flash_64k,    \
    &stm32_onchip_flash_128k,   \
    &w25q64,                    \
}
#endif
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#if defined(BSP_USING_BOOTLOADER)
#define FAL_PART_TABLE                                                                                               \
{                                                                                                                    \
    {FAL_PART_MAGIC_WROD, "bootloader", "onchip_flash_16k",  0 , FLASH_SIZE_GRANULARITY_16K , 0}, \
    {FAL_PART_MAGIC_WROD,      "param", "onchip_flash_64k",  0 , FLASH_SIZE_GRANULARITY_64K , 0}, \
    {FAL_PART_MAGIC_WROD,        "app", "onchip_flash_128k", 0 , FLASH_SIZE_GRANULARITY_128K, 0}, \
}
#else
#define FAL_PART_TABLE                                                                                               \
{                                                                                                                    \
    {FAL_PART_MAGIC_WROD, "bootloader", "onchip_flash_16k",  0 , FLASH_SIZE_GRANULARITY_16K , 0}, \
    {FAL_PART_MAGIC_WROD,      "param", "onchip_flash_64k",  0 , FLASH_SIZE_GRANULARITY_64K , 0}, \
    {FAL_PART_MAGIC_WROD,        "app", "onchip_flash_128k", 0 , FLASH_SIZE_GRANULARITY_128K, 0}, \
    {FAL_PART_MAGIC_WROD,  "easyflash", "W25Q64",                                    0,      512 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,   "download", "W25Q64",                           512 * 1024,     1024 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD, "wifi_image", "W25Q64",                  (512 + 1024) * 1024,      512 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,       "font", "W25Q64",            (512 + 1024 + 512) * 1024, 3 * 1024 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD, "filesystem", "W25Q64", (512 + 1024 + 512 + 3 * 1024) * 1024, 3 * 1024 * 1024, 0}, \
}

#endif

#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
