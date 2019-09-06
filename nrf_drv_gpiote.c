#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include "nrf_drv_gpiote.h"
#include "nrf_gpio.h"

bool nrf_drv_gpiote_in_is_set(nrf_drv_gpiote_pin_t pin) {
	srand((unsigned )time(NULL));
	int random = 0;

	//    ASSERT(pin < NUMBER_OF_PINS);
	assert(pin < NUMBER_OF_PINS);

	//    return nrf_gpio_pin_read(pin) ? true : false;
	random = rand() % 2;
	if (random == 0)
		return true;

	return false;
}
