/*
 * PB_i2c_ext_rtc_spo2.h
 *
 *  Created on: 2016. 5. 26.
 *      Author: Administrator
 */

#include <stdint.h>
#ifndef APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_I2C_H_
#define APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_I2C_H_


void PB_i2c_init();
void PB_i2c_reinit();
void PB_i2c_uninit();
unsigned int PB_i2c_read(uint8_t pSlaveAddress, uint8_t* pWriteBuffer, uint32_t pWDataLength, uint8_t* pReadBuffer, uint32_t pRDataLength);
unsigned int PB_i2c_write(uint8_t pSlaveAddress, uint8_t* pWriteBuffer, uint32_t pDataLength);

unsigned int PB_i2c_read_qc(uint8_t pSlaveAddress, uint8_t* pWriteBuffer, uint32_t pWDataLength, uint8_t* pReadBuffer, uint32_t pRDataLength);
#endif /* APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_I2C_H_ */
