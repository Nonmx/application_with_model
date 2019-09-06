#include <stdlib.h>
//ys modified
#include <string.h>
#include "PB_Glucose_uart.h"
#include "PB_Glucose_uartMsg.h"
#include "UI.h"

//yangsong modify
#include "PAARBand_Main.h"

uint32_t g_glucose_state;
uint8_t b_glucose_error;
uint8_t glucose_meals_state = UART_MSG_DATA_BEFORE_MEALS;
uint8_t b_Glucose_Strip_Out;
uint8_t b_Glucose_Enable;
uint32_t uart_msg_start_num;
static uint8_t Strip_in_check = 0;
uint8_t recv_msg_buffer[UART_MSG_LEN * 2] = { 0x00, };
uint8_t read_uart_msg_check = 0;
uint8_t adc_value_49[4];
uint8_t temp_value[2];
uint8_t drop_ui_check = 0;
uint8_t glucose_strip_code = STRIP_CODE_DEFAULT;

void Glucose_Meals_State_Change(uint8_t status);
void PB_Glucose_Go_State_Init();
uint32_t PB_UART_Read_Check();
uint8_t PB_Get_recv_msg(uint8_t msg_type);
static int PB_UART_ERROR_PROCESS(uint8_t error_state);
void PB_Glucose_MainLoop(uint8_t status);
int PB_Recv_msg_check(uint8_t msg_type, uint8_t value);
uint32_t PB_UART_Write(uint8_t msg_type, uint8_t value);
void PB_UART_RE_WRITE();

void PB_UART_RE_WRITE() {}
uint32_t PB_UART_Write(uint8_t msg_type, uint8_t value) { return 1; }

//ys modified
uint8_t g_glucose_result_array[5];

int PB_Recv_msg_check(uint8_t msg_type, uint8_t value) {
	return (recv_msg_buffer[uart_msg_start_num + msg_type] == value);
}

