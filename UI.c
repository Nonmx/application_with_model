#include <stdbool.h>
#include "absconfig.h"
#include "UI.h"
#include "PAARBand_Main.h"
#include "PB_Glucose_uartMsg.h"
#include "PB_Glucose_uart.h"
#include "sw_config.h"
#include "core_cm4.h"
//#include "os.h"
#include <stdlib.h>
#include "BMI_160.h"

//ys modified
//#include "BMI_160.c"

static void PB_UI_default_draw();
bool PB_is_qc_complete();
static void processing_keychange_evt(pbUIEvt_t UIevt_Msg);
static void processing_batt_evt(pbUIEvt_t UIevt_Msg);
static void processing_lcd_timeout_evt();
static void PB_AlarmControl();
static void processing_glucose_uart_evt(pbUIEvt_t UIevt_Msg);
static void processing_qc_msg_evt(pbUIEvt_t UIevt_Msg);

static msgq_pt uiMsgq;
static pbQC_t PB_current_qc_conf;
uint32_t PB_UI_State = UI_STATE_CLOCK;
uint8_t curAlarmIdx;

//yangsong modify
int r;

uint32_t PB_Get_UI_state() {
	return PB_UI_State;
}

// UI Timeout Handler
// period: every 1 minute
void UI_timeout_handler() {
	int32_t err;
	err = PB_UI_event_send(PB_LCD_TIMEOUT_EVT, 0, NULL);

	//	if(err == UBIK_ERR__OVERFLOWED)	{
	//		restart_lcd_timeout(1);
	//	}
}

int8_t PB_UI_event_send(uint8_t UI_evt, uint8_t UI_evt_state, uint8_t* msg) {
	pbUIEvt_t temp_msg;
	temp_msg.event = UI_evt;
	temp_msg.status = UI_evt_state;
	temp_msg.msg = msg;

	int32_t err;
	// OS
	err = msgq_send(uiMsgq, (unsigned char*)& temp_msg);

	return err;
}

void PB_UI_init() {
	int r;

	//msgq_create : UI msgq
	// OS
	r = msgq_create(&uiMsgq, sizeof(pbUIEvt_t), UI_MAX_MSGQ_COUNT);
	if (0 != r) {
#if DEBUG
		printf("fail at msgq_create\n");
#endif
	}

	r = task_create(5); //PB_UI_Task
	if (0 != r) {
#if DEBUG
		printf("fail at task_create\n");
#endif
	}
}

#define JUMP_PB_UI_task(){\
	switch (current_pc[PB_UI_Task])\
	{\
		case 0:\
			goto L_PB_UI_Task_0;break;\
		case 1:\
			goto L_PB_UI_Task_1;break;\
		case 2:\
			goto L_PB_UI_Task_2;break;\
		case 3:\
			goto L_PB_UI_Task_3;break;\
		case 4:\
			goto L_PB_UI_Task_4;break;\
		case 5:\
			goto L_PB_UI_Task_5;break;\
		case 6:\
			goto L_PB_UI_Task_6;break;\
		case 7:\
			goto L_PB_UI_Task_7;break;\
		case 8:\
			goto L_PB_UI_Task_8;break;\
		case 9:\
			goto L_PB_UI_Task_9;break;\
		case 10:\
			goto L_PB_UI_Task_10;break;\
	}\
}

