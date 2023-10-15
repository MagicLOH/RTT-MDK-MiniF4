#include "hal_config.h"

#include "rtthread.h"

#define LOG_TAG             "hal.button"
//#define DBG_LVL DBG_INFO
#define DBG_LVL    DBG_LOG    // Debug use
#include "rtdbg.h"


#ifdef PKG_USING_MULTIBUTTON
#include "multi_button.h"

//static const uint8_t BTN0 = 0;
static uint8_t s_active_level = 0;
static struct button s_btnHandler = {0};

static uint8_t pin_level_read(void)
{
	return (uint8_t)rt_pin_read(CONFIG_BUTTON0_PIN);
}

__weak void on_button_released(void *btn)
{
	// do something...
}

__weak void on_button_pressed(void *btn)
{
	// do something...
}

__weak void on_button_double_clicked(void *btn)
{
	// do something...
}

__weak void on_button_long_press_hold(void *btn)
{
	// do something...
}

void btn_thread_entry(void *param)
{
	while (1)
	{
		button_ticks();
		rt_thread_mdelay(5);
	}
}

void hal_button_init(void)
{
	rt_thread_t tid;

	rt_pin_mode(CONFIG_BUTTON0_PIN, PIN_MODE_INPUT_PULLUP);
	button_init(&s_btnHandler, pin_level_read, s_active_level);
	button_attach(&s_btnHandler, PRESS_UP, on_button_released);
	button_attach(&s_btnHandler, PRESS_DOWN, on_button_pressed);
	button_attach(&s_btnHandler, DOUBLE_CLICK, on_button_double_clicked);
	button_attach(&s_btnHandler, LONG_PRESS_HOLD, on_button_long_press_hold);
	button_start(&s_btnHandler);

	tid = rt_thread_create("button", btn_thread_entry, NULL,
						   CONFIG_BTN_THREAD_STACK_SIZE, CONFIG_BTN_THREAD_PRIORITY, 10);
	RT_ASSERT(tid != RT_NULL);
	rt_thread_startup(tid);
}

#endif