void PB_Glucose_MainLoop(uint8_t status)
{
	//uint16_t msg_data;

	// error �����̸� �ٷ� ����
	if (b_glucose_error > 0)
		return;

	switch (g_glucose_state) {
	case _STATE_GLUCOSE_NONE:
		if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_GLUCOSE_START_REQ))
		{
			PB_UART_Write(UART_MSG_TYPE_GLUCOSE_START_REQ, 0xFF);
			g_glucose_state = _STATE_GLUCOSE_INIT;
			b_Glucose_Strip_Out = 0;
			b_Glucose_Enable = 1;
			Strip_in_check = 1;
			drop_ui_check = 0;
		}
		else
		{
			// todo �߸��� ����
			uart_msg_start_num = 0;
			//				PB_UART_RE_WRITE();
		}
		break;
	case _STATE_GLUCOSE_INIT:
		g_glucose_state = _STATE_GLUCOSE_SELECT_TIME;

		// select the before meal / after meal by user's action(button)
	case _STATE_GLUCOSE_SELECT_TIME:
		if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_ACK)) {
			if (PB_Recv_msg_check(UART_MSG_POS_DATA_1, 0xFF)) {
				PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_MEALS_SELECT_EVT, &glucose_meals_state);
			}
			else {
				g_glucose_state = _STATE_GLUCOSE_CHECK_TIME;
			}
		}
		break;

	case _STATE_GLUCOSE_CHECK_TIME:
	case _STATE_GLUCOSE_CHECK_TEMPERATURE:
		PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_TEMP_CHECK_EVT, NULL);
		if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_INSERT_BLOOD_DISPLAY_REQ))
		{
			g_glucose_state = _STATE_GLUCOSE_BLOOD_DROP_READY;
			PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_WAIT_BLOOD_DROP_EVT, NULL);
			PB_UART_Write(UART_MSG_TYPE_ACK, 0xFF);
			drop_ui_check = 1;
		}
		else if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_STRIP_CODE)) {
			g_glucose_state = _STATE_GLUCOSE_CHECK_STRIP_CODE;
			PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_STRIP_CODE, NULL);

			PB_UART_Write(UART_MSG_TYPE_STRIP_CODE, glucose_strip_code);

			// OS
			task_sleep(100);
		}
		else
		{
			PB_UART_RE_WRITE();
		}
		break;
	case _STATE_GLUCOSE_CHECK_STRIP_CODE:
		if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_INSERT_BLOOD_DISPLAY_REQ))
		{
			g_glucose_state = _STATE_GLUCOSE_BLOOD_DROP_READY;
			PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_WAIT_BLOOD_DROP_EVT, NULL);
			PB_UART_Write(UART_MSG_TYPE_ACK, 0xFF);
			drop_ui_check = 1;
		}
		else
		{
			PB_UART_RE_WRITE();
		}

		break;
	case _STATE_GLUCOSE_BLOOD_DROP_READY:
	case _STATE_GLUCOSE_BLOOD_DROP:
		// todo  �� �ι��� ������ ������ �ʿ��ϸ� ����
		if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_INSERT_BLOOD_DISPLAY_REQ))
		{
			PB_UART_Write(UART_MSG_TYPE_ACK, 0xFF);
			drop_ui_check = 1;
		}
		else if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_BLOOD_INJECT_WAIT))
		{
			PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_WAIT_BLOOD_DROP_EVT, &drop_ui_check);
		}
		else if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_COUNT_DISPLAY_REQ))
		{
			g_glucose_state = _STATE_GLUCOSE_DISPLAY_RESULT_WAIT_CNT;

			if (PB_Recv_msg_check(UART_MSG_POS_DATA_1, UART_MSG_DATA_WAIT_COUNT_05))
			{
				PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_COUNT_5_EVT, NULL);
			}
		}
		else
		{
			PB_UART_RE_WRITE();
		}
		break;
		// 5���� ī���͸� �ϴ� �κ�
	case _STATE_GLUCOSE_WAIT_900MS:
	case _STATE_GLUCOSE_DISPLAY_RESULT_WAIT_CNT:
		if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_COUNT_DISPLAY_REQ))
		{
			// PB_GLUCOSE_DISPLAY_COUNT_1_EVT�� 6���� �����ϹǷ� ���� status���� +5�� �ؼ� ������.
			PB_UI_event_send(PB_GLUCOSE_EVT, (PB_Get_recv_msg(UART_MSG_POS_DATA_1) + (uint8_t)PB_GLUCOSE_DISPLAY_COUNT_1_EVT), NULL);
			if (PB_Recv_msg_check(UART_MSG_POS_DATA_1, UART_MSG_DATA_WAIT_COUNT_01))
			{
				g_glucose_state = _STATE_GLUCOSE_CALC_RESULT;
			}
		}
		else
		{
			PB_UART_RE_WRITE();
		}
		break;
		//  // ��� ǥ�� �� ����
	case _STATE_GLUCOSE_KEEP_268MV:
	case _STATE_GLUCOSE_CALC_RESULT:
	case _STATE_GLUCOSE_DISP_RESULT:
		if (PB_Recv_msg_check(UART_MSG_POS_TYPE, UART_MSG_TYPE_GLUCOSE_RESULT))
		{
			g_glucose_result_data = PB_Get_recv_msg(UART_MSG_POS_DATA_1) * 256 + PB_Get_recv_msg(UART_MSG_POS_DATA_2);
			g_glucose_result_array[0] = PB_Get_recv_msg(UART_MSG_POS_DATA_1);
			g_glucose_result_array[1] = PB_Get_recv_msg(UART_MSG_POS_DATA_2);
			PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_RESULT_EVT, g_glucose_result_array);
			// todo �����
			PB_UART_Write(UART_MSG_TYPE_ACK, 0xFF);
		}
		else
		{
			PB_UART_RE_WRITE();
		}
		break;
	}
}