//ys modified
int r;
extern int8_t PB_UI_event_send(uint8_t UI_evt, uint8_t UI_evt_state, uint8_t* msg);
//static void TASK(5) { // PB_UI_Task
void PB_UI()
{
	JUMP_PB_UI_task();
L_PB_UI_Task_0:
	//int r = 0;

	while (get_main_task_init_ready() == 0) {
		// OS
		current_pc[5] = 1;
		task_sleep(100);
		scheduler();
		return;

	L_PB_UI_Task_1:
		;
	}
	// OS
L_PB_UI_Task_2:
	current_pc[5] = 3;
	task_sleep(100);
	scheduler();
	return;

L_PB_UI_Task_3:
	PB_UI_default_draw();

	pbUIEvt_t UI_msgRxBuffer;

	for (;;) {
		// OS
		current_pc[5] = 4;
		r = msgq_receive(uiMsgq, (unsigned char*)& UI_msgRxBuffer);
		scheduler();
		return;
	L_PB_UI_Task_4:

		if (0 != r) {
#if DEBUG
			printf("fail at msgq_receive\n");
#endif
		}
		else {
			switch (UI_msgRxBuffer.event) {
			case PB_KEY_CHANGE_EVT:
				processing_keychange_evt(UI_msgRxBuffer);//msg send
				scheduler();
				current_pc[5] = 5;
				return;
			L_PB_UI_Task_5:

				break;
			case PB_BATT_EVT:
				//					processing_batt_evt(UI_msgRxBuffer);
				break;
			case PB_LCD_TIMEOUT_EVT:
				//					processing_lcd_timeout_evt();
				break;
			case PB_TIME_EVT:
				PB_AlarmControl(); //msg send
				scheduler();
				current_pc[5] = 6;
				return;

			L_PB_UI_Task_6:

				if (PB_UI_State == UI_STATE_CLOCK) {
					//						processing_update_screen();
				}

				//PB_UI_event_send(PB_UI_REFRESH_EVT, NULL, NULL);
				PB_UI_event_send(PB_UI_REFRESH_EVT, 0, 0);
				scheduler();
				current_pc[5] = 7;
				return;

			L_PB_UI_Task_7:

				break;
			case PB_BLE_EVT:
				//					processing_ui_ble_msg_evt(UI_msgRxBuffer);

				break;
			case PB_AFE_EVT:
				//					processing_ui_afe_evt(UI_msgRxBuffer);

				break;
			case PB_POPUP_EVT:
				//					processing_popup_evt(UI_msgRxBuffer);

				break;
			case PB_ALARM_EVT:
				//					processing_alarm_evt(UI_msgRxBuffer);

				break;
			case PB_LF_EVT:
				//					processing_lf_evt(UI_msgRxBuffer);

				break;
			case PB_ACTIVITY_EVT:
				//					processing_activity_msg(UI_msgRxBuffer);

				break;
			case PB_GLUCOSE_EVT:
				processing_glucose_uart_evt(UI_msgRxBuffer);//msg send
				scheduler();
				current_pc[5] = 8;
				return;

			L_PB_UI_Task_8:
				break;
			case PB_PNIP_EVT:
				//					processing_pnip_session_evt(UI_msgRxBuffer);

				break;
			case BIO_INT_EVT:
				break;
			case PB_PAAR_TAG_EVT:
				//					processing_paartag_evt(UI_msgRxBuffer);

				break;
			case PB_PEDOMETER_EVT:
				//					processing_pedometer_evt(UI_msgRxBuffer);

				break;
			case PB_SMART_CAR_TALK_EVT:
				//					processing_smart_ct_evt(UI_msgRxBuffer);

				break;
			case PB_ACC_PERIOD_EVT:
				//					processing_acc_period_evt(UI_msgRxBuffer);

				break;
			case PB_AFE_PERIOD_EVT:
				//					processing_afe_period_evt(UI_msgRxBuffer);

				break;
			case PB_TEST_MSG_EVT:
				//					processing_test_msg_evt(UI_msgRxBuffer);

				break;
			case PB_UI_REFRESH_EVT:
				if (PB_UI_State == UI_STATE_OFF) {
					//						Board_oledOff();
				}

				break;
			case PB_QC_EVT:
				processing_qc_msg_evt(UI_msgRxBuffer); //msg send or sleep
				scheduler();
				current_pc[5] = 9;
				return;

			L_PB_UI_Task_9:
				break;
			}

			if (UI_msgRxBuffer.msg != NULL) {
				free(UI_msgRxBuffer.msg);
			}
		}
	L_PB_UI_Task_10:
		;
	}

	current_pc[PB_UI_Task] = 0;
	TerminateTask();
	scheduler();
	return;
}

static void PB_UI_default_draw() {}

