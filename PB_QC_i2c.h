/*
 * PB_QC_i2c.h
 *
 *  Created on: 2016. 10. 7.
 *      Author: Administrator
 */

#ifndef APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_QC_I2C_H_
#define APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_QC_I2C_H_

#include "PAARBand_Main.h"
#include <stdint.h>
#include <stdbool.h>

#define PB_QC_I2C_READ_COUNT			10
#define PB_QC_MSG_MAX_BUFFER_SIZE		512
#define PB_QC_MSG_SIZE					20
#define PB_QC_MSG_STX					0x02

#define PB_QC_CMD_TEST_START			0x01
#define PB_QC_CMD_TEST_END				0x02

#define PB_QC_CMD_TEST_BUTTON_START		0x11
#define PB_QC_CMD_TEST_BUTTON_RESULT	0x12

#define PB_QC_CMD_TEST_FALSH_START		0x11
#define PB_QC_CMD_TEST_FALSH_RESULT		0x12

#define PB_QC_CMD_TEST_LCD_START		0x21
#define PB_QC_CMD_TEST_LCD_RESULT		0x22

#define PB_QC_CMD_TEST_MOTOR_START		0x31
#define PB_QC_CMD_TEST_MOTOR_RESULT		0x32

#define PB_QC_CMD_TEST_ACC_START		0x41
#define PB_QC_CMD_TEST_ACC_RESULT		0x42

#define PB_QC_CMD_TEST_LF_START			0x51
#define PB_QC_CMD_TEST_LF_RESULT		0x52

#define PB_QC_CMD_TEST_BS_START			0x51
#define PB_QC_CMD_TEST_BS_RESULT		0x52

#define PB_QC_CMD_TEST_RF_START			0x61
#define PB_QC_CMD_TEST_RF_RESULT		0x62

#define PB_QC_CMD_TEST_ALL				0x71

 //#define PB_QC_CMD_TEST_BS_START			0x81
 //#define PB_QC_CMD_TEST_BS_RESULT		0x82
 //
 //#define PB_QC_CMD_TEST_FALSH_START		0x91
 //#define PB_QC_CMD_TEST_FALSH_RESULT		0x92

#define PB_QC_MSG_INDEX_STX				0
#define PB_QC_MSG_INDEX_LENGTH			1
#define PB_QC_MSG_INDEX_PAAR_ID			2
#define PB_QC_MSG_INDEX_SERVICE_ID		6
#define PB_QC_MSG_INDEX_CMD				7
#define PB_QC_MSG_INDEX_CHECKSUM		8
#define PB_QC_MSG_INDEX_ETX				9

#define PB_QC_MSG_INDEX_RESULT				8
#define PB_QC_MSG_INDEX_RESULT_CHECKSUM		9
#define PB_QC_MSG_INDEX_RESULT_ETX			10

#define PB_QC_MSG_INDEX_BS_MIN			8
#define PB_QC_MSG_INDEX_BS_MAX			10


#define PB_QC_RESULT_FAIL			0x00
#define PB_QC_RESULT_SUCCESS		0x01

void PB_process_qc_evt(pbMainEvt_t evt_msg);
void PB_rev_qc_msg();

void PB_send_qc_result(uint8_t test_type, bool result);

#endif /* APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_QC_I2C_H_ */