uint32_t PB_UART_Read_Loop(uint8_t status, uint8_t* readData) {
	int read_complete = 0;
	uint8_t i = 0;

	if (status == PB_GLUCOSE_UART_WAKEUP_EVT_ST) {
		// I/O ������ ���� ����ó��, �ʿ� ���� �� ���Ƽ� �ϴ��� ����
	}
	else if (status == PB_GLUCOSE_UART_RX_EVT_ST) {
		memset(recv_msg_buffer, 0, UART_MSG_LEN * 2);

		while (i < 8) {
			recv_msg_buffer[i] = readData[i];
			i++;
		}

		read_complete = PB_UART_Read_Check();

		if (read_complete == 1 && read_uart_msg_check == 0) {
			PB_Glucose_MainLoop(status);
			return 1;
		}
		else if (read_complete == 2) {
			PB_UART_RE_WRITE();
			return 0;
		}
		// error state
		else if (read_complete == 3) {
			return 0;
		}
	}

	return 0;
}

void PB_Glucose_Key_Check_State(uint8_t state) {
	if (state == PB_LONG_KEY_EVT_ST) {
		if (g_glucose_state == _STATE_GLUCOSE_SELECT_TIME && b_glucose_error == 0) {
			Glucose_Meals_State_Change(state);
		}
		else {
			g_glucose_state = _STATE_GLUCOSE_NONE;
			PB_Glucose_Go_State_Init();
			PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_END_EVT, NULL);
		}
	}
	else {
		if (((g_glucose_state == _STATE_GLUCOSE_ERROR) || (g_glucose_state == _STATE_GLUCOSE_CALC_RESULT))
			&& state == PB_SHORT_KEY_EVT_ST) {
			g_glucose_state = _STATE_GLUCOSE_NONE;
			PB_Glucose_Go_State_Init();
			PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_END_EVT, NULL);
		}
		else if (g_glucose_state == _STATE_GLUCOSE_SELECT_TIME && b_glucose_error == 0) {
			Glucose_Meals_State_Change(state);
		}
	}
}

void Glucose_Meals_State_Change(uint8_t status) {
	switch (status) {
	case PB_SINGLE_TAP_EVT_ST:
	case PB_SHORT_KEY_EVT_ST:
		glucose_meals_state = (glucose_meals_state == UART_MSG_DATA_BEFORE_MEALS) ?
			UART_MSG_DATA_AFTER_MEALS : UART_MSG_DATA_BEFORE_MEALS;
		break;
	case PB_LONG_KEY_EVT_ST:
		//			PB_UART_Write(UART_MSG_TYPE_MEALS_STATE, glucose_meals_state);
		g_glucose_state = _STATE_GLUCOSE_CHECK_TIME;
		break;
	default:
		return;
	}
	PB_UI_event_send(PB_GLUCOSE_EVT, PB_GLUCOSE_DISPLAY_MEALS_SELECT_EVT, &glucose_meals_state);
}

void PB_Glucose_Go_State_Init() {
	g_glucose_state = _STATE_GLUCOSE_NONE;
	b_Glucose_Strip_Out = 0;
	b_Glucose_Enable = 0;
	b_glucose_error = 0;
	uart_msg_start_num = 0;
	Strip_in_check = 0;
	glucose_meals_state = UART_MSG_DATA_BEFORE_MEALS;

}