static void processing_keychange_evt(pbUIEvt_t UIevt_Msg) {
	switch (PB_UI_State) {
	case UI_STATE_OFF:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					Board_oledOn();
			//					PB_UI_State = UI_STATE_CLOCK;
			//					processing_update_screen();

			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_CLOCK:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_PEDOMETER;
			//					processing_update_screen();
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_PEDOMETER:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_AFE;
			//					processing_update_screen();
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_PEDOMETER_TEST:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_ACC_TEST;
			//					processing_update_screen();
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_ACC_TEST:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_AFE;
			//					processing_update_screen();
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_AFE:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					set_ui_afe_enable(false);
			//					AFE4404_FUNC_ENABLE(false);
			//					PB_UI_State = UI_STATE_SCHEDULE_VIEWER;
			//					processing_update_screen();
			break;

		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_AFE_TEST:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					set_ui_afe_enable(false);
			//					AFE4404_FUNC_ENABLE(false);
			//					PB_UI_State = UI_STATE_SCHEDULE_VIEWER;
			//					processing_update_screen();
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_POPUP:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_CLOCK;
			//					processing_update_screen();
			break;
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_POPUP_GLU:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_SCHEDULE_VIEWER:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_ACTIVITY_COUNT;
			//					processing_update_screen();
			break;
		case PB_LONG_KEY_EVT_ST:
			//					schedule_view_count = 0;
			//					if(PB_GetSchedule_avail() == 0) {
			//						PB_UI_State = UI_STATE_CLOCK;
			//					}
			//					else {
			//						PB_UI_State = UI_STATE_SCHEDULE_VIEWER_SUB;
			//					}
			//
			//					processing_update_screen();
			break;
		}
		break;
	case UI_STATE_SCHEDULE_VIEWER_SUB:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					schedule_view_count++;
			//
			//					if(schedule_view_count == 10) {
			//						schedule_view_count = 0;
			//					}
			//
			//					processing_update_screen();

			break;
		case PB_LONG_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_CLOCK;
			//
			//					processing_update_screen();
			break;
		}
		break;
	case UI_STATE_NOTIFICATION_VIEWER:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_NOTIFICATION_VIEWER_SUB:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_ACTIVITY_COUNT:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_SETTING_VIEWER;
			//					processing_update_screen();
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_SETTING_VIEWER:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_CLOCK;
			//					processing_update_screen();

			break;
		case PB_LONG_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_SETTING_VIEWER_DETAIL;
			//					PB_Setting_viewer_detail_toggle_num = 0;
			//					processing_update_screen();

			break;
		}
		break;
	case UI_STATE_SETTING_VIEWER_DETAIL:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//				PB_UI_State = UI_STATE_SETTING_VIEWER_DETAIL;
			//				processing_update_screen();

			break;
		case PB_LONG_KEY_EVT_ST:
			//				if(PB_Setting_viewer_detail_toggle_num == 1) {
			//					PB_UI_State = UI_STATE_SETTING_DEVICE_ID;
			//					processing_update_screen();
			//				}
			//				else if(PB_Setting_viewer_detail_toggle_num == 2) {
			//					PB_UI_State = UI_STATE_SETTING_FIRMWARE_VERSION;
			//					processing_update_screen();
			//				}
			//				else {
			//					PB_UI_State = UI_STATE_SETTING_GLU_STRIP_CODE;
			//					glucose_strip_code_select = 0 ;
			//					processing_update_screen();
			//				}
			break;
		}
		break;
	case UI_STATE_SETTING_DEVICE_ID:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_CLOCK;
			//					processing_update_screen();

			break;
		case PB_LONG_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_CLOCK;
			//					processing_update_screen();

			break;
		}
		break;
	case UI_STATE_SETTING_FIRMWARE_VERSION:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_CLOCK;
			//					processing_update_screen();

			break;
		case PB_LONG_KEY_EVT_ST:
			//					PB_UI_State = UI_STATE_CLOCK;
			//					processing_update_screen();

			break;
		}
		break;
	case UI_STATE_SETTING_GLU_STRIP_CODE:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
		case PB_SHORT_KEY_EVT_ST:
			//					if( glucose_strip_code_select == 0 ) {
			//						glucose_strip_code++;
			//
			//						if (glucose_strip_code > STRIP_CODE_MAX)
			//							glucose_strip_code = 1;
			//					}
			//					else {
			//						glucose_strip_code_select = 0 ;
			//						PB_UI_State = UI_STATE_CLOCK;
			//					}
			//					processing_update_screen();

			break;
		case PB_LONG_KEY_EVT_ST:
			//					if( glucose_strip_code_select == 0 ) {
			//						glucose_strip_code_select = 1 ;
			//					}
			//					else {
			//						glucose_strip_code_select = 0 ;
			//						PB_UI_State = UI_STATE_CLOCK;
			//					}
			//
			//					processing_update_screen();

			break;
		}
		break;
	case UI_STATE_TEST:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			break;
		case PB_LONG_KEY_EVT_ST:
			break;
		}
		break;
	case UI_STATE_QC_LCD_TEST:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_SUCCESS_LCD_ST, NULL);
			//					processing_qc_default_view();

			break;
		case PB_LONG_KEY_EVT_ST:
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_FAIL_LCD_ST, NULL);
			//					processing_qc_default_view();

			break;
		}
		break;
	case UI_STATE_QC_MOT_TEST:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_SUCCESS_MOT_ST, NULL);
			//					processing_qc_default_view();
			break;
		case PB_LONG_KEY_EVT_ST:
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_FAIL_MOT_ST, NULL);
			//					processing_qc_default_view();
			break;
		}
		break;
	case UI_STATE_QC_ACC_TEST:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			//					processing_qc_default_view();
			break;
		case PB_LONG_KEY_EVT_ST:
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_FAIL_ACC_ST, NULL);
			//					processing_qc_default_view();
			break;
		}
		break;
	case UI_STATE_QC_BS_TEST:
		switch (UIevt_Msg.status) {
		case PB_SINGLE_TAP_EVT_ST:
			break;
		case PB_SHORT_KEY_EVT_ST:
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_SUCCESS_BS_ST, NULL);
			//					processing_qc_default_view();

			break;
		case PB_LONG_KEY_EVT_ST:
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_FAIL_BS_ST, NULL);
			//					processing_qc_default_view();

			break;
		}
		break;
	}
}

static void processing_batt_evt(pbUIEvt_t UIevt_Msg) {
	if (PB_UI_State == UI_STATE_OFF) {
		//		Board_oledOn();
		//
		//		PB_UI_State = UI_STATE_CLOCK;
		//
		//		processing_update_screen();
	}
	else if (PB_UI_State == UI_STATE_CLOCK) {
		//		PB_UI_State = UI_STATE_CLOCK;
		//
		//		processing_update_screen();
	}
}

