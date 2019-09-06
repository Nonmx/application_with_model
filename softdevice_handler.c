#include "softdevice_handler.h"
#include "PB_ble.h"


void intern_softdevice_events_execute(void) {
	on_ble_evt();
}
