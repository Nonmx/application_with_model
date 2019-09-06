#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "PB_QC_i2c.h"
//#include "PAARBand_Main.h"
//#include "UI.h"
#include "hw_config.h"
#include "sw_config.h"
#include "PB_i2c.h"
#include "nrf_drv_gpiote.h"

void PB_parse_qc_msg(uint8_t* read_buffer);
bool result;

void PB_send_qc_result(uint8_t test_type, bool result)
{
	PB_i2c_reinit();

	uint8_t temp_w_buffer[15];

	switch (test_type)
	{
	case PB_QC_TEST_START_BUTTON_ST:
		break;
	case PB_QC_TEST_START_LCD_ST:
	{
		if (result == true)
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_LCD_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_SUCCESS;

			//ys modified
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);

			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);


			if (get_qc_test_all_enable() == true)
			{
				PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_MOT_ST, NULL);
			}
		}
		else
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_LCD_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_FAIL;
			//정의 없다.
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			//
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			set_qc_test_all_enable(false);
		}
	}
	break;
	case PB_QC_TEST_START_MOT_ST:
	{
		if (result == true)
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_MOTOR_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_SUCCESS;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			if (get_qc_test_all_enable() == true)
			{
				PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_FLASH_ST, NULL);
			}

		}
		else
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_MOTOR_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_FAIL;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			set_qc_test_all_enable(false);

		}
	}
	break;
	case PB_QC_TEST_START_FLASH_ST:
	{
		if (result == true)
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_FALSH_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_SUCCESS;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			if (get_qc_test_all_enable() == true)
			{
				PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_RF_ST, NULL);
			}
		}
		else
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_FALSH_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_FAIL;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			set_qc_test_all_enable(false);

		}
	}
	break;
	case PB_QC_TEST_START_RF_ST:
	{
		if (result == true)
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_RF_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_SUCCESS;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			if (get_qc_test_all_enable() == true)
			{
				PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_ACC_ST, NULL);
			}
		}
		else
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_RF_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_FAIL;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			set_qc_test_all_enable(false);

		}
	}
	break;
	case PB_QC_TEST_START_ACC_ST:
	{
		if (result == true)
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_ACC_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_SUCCESS;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			if (get_qc_test_all_enable() == true)
			{
				PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_BS_ST, NULL);
			}
		}
		else
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_ACC_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_FAIL;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			set_qc_test_all_enable(false);
		}
	}
	break;
	case PB_QC_TEST_START_BS_ST:
	{
		if (result == true)
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_BS_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_SUCCESS;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			set_qc_test_all_enable(false);
		}
		else
		{
			//send QC result
			temp_w_buffer[PB_QC_MSG_INDEX_STX] = 0x02;
			temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] = 0x07;
			memset(&temp_w_buffer[PB_QC_MSG_INDEX_PAAR_ID], 0, 4);
			temp_w_buffer[PB_QC_MSG_INDEX_SERVICE_ID] = 0xF3;
			temp_w_buffer[PB_QC_MSG_INDEX_CMD] = PB_QC_CMD_TEST_BS_RESULT;
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT] = PB_QC_RESULT_FAIL;
			//temp_w_buffer[PB_QC_MSG_INDEX_RESULT_CHECKSUM] = PB_QC_cal_checksum(&temp_w_buffer[PB_QC_MSG_INDEX_LENGTH], temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 1);
			temp_w_buffer[PB_QC_MSG_INDEX_RESULT_ETX] = 0x03;
			PB_i2c_write(0x13, temp_w_buffer, temp_w_buffer[PB_QC_MSG_INDEX_LENGTH] + 4);

			set_qc_test_all_enable(false);
		}
	}
	break;
	}

	PB_i2c_uninit();
}

void PB_process_qc_evt(pbMainEvt_t evt_msg)
{

	switch (evt_msg.status)
	{
	case PB_QC_TEST_START_LCD_ST:
	case PB_QC_TEST_START_MOT_ST:
	case PB_QC_TEST_START_ACC_ST:
	case PB_QC_TEST_START_RF_ST:
	case PB_QC_TEST_START_ALL_ST:
	case PB_QC_TEST_START_BS_ST:
	case PB_QC_TEST_START_FLASH_ST:
	case PB_QC_TEST_END_ST:
		PB_UI_event_send(evt_msg.event, evt_msg.status, evt_msg.msg);

		break;
	case PB_QC_TEST_START_ST:
		break;
	case PB_QC_TEST_START_BUTTON_ST:
		break;
	case PB_QC_TEST_START_LF_ST:
		break;
	}
}