static void processing_lcd_timeout_evt() {
	switch (PB_UI_State) {
	case UI_STATE_OFF:
		break;
	case UI_STATE_CLOCK:
	case UI_STATE_PEDOMETER:
	case UI_STATE_PEDOMETER_TEST:
	case UI_STATE_POPUP:
	case UI_STATE_POPUP_GLU:
	case UI_STATE_SCHEDULE_VIEWER:
	case UI_STATE_SCHEDULE_VIEWER_SUB:
	case UI_STATE_NOTIFICATION_VIEWER:
	case UI_STATE_NOTIFICATION_VIEWER_SUB:
	case UI_STATE_ACTIVITY_COUNT:
	case UI_STATE_SETTING_VIEWER:
	case UI_STATE_SETTING_VIEWER_DETAIL:
		//		PB_UI_State = UI_STATE_OFF;
		//
		//		Board_clearLCD();
		//
		//		Board_oledOff();

		break;
	case UI_STATE_SETTING_GLU_STRIP_CODE:
		//		if( glucose_strip_code_select == 0 ) {
		//			glucose_strip_code_select = 1 ;
		//			processing_update_screen();
		//		}
		//		else {
		//			PB_UI_State = UI_STATE_OFF;
		//			Board_clearLCD();
		//			Board_oledOff();
		//		}
		break;
	case UI_STATE_AFE:
		//			set_ui_afe_enable(false);
		//			AFE4404_FUNC_ENABLE(false);
		//			PB_UI_State = UI_STATE_OFF;
		//			Board_clearLCD();
		//			Board_oledOff();

		break;
	}
}

