CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m4)
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_COMPILER "E:/_Tools/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_ASM_COMPILER "E:/_Tools/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_C_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g")
SET(CMAKE_ASM_FLAGS " -c -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2")
SET(CMAKE_C_COMPILER_WORKS TRUE)

SET(CMAKE_CXX_COMPILER "E:/_Tools/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-g++.exe")
SET(CMAKE_CXX_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g")
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

SET(CMAKE_OBJCOPY "E:/_Tools/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-objcopy.exe")
SET(CMAKE_SIZE "E:/_Tools/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-size.exe")

SET(CMAKE_EXE_LINKER_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rt-thread.map,-cref,-u,Reset_Handler -T ${CMAKE_SOURCE_DIR}/board/linker_scripts/link.lds")

SET(CMAKE_CXX_STANDARD 14)
PROJECT(rtthread C CXX ASM)
INCLUDE_DIRECTORIES(
	applications
	board/board_drivers
	board/board_drivers/spi_flash_w25q64
	../rt-thread/components/libc/compilers/common/include
	../rt-thread/components/libc/compilers/newlib
	../rt-thread/libcpu/arm/common
	../rt-thread/libcpu/arm/cortex-m4
	../rt-thread/components/drivers/include
	../rt-thread/components/drivers/spi
	../rt-thread/components/drivers/spi/sfud/inc
	board
	board/CubeMX_Config/Inc
	"E:/ProjectsDir/STM32F411CEU6/RTT-MiniF4/libraries/HAL_Drivers",
	"E:/ProjectsDir/STM32F411CEU6/RTT-MiniF4/libraries/HAL_Drivers/config",
	"E:/ProjectsDir/STM32F411CEU6/RTT-MiniF4/libraries/HAL_Drivers/CMSIS/Include",
	"E:/ProjectsDir/STM32F411CEU6/RTT-MiniF4/libraries/HAL_Drivers/drv_flash",
	../rt-thread/components/fal/inc
	../rt-thread/components/finsh
	hal
	.
	../rt-thread/include
	"E:/ProjectsDir/STM32F411CEU6/RTT-MiniF4/libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Inc",
	"E:/ProjectsDir/STM32F411CEU6/RTT-MiniF4/libraries/STM32F4xx_HAL/CMSIS/Device/ST/STM32F4xx/Include",
	"E:/ProjectsDir/STM32F411CEU6/RTT-MiniF4/offline_pkgs/MultiButton",
	board/ports
	../rt-thread/components/libc/posix/io/epoll
	../rt-thread/components/libc/posix/io/eventfd
	../rt-thread/components/libc/posix/io/poll
	../rt-thread/components/libc/posix/ipc
)

ADD_DEFINITIONS(
	-DRT_USING_LIBC
	-DRT_USING_NEWLIBC
	-DSTM32F411xE
	-DUSE_HAL_DRIVER
	-D_POSIX_C_SOURCE=1
	-D__RTTHREAD__
)

SET(PROJECT_SOURCES
	applications/main.c
	board/board_drivers/spi_flash_w25q64/drv_soft_spi_flash.c
	board/board_drivers/spi_flash_w25q64/drv_hw_spi_flash.c
	../rt-thread/components/libc/compilers/common/cctype.c
	../rt-thread/components/libc/compilers/common/cstdlib.c
	../rt-thread/components/libc/compilers/common/cstring.c
	../rt-thread/components/libc/compilers/common/ctime.c
	../rt-thread/components/libc/compilers/common/cunistd.c
	../rt-thread/components/libc/compilers/common/cwchar.c
	../rt-thread/components/libc/compilers/newlib/syscalls.c
	../rt-thread/libcpu/arm/common/atomic_arm.c
	../rt-thread/libcpu/arm/common/div0.c
	../rt-thread/libcpu/arm/common/showmem.c
	../rt-thread/libcpu/arm/cortex-m4/context_gcc.S
	../rt-thread/libcpu/arm/cortex-m4/cpuport.c
	../rt-thread/components/drivers/core/device.c
	../rt-thread/components/drivers/ipc/completion.c
	../rt-thread/components/drivers/ipc/dataqueue.c
	../rt-thread/components/drivers/ipc/pipe.c
	../rt-thread/components/drivers/ipc/ringblk_buf.c
	../rt-thread/components/drivers/ipc/ringbuffer.c
	../rt-thread/components/drivers/ipc/waitqueue.c
	../rt-thread/components/drivers/ipc/workqueue.c
	../rt-thread/components/drivers/misc/pin.c
	../rt-thread/components/drivers/serial/serial.c
	../rt-thread/components/drivers/spi/sfud/src/sfud.c
	../rt-thread/components/drivers/spi/sfud/src/sfud_sfdp.c
	../rt-thread/components/drivers/spi/spi_core.c
	../rt-thread/components/drivers/spi/spi_dev.c
	../rt-thread/components/drivers/spi/spi_flash_sfud.c
	../libraries/HAL_Drivers/drv_common.c
	../libraries/HAL_Drivers/drv_flash/drv_flash_f4.c
	../libraries/HAL_Drivers/drv_gpio.c
	../libraries/HAL_Drivers/drv_spi.c
	../libraries/HAL_Drivers/drv_usart.c
	../libraries/STM32F4xx_HAL/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f411xe.s
	board/CubeMX_Config/Src/stm32f4xx_hal_msp.c
	board/board.c
	../rt-thread/components/fal/src/fal_flash.c
	../rt-thread/components/fal/src/fal_partition.c
	../rt-thread/components/fal/src/fal.c
	../rt-thread/components/fal/samples/porting/fal_flash_sfud_port.c
	../rt-thread/components/fal/src/fal_rtt.c
	../rt-thread/components/finsh/shell.c
	../rt-thread/components/finsh/msh.c
	../rt-thread/components/finsh/msh_parse.c
	../rt-thread/components/finsh/cmd.c
	hal/hal_button.c
	hal/hal.c
	../rt-thread/src/clock.c
	../rt-thread/src/components.c
	../rt-thread/src/idle.c
	../rt-thread/src/ipc.c
	../rt-thread/src/irq.c
	../rt-thread/src/kservice.c
	../rt-thread/src/mem.c
	../rt-thread/src/mempool.c
	../rt-thread/src/object.c
	../rt-thread/src/scheduler_up.c
	../rt-thread/src/thread.c
	../rt-thread/src/timer.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.c
	../libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
	../libraries/STM32F4xx_HAL/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
	../offline_pkgs/MultiButton/multi_button.c
	board/ports/fal_spi_flash_sfud_port.c
)

LINK_DIRECTORIES(
)

LINK_LIBRARIES(
	c
	m
)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf)