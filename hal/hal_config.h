#ifndef __HAL_CONFIG_H_
#define __HAL_CONFIG_H_

#include "drv_gpio.h"

#define CONFIG_BUTTON0_PIN				GET_PIN(A, 0)
#define CONFIG_BTN_THREAD_STACK_SIZE	(512)
#define CONFIG_BTN_THREAD_PRIORITY		(RT_MAIN_THREAD_PRIORITY)


#endif