static void PB_AlarmControl() {
	uint8_t i;
	//uint8_t dow;

	pbSchedule_t temp_schedule_data;
	uint8_t boundary_temp[2];

	//tm cur_time;
	//tm cur_time_pre;
	//ys modified
	//Clock_Get_Time(&cur_time);

	//	//save Pedometer
	//	if ( (cur_time.tm_hour == 23)&&(cur_time.tm_min == 50))
	//	{
	//		PB_step_count_end();
	//	}
	//	else if ( (cur_time.tm_hour == 00)&&(cur_time.tm_min == 50))
	//	{
	//		PB_step_count_start();
	//	}

		//This loop is very dirty and simple, but this loop checks schedule and alarming.
	for (i = 0; i < 10; i++) {
		//		PB_Schedule_flash_read(&temp_schedule_data, boundary_temp, i);
		bool read_result = PB_Schedule_flash_read(&temp_schedule_data, boundary_temp, i);

		// written by yshin
		if (!read_result) {
			curAlarmIdx = i;
			PB_Main_event_send(PB_ALARM_EVT, PB_ALARM_CHECK_DISPLAY_ST, NULL);
		}

		//		if(boundary_temp[0] == 0xB5 && boundary_temp[1] == 0xA0) {
		//			if ( (temp_schedule_data.seq != 0x00) && (temp_schedule_data.seq != 0xFF) ) {
		//				if ((temp_schedule_data.weeklyRepeat & cur_time.tm_wday) != 0x00) {
		//					if ((temp_schedule_data.hour == cur_time.tm_hour) && (temp_schedule_data.min == cur_time.tm_min)
		//							&& ((temp_schedule_data.alarmFlags & 0x04) == 0x00)) {
		//						curAlarmIdx = i;
		//
		//						PB_Main_event_send(PB_ALARM_EVT, PB_ALARM_CHECK_DISPLAY_ST, NULL);
		//					}
		//				}
		//
		//				//Check pre-alarm field.
		//				if (temp_schedule_data.preAlarm == PB_PREALARM_DAY) {
		//					memset(&cur_time_pre, 0, sizeof(tm));
		//					Clock_Get_time_pre(&cur_time_pre, 24*60*60);
		//					if (( (temp_schedule_data.year) == (cur_time_pre.tm_year +1900)) && (temp_schedule_data.mon == (cur_time_pre.tm_mon+1))
		//							&& (temp_schedule_data.day == cur_time_pre.tm_mday) && (temp_schedule_data.hour == cur_time_pre.tm_hour)
		//							 && (temp_schedule_data.min == cur_time_pre.tm_min) && ((temp_schedule_data.alarmFlags & 0x02) == 0x00)) {
		//						//Do alarm!
		//						//Check alarm method field.
		//						//Do not care method, use popup and vibration
		//						curAlarmIdx = i;
		//
		//						PB_Main_event_send(PB_ALARM_EVT, PB_ALARM_CHECK_DISPLAY_ST, NULL);
		//					}
		//				} else if (temp_schedule_data.preAlarm == PB_PREALARM_HOUR) {
		//					memset(&cur_time_pre, 0, sizeof(tm));
		//					Clock_Get_time_pre(&cur_time_pre, 60*60);
		//					if (( (temp_schedule_data.year) == (cur_time_pre.tm_year +1900)) && (temp_schedule_data.mon == (cur_time_pre.tm_mon+1))
		//					&& (temp_schedule_data.day == cur_time_pre.tm_mday) && (temp_schedule_data.hour == cur_time_pre.tm_hour)
		//					 && (temp_schedule_data.min == cur_time_pre.tm_min) && ((temp_schedule_data.alarmFlags & 0x02) == 0x00)) {
		//						//Do alarm!
		//						//Check alarm method field.
		//						//Do not care method, use popup and vibration
		//						curAlarmIdx = i;
		//
		//						PB_Main_event_send(PB_ALARM_EVT, PB_ALARM_CHECK_DISPLAY_ST, NULL);
		//					}
		//				} else if (temp_schedule_data.preAlarm == PB_PREALARM_HALFHOUR) {
		//					memset(&cur_time_pre, 0, sizeof(tm));
		//					Clock_Get_time_pre(&cur_time_pre, 30*60);
		//					if (( (temp_schedule_data.year) == (cur_time_pre.tm_year +1900)) && (temp_schedule_data.mon == (cur_time_pre.tm_mon+1))
		//					&& (temp_schedule_data.day == cur_time_pre.tm_mday) && (temp_schedule_data.hour == cur_time_pre.tm_hour)
		//					 && (temp_schedule_data.min == cur_time_pre.tm_min) && ((temp_schedule_data.alarmFlags & 0x02) == 0x00)) {
		//						//Do alarm!
		//						//Check alarm method field.
		//						//Do not care method, use popup and vibration
		//						curAlarmIdx = i;
		//
		//						PB_Main_event_send(PB_ALARM_EVT, PB_ALARM_CHECK_DISPLAY_ST, NULL);
		//					}
		//				}
		//
		//				//At time alarm.
		//				if (((temp_schedule_data.year) == (cur_time.tm_year +1900)) && (temp_schedule_data.mon == (cur_time.tm_mon+1))
		//					&& (temp_schedule_data.day == cur_time.tm_mday) && (temp_schedule_data.hour == cur_time.tm_hour)
		//					 && (temp_schedule_data.min == cur_time.tm_min) && ((temp_schedule_data.alarmFlags & 0x01) == 0x00)) {
		//					//Do alarm!
		//					//Check alarm method field.
		//					//Do not care method, use popup and vibration
		//					curAlarmIdx = i;
		//
		//					PB_Main_event_send(PB_ALARM_EVT, PB_ALARM_CHECK_DISPLAY_ST, NULL);
		//				}
		//
		//				//check snooze
		//				switch(temp_schedule_data.snooze)
		//				{
		//				case PB_SCH_SNOOZE_5MIN :
		//				{
		//					memset(&cur_time_pre, 0, sizeof(tm));
		//					Clock_Get_time_post(&cur_time_pre, 5*60);
		//					if (( (temp_schedule_data.year) == (cur_time_pre.tm_year +1900)) && (temp_schedule_data.mon == (cur_time_pre.tm_mon+1))
		//					&& (temp_schedule_data.day == cur_time_pre.tm_mday) && (temp_schedule_data.hour == cur_time_pre.tm_hour)
		//					 && (temp_schedule_data.min == cur_time_pre.tm_min))
		//					{
		//						curAlarmIdx = i;
		//						PB_Main_event_send(PB_ALARM_EVT, PB_ALARM_CHECK_DISPLAY_ST, NULL);
		//					}
		//				}
		//					break;
		//				case PB_SCH_SNOOZE_10MIN :
		//				{
		//					memset(&cur_time_pre, 0, sizeof(tm));
		//					Clock_Get_time_post(&cur_time_pre, 10*60);
		//					if (( (temp_schedule_data.year) == (cur_time_pre.tm_year +1900)) && (temp_schedule_data.mon == (cur_time_pre.tm_mon+1))
		//					&& (temp_schedule_data.day == cur_time_pre.tm_mday) && (temp_schedule_data.hour == cur_time_pre.tm_hour)
		//					&& (temp_schedule_data.min == cur_time_pre.tm_min))
		//					{
		//						curAlarmIdx = i;
		//						PB_Main_event_send(PB_ALARM_EVT, PB_ALARM_CHECK_DISPLAY_ST, NULL);
		//					}
		//				}
		//					break;
		//				}
		//			}
		//		}
	}
}

