#ifndef BLE_INIT_H_
#define BLE_INIT_H_

#include <stdint.h>

void PB_BLE_init();
//ys modified
//static void on_ble_evt();
void on_ble_evt();

typedef struct {
	uint8_t event;
	uint8_t status;
	uint8_t* msg;
}pbBLEEvt_t;

#endif /* BLE_INIT_H_ */
