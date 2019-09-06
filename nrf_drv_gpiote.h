#ifndef NRF_DRV_GPIOTE__
#define NRF_DRV_GPIOTE__

#include <stdint.h>

#include <stdbool.h>

typedef uint32_t nrf_drv_gpiote_pin_t;
bool nrf_drv_gpiote_in_is_set(nrf_drv_gpiote_pin_t pin);

#endif