uint32_t time_check = 0;
static void processing_glucose_uart_evt(pbUIEvt_t UIevt_Msg)
{
	//uint8_t result_data_show[2][5];
	//uint8_t buffer_t;
	uint8_t temp_activity[19] = { 0, };

	if (PB_UI_State == UI_STATE_OFF) {
		//		Board_oledOn();
	}
	else if (PB_UI_State == UI_STATE_AFE || PB_UI_State == UI_STATE_AFE_TEST) {
		//		set_ui_afe_enable(false);
		//		AFE4404_FUNC_ENABLE(false);
	}

	//	stop_lcd_timeout();
	PB_UI_State = UI_STATE_POPUP_GLU;
	//	Board_clearLCD();
		//
	switch (UIevt_Msg.status) {
	case PB_GLUCOSE_DISPLAY_MEALS_SELECT_EVT:
		//		Board_oledOff() ;
		if (PB_UI_State == UI_STATE_AFE) {
			//			AFE4404_FUNC_ENABLE(AFE_FUNC_DISABLE);
		}

		if (UIevt_Msg.msg[0] == UART_MSG_DATA_BEFORE_MEALS) {
			//				Board_printGlucoseScreen( NULL, 0);
		}
		else if (UIevt_Msg.msg[0] == UART_MSG_DATA_AFTER_MEALS) {
			//				Board_printGlucoseScreen( NULL, 1);
		}
		break;
	case PB_GLUCOSE_DISPLAY_TEMP_CHECK_EVT:
		//			Board_DrawText(15, 10, "Glucose Test", LCD_COLOR_WHITE);
		//			Board_DrawText(25, 35, "Temp Measure", LCD_COLOR_WHITE);
		time_check = 0;
		break;
	case PB_GLUCOSE_DISPLAY_STRIP_CODE:
		//			Board_DrawText( 15, 10, "StripCode Num", LCD_COLOR_WHITE ) ;
		//			temp_activity[0] = '0' + glucose_strip_code/10 ;
		//			temp_activity[1] = '0' + glucose_strip_code%10 ;
		//			temp_activity[2] = NULL ;
		//
		//			Board_printGlucoseScreen( temp_activity, 6);
		break;
	case PB_GLUCOSE_DISPLAY_WAIT_BLOOD_DROP_EVT:
		//			if (time_check < 2) {
		//				Board_DrawText(12, 11, "Please Inject", LCD_COLOR_WHITE);
		//				Board_DrawText(14, 39, "Your Blood.", LCD_COLOR_WHITE);
		//			} else {
		//				Board_printGlucoseScreen( NULL, 2);
		//			}
		time_check++;
		break;
	case PB_GLUCOSE_DISPLAY_COUNT_1_EVT:
		//			buffer_t = '1' + UIevt_Msg.status - PB_GLUCOSE_DISPLAY_COUNT_1_EVT;
		//			Board_printGlucoseScreen(&buffer_t, 3);
		break;
	case PB_GLUCOSE_DISPLAY_COUNT_2_EVT:
		//			buffer_t = '1' + UIevt_Msg.status - PB_GLUCOSE_DISPLAY_COUNT_1_EVT;
		//			Board_printGlucoseScreen(&buffer_t, 3);
		break;
	case PB_GLUCOSE_DISPLAY_COUNT_3_EVT:
		//			buffer_t = '1' + UIevt_Msg.status - PB_GLUCOSE_DISPLAY_COUNT_1_EVT;
		//			Board_printGlucoseScreen(&buffer_t, 3);
		break;
	case PB_GLUCOSE_DISPLAY_COUNT_4_EVT:
		//			buffer_t = '1' + UIevt_Msg.status - PB_GLUCOSE_DISPLAY_COUNT_1_EVT;
		//			Board_printGlucoseScreen(&buffer_t, 3);
		break;
	case PB_GLUCOSE_DISPLAY_COUNT_5_EVT:
		//			buffer_t = '1' + UIevt_Msg.status - PB_GLUCOSE_DISPLAY_COUNT_1_EVT;
		//			Board_printGlucoseScreen(&buffer_t, 3);
		break;
	case PB_GLUCOSE_DISPLAY_RESULT_EVT:
		//			Board_oledOn() ;
		PB_UI_State = UI_STATE_POPUP;
		//			uitoa(get_glucose_result_data(), result_data_show[0], 5);
					// todo �߰�
		//			Board_printGlucoseScreen(result_data_show[0], 4);

					// isens test��, 4.9sec ������ ,�µ��� ǥ��
#if		ISENS_TEST_MODE
//			Board_DrawSmallNum( 20, 53, (uint8_t *)adc_value_49, LCD_COLOR_BLACK ) ;
//			Board_DrawSmallNum( 60, 53, (uint8_t *)temp_value, LCD_COLOR_BLACK ) ;
#endif

		if (PB_is_qc_complete() == false) {
			if (check_qc_test_bs(g_glucose_result_data) == true) {
				PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_SUCCESS_BS_ST, NULL);
				//					set_qc_test_bs_enable(false, 0, 0);
			}
			else {
				PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_FAIL_BS_ST, NULL);
			}
		}
		//			else
		//			{
		//				temp_activity[0] = 0x40;
		//				temp_activity[1] = PB_ACTIVITY_ID_GLUCOSE;
		//				temp_activity[2] = 0x11;
		//				temp_activity[3] = 0x04;
		//				temp_activity[4] = 0x01;	//CMD
		//				temp_activity[5] = g_glucose_result_data & 0xFF; // value low
		//				temp_activity[6] = (g_glucose_result_data & 0xFF00) >> 8; //value high
		//				temp_activity[7] = get_meal_state();
		//		//		data �����ϴºκ��̳� ���� �����ȵ�
		//				PB_Activity_flash_save(temp_activity);
		//			}
		break;
		// todo ������� ERROR, �� HI, RO ������ ���� ǥ�õǴ� ���� �ۼ�
	case PB_GLUCOSE_DISPLAY_ERROR_RES_HI:
		//			Board_printGlucoseScreen(result_data_show[0], 5);
		//			Board_DrawText(15, 28, "Error : High ", LCD_COLOR_WHITE);
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_RES_LO:
		//			Board_printGlucoseScreen(result_data_show[0], 5);
		//			Board_DrawText(15, 28, "Error : Low ", LCD_COLOR_WHITE);
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_STRIP_OUT_STATE:
		//			if(PB_is_qc_complete() == false) {
		//				task_sleep(1000);
		//				processing_qc_default_view();
		//				return;
		//			}
		//			else {
		//				restart_lcd_timeout(PB_LCD_TIMEOUT);
		//				PB_UI_State = UI_STATE_POPUP;
		//				Board_DrawText(15, 10, "PAAR Glucose", LCD_COLOR_WHITE);
		//				Board_DrawText(15, 35, "Strip Out!", LCD_COLOR_WHITE);
		//			}
		//			PB_sub_uart_uninit() ;
		//
		//			nrf_drv_gpiote_in_event_enable(BOARD_PIN_SUB_IO_IN, true);

		break;
	case PB_GLUCOSE_DISPLAY_END_EVT:
		//			restart_lcd_timeout(PB_LCD_TIMEOUT);
		PB_UI_State = UI_STATE_CLOCK;
		//			processing_update_screen();
		break;
		//////////////////// ERROR DISPLAY /////////////////////////////////////////////////
	case PB_GLUCOSE_DISPLAY_ERROR_USED_STRIP:
