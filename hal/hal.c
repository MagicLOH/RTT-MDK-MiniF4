#include "hal.h"

#define DBG_TAG			"hal"
#define DBG_LVL	DBG_LOG
#include "rtdbg.h"

void on_button_released(void *btn)
{
	RT_UNUSED(btn);

	LOG_D("btn released!");
}

void on_button_pressed(void *btn)
{
	RT_UNUSED(btn);

	LOG_D("btn press down!");
}

void on_button_double_clicked(void *btn)
{
	RT_UNUSED(btn);

	LOG_D("btn double clicked!");
}

void on_button_long_press_hold(void *btn)
{
	RT_UNUSED(btn);

	LOG_D("btn long press hold!");
}


int hal_init(void)
{
	/* button */
	hal_button_init();

	return 0;
}
INIT_APP_EXPORT(hal_init);
