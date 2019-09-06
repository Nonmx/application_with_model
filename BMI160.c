#ifndef APPLICATION_PAARBand_EXE_PAARBand_SRC_BMI_160_C_
#define APPLICATION_PAARBand_EXE_PAARBand_SRC_BMI_160_C_

#include <stdlib.h>
#include <time.h>
#include "BMI_160.h"

uint16_t BMI_ACC_AVR_sum = 0;
uint32_t BMI_ACC_AVR_count = 0;

void Imu_readReg(uint8_t reg, uint8_t* pVal);

void Imu_readReg(uint8_t reg, uint8_t* pVal) {
	srand(time(NULL));
	uint8_t random = (uint8_t)(rand() % 2);
	*pVal = random;
}

int16_t BMI160_ACC_DATA_READ_X_AXIS(void) {
	//	uint8_t temp[2];
	//
	//	Imu_readReg(BMI160_ACCEL_X_LSB_ADDR, (uint8_t*)&temp[0]);
	//
	//	Imu_readReg(BMI160_ACCEL_X_MSB_ADDR, (uint8_t*)&temp[1]);
	//
	//	return (int16_t)((temp[1] << 8) | temp[0]);
	srand(time(NULL));
	int random = rand() % 2;

	if (random == 0)
		return 0;

	return 1;
}

void BMI160_ACC_avr_check()
{
	uint8_t temp[2];
	uint16_t temp_sum = 0;

	Imu_readReg(BMI160_ACCEL_X_LSB_ADDR, (uint8_t*)& temp[0]);
	Imu_readReg(BMI160_ACCEL_X_MSB_ADDR, (uint8_t*)& temp[1]);
	temp_sum += abs((int16_t)((temp[1] << 8) | temp[0]));

	Imu_readReg(BMI160_ACCEL_Y_LSB_ADDR, (uint8_t*)& temp[0]);
	Imu_readReg(BMI160_ACCEL_Y_MSB_ADDR, (uint8_t*)& temp[1]);
	temp_sum += abs((int16_t)((temp[1] << 8) | temp[0]));

	Imu_readReg(BMI160_ACCEL_Z_LSB_ADDR, (uint8_t*)& temp[0]);
	Imu_readReg(BMI160_ACCEL_Z_MSB_ADDR, (uint8_t*)& temp[1]);
	temp_sum += abs((int16_t)((temp[1] << 8) | temp[0]));

	temp_sum = temp_sum / 3;

	BMI_ACC_AVR_sum += temp_sum;

	BMI_ACC_AVR_count++;
}

#endif
