#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "PB_i2c.h"
#include "hw_config.h"
#include "sw_config.h"
#include "nrf_error.h"
#include <stdint.h>

void PB_i2c_reinit() {}

void PB_i2c_uninit() {}


unsigned int PB_i2c_read_qc(uint8_t pSlaveAddress, uint8_t* pWriteBuffer, uint32_t pWDataLength, uint8_t* pReadBuffer, uint32_t pRDataLength)
{
	
	srand((unsigned)time(NULL));
	int random = rand() % 2;
	printf("PB_i2c_read_qc -> random %d\n\n", random);
	if (random == 0)
		return NRF_SUCCESS;

	return NRF_ERROR_NOT_SUPPORTED;
}

unsigned int PB_i2c_write(uint8_t pSlaveAddress, uint8_t* pWriteBuffer, uint32_t pDataLength)
{
	//	mutex_lock(PB_i2c_mutex);
	//
	//	nrf_drv_twi_tx(&twi_master, pSlaveAddress, pWriteBuffer, pDataLength, false);
	//
	//	mutex_unlock(PB_i2c_mutex);

	return 0;

}