void PB_parse_qc_msg(uint8_t* read_buffer)
{
	uint16_t cur_read_cnt = 0;

	//check STX
	while (cur_read_cnt <= PB_QC_MSG_MAX_BUFFER_SIZE)
	{
		if (read_buffer[cur_read_cnt] == PB_QC_MSG_STX)
			break;

		cur_read_cnt++;
	}
	if (PB_QC_MSG_MAX_BUFFER_SIZE - cur_read_cnt < PB_QC_MSG_SIZE)
		return;

	uint8_t packet_len = 0;

	//check length
	if (read_buffer[cur_read_cnt + PB_QC_MSG_INDEX_LENGTH] >= PB_QC_MSG_SIZE)
		return;

	switch (read_buffer[cur_read_cnt + PB_QC_MSG_INDEX_CMD])
	{
	case PB_QC_CMD_TEST_START:
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);
//		PB_QC_conf_set(false, read_buffer[cur_read_cnt+PB_QC_MSG_INDEX_PAAR_ID], read_buffer[cur_read_cnt+PB_QC_MSG_INDEX_PAAR_ID+1]
//								 , read_buffer[cur_read_cnt+PB_QC_MSG_INDEX_PAAR_ID+2], read_buffer[cur_read_cnt+PB_QC_MSG_INDEX_PAAR_ID+3], true, false);
		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_ST, NULL);
		break;
	case PB_QC_CMD_TEST_END:
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);

//		set_qc_test_all_enable(false);

		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_END_ST, NULL);
		break;
		//	case PB_QC_CMD_TEST_BUTTON_START :
		//		//send ACK
		//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);
		//		break;
	case PB_QC_CMD_TEST_LCD_START:
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);
		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_LCD_ST, NULL);
		break;
	case PB_QC_CMD_TEST_MOTOR_START:
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);
		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_MOT_ST, NULL);
		break;
	case PB_QC_CMD_TEST_FALSH_START:
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);
		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_FLASH_ST, NULL);
		break;
	case PB_QC_CMD_TEST_RF_START:
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);
		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_RF_ST, NULL);
		break;
	case PB_QC_CMD_TEST_ACC_START:
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);
		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_ACC_ST, NULL);
		break;
	case PB_QC_CMD_TEST_BS_START:
	{
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);
//		uint16_t min, max;
//		memcpy(&min, &read_buffer[cur_read_cnt+PB_QC_MSG_INDEX_BS_MIN], 2);
//		memcpy(&max, &read_buffer[cur_read_cnt+PB_QC_MSG_INDEX_BS_MAX], 2);
//		set_qc_test_bs_enable(true, min, max);
		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_BS_ST, NULL);
	}
	break;
	case PB_QC_CMD_TEST_ALL:
	{
		//send ACK
//		PB_send_qc_ack(&read_buffer[cur_read_cnt]);

//		set_qc_test_all_enable(true);

//		uint16_t min, max;
//		memcpy(&min, &read_buffer[cur_read_cnt+PB_QC_MSG_INDEX_BS_MIN], 2);
//		memcpy(&max, &read_buffer[cur_read_cnt+PB_QC_MSG_INDEX_BS_MAX], 2);
//		set_qc_test_bs_enable(true, min, max);

		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_START_LCD_ST, NULL);
	}
	break;
	}
}


void PB_rev_qc_msg()
{
	uint8_t* temp_buffer = NULL;
	temp_buffer = malloc(sizeof(uint8_t) * 50);
	uint32_t err;

	memset(temp_buffer, 0, sizeof(uint8_t) * 50);
	PB_i2c_reinit();

	uint16_t cur_qc_read_cnt = 0;

	err = PB_i2c_read_qc(0x13, NULL, 0, &temp_buffer[cur_qc_read_cnt], PB_QC_I2C_READ_COUNT);
	cur_qc_read_cnt += PB_QC_I2C_READ_COUNT;

	while (nrf_drv_gpiote_in_is_set(BOARD_PIN_EXT_INT) == false)
	{
		err = PB_i2c_read_qc(0x13, NULL, 0, &temp_buffer[cur_qc_read_cnt], PB_QC_I2C_READ_COUNT);
		cur_qc_read_cnt += PB_QC_I2C_READ_COUNT;

		// OS
		task_sleep(100);

		if (cur_qc_read_cnt > 40)
			break;
	}

	PB_parse_qc_msg(temp_buffer);

	free(temp_buffer);

	PB_i2c_uninit();
}