#if ISENS_TEST_MODE
		//			Board_DrawText(15, 35, "ERR1 USED", LCD_COLOR_WHITE);
#else
		//			Board_DrawText(15, 35, "Used Strip", LCD_COLOR_WHITE);
#endif
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_TEMPERATURE:
#if ISENS_TEST_MODE
		//			Board_DrawText(15, 35, "ERR3 TEMP", LCD_COLOR_WHITE);
#else
		//			Board_DrawText(15, 35, "Temp Err", LCD_COLOR_WHITE);
#endif
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_BLOOD_AMOUNT:
#if ISENS_TEST_MODE
		//			Board_DrawText(15, 35, "ERR4 AMOUNT", LCD_COLOR_WHITE);
#else
		//			Board_DrawText(15, 35, "Inject Err", LCD_COLOR_WHITE);
#endif
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_INJECT:
#if ISENS_TEST_MODE
		//			Board_DrawText(15, 35, "ERR2 INJECT", LCD_COLOR_WHITE);
#else
		//			Board_DrawText(15, 35, "Inject Err", LCD_COLOR_WHITE);
#endif
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_TIMEOUT:
		//			Board_DrawText(15, 35, "Time Out", LCD_COLOR_WHITE);
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_INVALID_STATE:
		//			Board_DrawText(15, 35, "Invalid State", LCD_COLOR_WHITE);
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_MSG_ERROR:
		//			Board_DrawText(15, 35, "Msg Err", LCD_COLOR_WHITE);
		break;
	case PB_GLUCOSE_DISPLAY_ERROR_ADC_ERROR:
		//			Board_DrawText(15, 35, "Value Err", LCD_COLOR_WHITE);
		break;
	default:
		break;
	}

	if ((UIevt_Msg.status >= PB_GLUCOSE_DISPLAY_ERROR_USED_STRIP)
		&& (UIevt_Msg.status != PB_GLUCOSE_DISPLAY_ERROR_STRIP_OUT_STATE)
		&& (UIevt_Msg.status != PB_GLUCOSE_DISPLAY_ERROR_RES_LO)
		&& (UIevt_Msg.status != PB_GLUCOSE_DISPLAY_ERROR_RES_HI))
	{
		//		Board_DrawText(15, 10, "Push Button", LCD_COLOR_WHITE);
	}

	//	Board_updateLCD();
	UIevt_Msg.msg = NULL;
}