uint32_t PB_UART_Read_Check() {
	uint16_t temp_d = 0;

	uart_msg_start_num = 0;
	if ((recv_msg_buffer[UART_MSG_POS_START_DESC] != 0x00) | (recv_msg_buffer[UART_MSG_POS_STX] != 0x00)
		| (recv_msg_buffer[UART_MSG_POS_TYPE] != 0x00))
	{
		read_uart_msg_check = 0;
		// state�� ��� ���
		if (recv_msg_buffer[UART_MSG_POS_TYPE] >= UART_MSG_MAX_LEN || recv_msg_buffer[UART_MSG_POS_TYPE] < UART_MSG_TYPE_ACK) {
			return 2;
		}
		if (!(recv_msg_buffer[UART_MSG_POS_START_DESC] == UART_MSG_DATA_START && recv_msg_buffer[UART_MSG_POS_STX] == UART_MSG_DATA_STX)) {
			return 2;
		}

		if (recv_msg_buffer[UART_MSG_POS_TYPE] == UART_MSG_TYPE_ADC_VALUE) {
			temp_d = PB_Get_recv_msg(UART_MSG_POS_DATA_1) * 256 + PB_Get_recv_msg(UART_MSG_POS_DATA_2);
			adc_value_49[0] = (temp_d / 1000) + '0';
			temp_d = temp_d % 1000;
			adc_value_49[1] = (temp_d / 100) + '0';
			temp_d = temp_d % 100;
			adc_value_49[2] = (temp_d / 10) + '0';
			adc_value_49[3] = (temp_d % 10) + '0';
			read_uart_msg_check = 1;
		}
		else if (recv_msg_buffer[UART_MSG_POS_TYPE] == UART_MSG_TYPE_TEMP_VALUE)
		{
			temp_d = PB_Get_recv_msg(UART_MSG_POS_DATA_1);
			temp_value[0] = (temp_d / 10) + '0';
			temp_value[1] = (temp_d % 10) + '0';
			read_uart_msg_check = 1;
		}

		// Glucose Sequence ����
		if (recv_msg_buffer[UART_MSG_POS_TYPE] == UART_MSG_TYPE_GLUCOSE_START_REQ)
		{
			PB_Glucose_Go_State_Init();
		}

		// DATA 1, 2�� ����ϴ� state ( ��� )
		if (recv_msg_buffer[UART_MSG_POS_TYPE] == UART_MSG_TYPE_GLUCOSE_RESULT)
		{
			// ���� ����� �ȵ����� �� �ٽ� �����ۻ����� return
			if (recv_msg_buffer[UART_MSG_POS_DATA_1] == 0x00 && recv_msg_buffer[UART_MSG_POS_DATA_2] == 0x00)
			{
				return 2;
			}
		}

		// DATA_1�� ����ϴ� state ( ����, Count )
		else if (recv_msg_buffer[UART_MSG_POS_TYPE] == UART_MSG_TYPE_COUNT_DISPLAY_REQ)
		{
			// ���� ����� �ȵ����� �� �ٽ� �����ۻ����� return
			if (recv_msg_buffer[UART_MSG_POS_DATA_1] > 5)
			{
				return 2;
			}
		}

		else if (recv_msg_buffer[UART_MSG_POS_TYPE] == UART_MSG_TYPE_ERROR_STATE)
		{
			// �̹� ����ó���� �ؼ� ����� �����ε� �ٽ� ���� ��� ó������ ����
			if (!b_Glucose_Enable)
				return 3;

			// ���� ����� �ȵ����� �� �ٽ� �����ۻ����� return
			if (recv_msg_buffer[UART_MSG_POS_DATA_1] >= UART_MSG_DATA_ERROR_MAX)
			{
				return 2;
			}

			PB_UART_ERROR_PROCESS(recv_msg_buffer[UART_MSG_POS_DATA_1]);

			return 3;
		}

		// state�� ����ϴ� ���
		return 1;
	}
	return 3;
}

uint8_t PB_Get_recv_msg(uint8_t msg_type) {
	return recv_msg_buffer[msg_type + uart_msg_start_num];
}

static int PB_UART_ERROR_PROCESS(uint8_t error_state) {
	// msg  ߸ͼ  ؾߵ
	if (error_state == UART_MSG_DATA_ERROR_MSG_ERROR) {
		//		PB_UART_Write( UART_MSG_TYPE_ASK_RE_WRITE, 0xFF );

		return 1;
	}

	PB_UI_event_send(PB_GLUCOSE_EVT, (uint8_t)(error_state + PB_GLUCOSE_DISPLAY_ERROR_START), NULL);
	g_glucose_state = _STATE_GLUCOSE_ERROR;
	b_glucose_error = error_state;
	b_Glucose_Strip_Out = 1;

	return 1;
}