static void processing_qc_msg_evt(pbUIEvt_t UIevt_Msg) {
	switch (UIevt_Msg.status) {
	case PB_QC_TEST_START_BUTTON_ST:
		break;
	case PB_QC_TEST_START_LCD_ST:
		//			if(PB_UI_State == UI_STATE_OFF) {
		//				Board_oledOn();
		//			}
		//
		PB_UI_State = UI_STATE_QC_LCD_TEST;
		//
		//			Board_clearLCD();
		//
		//			Board_DrawFillRect(0, 0, 128, 64, LCD_COLOR_WHITE);
		//
		//			Board_updateLCD();
		//
		//			task_sleep(1000);
		//
		//			Board_clearLCD();
		//
		//			Board_updateLCD();
		//
		//			task_sleep(1000);
		//
		//			Board_clearLCD();
		//
		//			Board_DrawFillRect(0, 0, 128, 64, LCD_COLOR_WHITE);
		//
		//			Board_updateLCD();

		break;
	case PB_QC_TEST_START_MOT_ST:
		PB_UI_State = UI_STATE_QC_MOT_TEST;

		//			Board_clearLCD();
		//
		//			Board_DrawText(3,3,(uint8_t*) "PAAR Band QC",LCD_COLOR_WHITE);
		//			Board_DrawText(3,30,(uint8_t*) "Motor Test",LCD_COLOR_WHITE);
		//
		//			Board_updateLCD();
		//
		//			PB_Set_Motor_vibration(1000, 3);//duration : 1sec, count : 3

		break;
	case PB_QC_TEST_START_FLASH_ST: {
		PB_UI_State = UI_STATE_QC_MOT_TEST;

		//			Board_clearLCD();

		//			Board_DrawText(3,3,(uint8_t*) "PAAR Band QC",LCD_COLOR_WHITE);
		//			Board_DrawText(3,30,(uint8_t*) "Flash Test",LCD_COLOR_WHITE);

		//			Board_updateLCD();

		bool result;
		//			PB_QC_flash_test_init();
		//			PB_QC_flash_test_flash_write();
		result = PB_QC_flash_test_flash_read();

		if (result == true)
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_SUCCESS_FLASH_ST, NULL);
		else
			PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_FAIL_FLASH_ST, NULL);

		// OS
		task_sleep(100);

		//			processing_qc_default_view();

		break;
	case PB_QC_TEST_START_RF_ST:
	{
		PB_UI_State = UI_STATE_QC_MOT_TEST;

		//			Board_clearLCD();

		//			Board_DrawText(3,3,(uint8_t*) "PAAR Band QC",LCD_COLOR_WHITE);
		//			Board_DrawText(3,30,(uint8_t*) "RF Test",LCD_COLOR_WHITE);

		//			Board_updateLCD();

		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_SUCCESS_RF_ST, NULL);

		// OS
		task_sleep(1000);

		//			processing_qc_default_view();
	}

	break;
	case PB_QC_TEST_START_ACC_ST:
	{
		PB_UI_State = UI_STATE_QC_ACC_TEST;

		//			Board_clearLCD();

		//			Board_DrawText(3,3,(uint8_t*) "PAAR Band QC",LCD_COLOR_WHITE);
		//			Board_DrawText(3,30,(uint8_t*) "ACC Test",LCD_COLOR_WHITE);

		//			Board_updateLCD();

		int16_t temp_pre_x = BMI160_ACC_DATA_READ_X_AXIS();

		while (1)
		{
			int16_t temp_x;
			temp_x = BMI160_ACC_DATA_READ_X_AXIS();

			//				if((temp_pre_x - temp_x) >= 500 || (temp_pre_x - temp_x) <= -500 )
			if ((temp_pre_x - temp_x) >= 1 || (temp_pre_x - temp_x) <= -1)
				break;

			// OS
			task_sleep(100);
		}

		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_SUCCESS_ACC_ST, NULL);
	}
	break;
	case PB_QC_TEST_START_BS_ST:
	{
		PB_UI_State = UI_STATE_QC_MOT_TEST;

		//			Board_clearLCD();

		//			Board_DrawText(3,3,(uint8_t*) "PAAR Band QC",LCD_COLOR_WHITE);
		//			Board_DrawText(3,30,(uint8_t*) "BS Test",LCD_COLOR_WHITE);

		//			Board_updateLCD();

			//		set_qc_test_bs_enable(true);
			//		PB_Main_event_send(PB_QC_EVT, PB_QC_TEST_RESULT_SUCCESS_BS_ST, NULL);
	}
	break;
	case PB_QC_TEST_START_ALL_ST:
	{
		PB_UI_State = UI_STATE_QC_MOT_TEST;

		//			Board_clearLCD();

		//			Board_DrawText(3,3,(uint8_t*) "PAAR Band QC",LCD_COLOR_WHITE);
		//			Board_DrawText(3,30,(uint8_t*) "Test All",LCD_COLOR_WHITE);

		//			Board_updateLCD();

					// OS
		task_sleep(1000);
	}
	break;
	case PB_QC_TEST_END_ST:

		PB_UI_State = UI_STATE_CLOCK_NOT_QC_COMPLETE;

		//			Board_clearLCD();?

		//			Board_DrawText(3,3,(uint8_t*) "PAAR Band QC",LCD_COLOR_WHITE);
		//			Board_DrawText(3,30,(uint8_t*) "Test END",LCD_COLOR_WHITE);

		//			Board_updateLCD();

		//			PB_QC_conf_end_save();

					// OS
		task_sleep(1000);

		NVIC_SystemReset();

		break;
	}
	}
}
