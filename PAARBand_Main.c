#include <stdlib.h>
#include <time.h>
#include "PAARBand_Main.h"
#include "UI.h"
#include "sw_config.h"

#include "absconfig.h"
#include "PB_Glucose_uart.h"
#include "AFE4404.h"
#include "BMI_160.h"
#include "PB_QC_i2c.h"
#include "nrf_drv_config.h"
//#include "os.h"

extern int scheduler();
static uint8_t main_task_init_ready = 0;
static pbQC_t PB_current_qc_conf;
uint16_t PB_qc_test_bs_min = 0;
uint16_t PB_qc_test_bs_max = 0;
static msgq_pt Main_Msgq;
uint8_t g_glucose_enable = 0;
sem_pt _uart_tx_evt_sem = NULL;
pb_afe_save PB_AFE_save;
bool PB_qc_test_all_enable = false;
void PB_STOP_SMART_CT();
void PB_stop_BS_stable_timer();

void PB_stop_BS_stable_timer() {}

// watch dog refresh handler
static void PB_wdt_refresh_handler() {
	PB_Main_event_send(PB_WDT_REFRESH_EVT, NULL, NULL);
}

uint8_t PB_Main_event_send(uint8_t Main_evt, uint8_t Main_evt_state, uint8_t* msg)
{
	pbMainEvt_t temp_msg;

	temp_msg.event = Main_evt;
	temp_msg.status = Main_evt_state;
	temp_msg.msg = msg;
	printf("the msg is %s\n",msg);

	// OS
	msgq_send(Main_Msgq, (unsigned char*)& temp_msg);

	return 0;
}

uint8_t get_main_task_init_ready() {
	return main_task_init_ready;
}

bool PB_Schedule_flash_read(pbSchedule_t* schedule_buf, uint8_t* boundary, uint16_t index)
{
	//	readSchduleData(schedule_buf, boundary, index);
	//
	//	return 0;

	srand(time(NULL));
	int random = rand() % 2;

	if (random == 0) {
		return false;
	}

	return true;
}

bool PB_is_qc_complete() {
	return PB_current_qc_conf.is_qc_completed;
}

bool check_qc_test_bs(uint16_t val) {
	if (val >= PB_qc_test_bs_min && val <= PB_qc_test_bs_max)
		return true;
	else
		return false;
}

bool PB_QC_flash_test_flash_read() {
	//	qc_flash_test_t temp_test_data1, temp_test_data2;
	//
	//	memset(temp_test_data2.test_data, QC_TEST_FLASH_DATA_DEFAULT, sizeof(qc_flash_test_t));
	//
	//	readQC_test_data((uint8_t*)&temp_test_data1);
	//
	//	if(memcmp(&temp_test_data1, &temp_test_data2, sizeof(qc_flash_test_t)) == 0)
	//		return true;
	//	else
	//		return false;

		// written by yshin
	srand(time(NULL));
	int random = rand() % 2;

	if (random == 0)
		return true;

	return false;
}

void PB_PAARBand_Main_init() {
	int r;

	//msgq_create : UI msgq
	// OS
	printf("create msgq Main_Msgq\n\n");
	r = msgq_create(&Main_Msgq, sizeof(pbMainEvt_t), UI_MAX_MSGQ_COUNT);
	if (0 != r) {
#if DEBUG
		printf("fail at msgq_create\n");
#endif
	}

	//	PB_spi_init();

		// OS
	printf("create task MainTask\n\n");
	r = task_create(4);//Main Task
	if (0 != r) {
#if DEBUG
		printf("fail at task_create\n");
#endif
	}

#if(PB_POWER_MANAGER_ENABLE == 1)
	//	Power_Manager_Init();
#endif
}

#define JUMP_PB_Main_Task(){\
	switch (current_pc[4])\
	{\
		case 0:\
			goto L_PB_Main_Task_0;break;\
		case 1:\
			goto L_PB_Main_Task_1;break;\
		case 2:\
			goto L_PB_Main_Task_2;break;\
		case 3:\
			goto L_PB_Main_Task_3;break;\
		case 4:\
			goto L_PB_Main_Task_4;break;\
		case 5:\
			goto L_PB_Main_Task_5;break;\
		case 7:\
			goto L_PB_Main_Task_7;break;\
		case 8:\
			goto L_PB_Main_Task_8;break;\
		case 9:\
			goto L_PB_Main_Task_9;break;\
		case 10:\
			goto L_PB_Main_Task_10;break;\
		case 11:\
			goto L_PB_Main_Task_11;break;\
		case 12:\
			goto L_PB_Main_Task_12;break;\
		case 13:\
			goto L_PB_Main_Task_13;break;\
		case 14:\
			goto L_PB_Main_Task_14;break;\
		case 15:\
			goto L_PB_Main_Task_15;break;\
		case 16:\
			goto L_PB_Main_Task_16;break;\
		case 17:\
			goto L_PB_Main_Task_17;break;\
		case 18:\
			goto L_PB_Main_Task_18;break;\
		case 19:\
			goto L_PB_Main_Task_19;break;\
		case 20:\
			goto L_PB_Main_Task_20;break;\
		case 21:\
			goto L_PB_Main_Task_21;break;\
		case 22:\
			goto L_PB_Main_Task_22;break;\
		case 23:\
			goto L_PB_Main_Task_23;break;\
		case 24:\
			goto L_PB_Main_Task_24;break;\
		case 25:\
			goto L_PB_Main_Task_25;break;\
		case 26:\
			goto L_PB_Main_Task_26;break;\
		case 27:\
			goto L_PB_Main_Task_27;break;\
		case 28:\
			goto L_PB_Main_Task_28;break;\
		case 29:\
			goto L_PB_Main_Task_29;break;\
		case 30:\
			goto L_PB_Main_Task_30;break;\
		case 31:\
			goto L_PB_Main_Task_31;break;\
		case 32:\
			goto L_PB_Main_Task_32;break;\
		case 33:\
			goto L_PB_Main_Task_33;break;\
		case 34:\
			goto L_PB_Main_Task_34;break;\
		case 35:\
			goto L_PB_Main_Task_35;break;\
		case 36:\
			goto L_PB_Main_Task_36;break;\
		case 37:\
			goto L_PB_Main_Task_37;break;\
		case 38:\
			goto L_PB_Main_Task_38;break;\
		case 39:\
			goto L_PB_Main_Task_39;break;\
		case 40:\
			goto L_PB_Main_Task_40;break;\
	}\
}

/* ======================PB_Main_Task local var=================================*/
int r = 0;
uint32_t temp_HR_output = 0;
pbMainEvt_t Main_msgRxBuffer;

//	intr_connectisr_test(RTC2_IRQn, RTC2_IRQHandler);

uint8_t test_count_tick = 0;
uint8_t test_count_loop = 0;
uint8_t test_result_mux;
uint32_t err = 0;
extern uint8_t PB_BLE_event_send(uint8_t UI_evt, uint8_t UI_evt_state, uint8_t* msg);
/*================================================================================*/

//static void TASK(4) { // PB_Main_Task

void PB_Main()
{
	JUMP_PB_Main_Task();
L_PB_Main_Task_0:


	//	app_timer_create(&PB_button_stable_timer_id, APP_TIMER_MODE_SINGLE_SHOT, Board_Button_Stable_handler);
	//	app_timer_create(&PB_nxp_stable_timer_id, APP_TIMER_MODE_SINGLE_SHOT, stable_nxp);

	//	app_timer_create(&PB_SMART_CT_data_timer, APP_TIMER_MODE_REPEATED, PB_smart_ct_data_period_handler);
	//	app_timer_create(&PB_SMART_CT_acc_avr_timer, APP_TIMER_MODE_REPEATED, PB_smart_ct_acc_check_handler);

	//	app_timer_create(&PB_bs_stable_timer_id, APP_TIMER_MODE_SINGLE_SHOT, PB_stable_bs_uart);

		// OS
	current_pc[4] = 1;
	printf("PB_Main going to sleep\n\n");
	task_sleep(100);
	scheduler();
	return;

L_PB_Main_Task_1:

	//	nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(false);

	//	_irq_handler_table[GPIOTE_IRQn] = GPIOTE_IRQHandler;

	//	err_code = nrf_drv_gpiote_init();

	//	nrf_drv_gpiote_in_config_t in_config_nxp = GPIOTE_CONFIG_IN_SENSE_LOTOHI(false);
	//	nrf_drv_gpiote_in_config_t in_config_nxp =

		//test_code : regulator
	//	nrf_gpio_cfg_output(BOARD_PIN_MOTOR_PWR);
	//	nrf_gpio_pin_clear(BOARD_PIN_MOTOR_PWR);

	//	err_code = nrf_drv_gpiote_in_init(BOARD_PIN_BUTTON_INT, &in_config, Board_Button_handler);
	//	nrf_drv_gpiote_in_event_enable(BOARD_PIN_BUTTON_INT, true);

	//	nrf_gpio_cfg_output(BOARD_PIN_SUB_PWR);

	//	nrf_gpio_pin_clear(BOARD_PIN_SUB_PWR);

		// OS
	current_pc[4] = 2;
	printf("PB_Main going to sleep\n\n");
	task_sleep(100);
	scheduler();
	return;

L_PB_Main_Task_2:
	//	nrf_gpio_pin_set(BOARD_PIN_SUB_PWR);

#if(PB_LF_PNIP_ENABLE && (BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_LF || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_LF))
//	nrf_drv_gpiote_in_init(BOARD_PIN_SUB_IO_IN, &in_config_nxp, in_pin_handler_nxp);
//	nrf_drv_gpiote_in_event_enable(BOARD_PIN_SUB_IO_IN, true);

//	nrf_gpio_cfg_output(BOARD_PIN_SUB_IO_OUT);

//	LFwakeup_pin_disable();

	// OS
	//current_pc[PB_Main_Task] = 3;
	//task_sleep(100);
	//scheduler();
	//return;

	//	nrf_gpio_pin_set(BOARD_PIN_SUB_PWR);

//L_PB_Main_Task_3:

		// OS
	//current_pc[PB_Main_Task] = 4;
	//task_sleep(300);
	//scheduler();
	//return;
//L_PB_Main_Task_4:

#elif(PB_BS_CHECK_EANBLE && ( BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_BS || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_BS ) )
//	nrf_drv_gpiote_in_init(BOARD_PIN_SUB_IO_IN, &in_config_nxp, out_pin_handler_glucose);
//	nrf_drv_gpiote_in_event_enable(BOARD_PIN_SUB_IO_IN, true);

	//test code
//	PB_Glucose_Go_State_Init() ;
#endif

#if(PB_ACC_TAP_ENABLE == 1)
//	err_code = nrf_drv_gpiote_in_init(BOARD_PIN_ACCEL_INT1, &in_config2, Board_ACCTap_Handler);
#endif

//	nrf_drv_gpiote_in_config_t in_config_batt_check = GPIOTE_CONFIG_IN_SENSE_TOGGLE(false);

//	nrf_drv_gpiote_in_init(BOARD_PIN_CHARGE_ST_INT, &in_config_batt_check, batt_check_handler);
//	nrf_drv_gpiote_in_event_enable(BOARD_PIN_CHARGE_ST_INT, true);
////===========================================================================================

//	PB_pedometer_init();

#if(PB_LF_PNIP_ENABLE && ( BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_LF || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_LF ) )
	// OS
	//current_pc[PB_Main_Task] = 5;
	//r = mutex_create(&PB_NXP_uart_evt_guard);
	if (0 != r) {
#if DEBUG
		printf("fail to sem_create\n\r");
#endif
	}
	//scheduler();
	//return;

//L_PB_Main_Task_5:



#elif(PB_BS_CHECK_EANBLE && ( BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_BS || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_BS ) )

	g_glucose_enable = 0;

	// OS
	current_pc[4] = 3;
	printf("create sem _uart_tx_evt_sem\n\n");
	r = sem_create(&_uart_tx_evt_sem);
	scheduler();
	return;

L_PB_Main_Task_3:

	if (0 != r) {
#if DEBUG
		printf("fail to sem_create\n\r");
#endif
	}

#endif
	//	PB_i2c_init();

	//    Clock_Init();


	//	PB_RTC_Write_control(0x00);

	//	uint8_t year;
	//	uint8_t mon;
	//	uint8_t days;
	//	uint8_t hours;
	//	uint8_t min;
	//	uint8_t sec;
	//
	//	PB_RTC_Read_time(&year, &mon, &days, &hours, &min, &sec);
	//
	//	tm temp_time;
	//
	//	temp_time.tm_sec = sec;
	//	temp_time.tm_min = min;
	//	temp_time.tm_hour = hours;
	//	temp_time.tm_mday = days;
	//	temp_time.tm_mon = mon -1;
	//	temp_time.tm_year = 2000 + year - 1900;
	//	temp_time.tm_isdst = -1;
	//
	//	temp_time.tm_wday 	= 0;
	//	temp_time.tm_yday 	= 0;
	//
	//	Clock_Set_Time(&temp_time);

	//	BMI160_Count_Reset();

	//	PB_step_count_start();

#if( PB_LF_PNIP_ENABLE && (BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_LF || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_LF))
	NXP_LF_data rev_LF_data;
	uint8_t sendData[2] = { 0, };

	//	PB_NXP_Uart_Trx_enable();

	//	LFwakeup_pin_enable();

		// OS
	//current_pc[PB_Main_Task] = 7;
	//task_sleep(50);
	//scheduler();
	//return;

//L_PB_Main_Task_7:


	// PNIP state
	sendData[0] = 0xC9;
	sendData[1] = 0xAE;
	//	NXP_Uart_send(sendData);

		// OS
	//current_pc[PB_Main_Task] = 8;
	//task_sleep(50);
	//scheduler();
	//return;

//L_PB_Main_Task_8:

	//	LFwakeup_pin_disable();

	//	PB_NXP_Uart_Trx_disable();
#endif

#if(PB_QC_FUNC_ENABLE == 1)

#if(PB_QC_INIT_FORCED == 1)
//	PB_QC_Conf_init();
#endif

//	PB_QC_Conf_Check();

#else
	//no implentment
	//PB_QC_conf_set(true, PAAR_DEVICE_ID0, PAAR_DEVICE_ID1, PAAR_DEVICE_ID2, PAAR_DEVICE_ID3, true, false);

#if PB_FONT_DOWNLOAD_ENABLE
	writeUIData(PB_KOREAN, KSX1001_FontTbl, sizeof(KSX1001_FontTbl));
	writeUIData(PB_ENGLISH, FontTbl_eng, sizeof(FontTbl_eng));
	writeUIData(PB_KOREANTABLE, HanIndexTbl, sizeof(HanIndexTbl));

	PB_init_Activity_flash();
	PB_Set_LEXCO_Setting_Default();
#endif

#endif

	//	PB_init_Activity_check();
	//	PB_init_Schedule_check();

	//	nrf_gpio_cfg_output(BOARD_PIN_BAT_ADC_EN);

	//	nrf_gpio_pin_clear(BOARD_PIN_BAT_ADC_EN);

	//    nrf_saadc_channel_config_t channel_config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);

	//    nrf_drv_saadc_init(NULL, saadc_callback);

	//    nrf_drv_saadc_channel_init(0, &channel_config);

		//test_code Power Manager
#if(PB_POWER_MANAGER_ENABLE == 1)
//    ubik_tick_switch();

//    PB_Power_Manager_Enable();
#endif

	//set_main_task_init_ready();
	// ys modified

	main_task_init_ready = 1;
	current_pc[4] = 4;
	printf("Main task -> PB_BLE_event_send(PB_BLE_CONTROL_EVT, PB_BLE_REFRESH, NULL);\n\n");
	PB_BLE_event_send(PB_BLE_CONTROL_EVT, PB_BLE_REFRESH, NULL);
	scheduler();
	return;

L_PB_Main_Task_4:


	//==============================================================
	//WatchDog Timer Setup
//    nrf_drv_wdt_config_t config = PB_WDT_DEAFULT_CONFIG;
//	nrf_drv_wdt_init(&config, PB_wdt_event_handler);
//	nrf_drv_wdt_channel_alloc(&m_channel_id);
//	app_timer_create(&PB_wdt_refresh_timer, APP_TIMER_MODE_REPEATED, PB_wdt_refresh_handler);
//	nrf_drv_wdt_enable();
//  app_timer_start(PB_wdt_refresh_timer, PB_WDT_CONFIG_RELOAD_VALUE/2*32, NULL);
	//==============================================================

	while (1) {
		// OS
		current_pc[4] = 5;
		printf("Main task -> msgq_receive(Main_Msgq, (unsigned char*)& Main_msgRxBuffer)\n\n");
		r = msgq_receive(Main_Msgq, (unsigned char*)& Main_msgRxBuffer);
		scheduler();
		return;

	L_PB_Main_Task_5:


		if (0 != r) {
#if DEBUG
			printf("fail at msgq_receive\r\n");
#endif
		}
		else {
			switch (Main_msgRxBuffer.event) {
			case PB_KEY_CHANGE_EVT:
#if(BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_LF || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_LF )
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
#elif(BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_BS || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_BS)
				//no implement
				/*if (get_glucose_state()) {
					PB_Glucose_Key_Check_State(Main_msgRxBuffer.status); //msg send;
					scheduler();
					current_pc[4] = 6;
					return;

				L_PB_Main_Task_6:
					;
				}
				else {*/
					printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
					PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
					scheduler();
					current_pc[4] = 7;
					return;

				L_PB_Main_Task_7:
					;
				//}
#endif
				break;
			case PB_BATT_EVT:
				if (PB_Get_UI_state() != UI_STATE_AFE) {

					printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
					PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
					scheduler();
					current_pc[4] = 8;
					return;

				L_PB_Main_Task_8:
					;
				}

				break;
			case PB_TIME_EVT:
				if (PB_Get_UI_state() != UI_STATE_AFE) {
					printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);");
					PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
					scheduler();
					current_pc[4] = 9;
					return;

				L_PB_Main_Task_9:
					;
				}

				break;
			case PB_BLE_EVT:
				if (Main_msgRxBuffer.status == PB_BLE_DISCONNECTION_EVT_ST) {
					printf("Main task -> PB_STOP_SMART_CT();");
					PB_STOP_SMART_CT(); // msg send
					scheduler();
					current_pc[4] = 10;
					return;

				L_PB_Main_Task_10:
					;
				}

				if (PB_Get_UI_state() != UI_STATE_AFE) {
					printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n");
					PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
					scheduler();
					current_pc[4] = 11;
					return;

				L_PB_Main_Task_11:
					;
				}

				break;
			case PB_AFE_EVT:
				if (Main_msgRxBuffer.status == PB_AFE_EQZ_EVT_ST) {
					if (temp_HR_output < 200) {
						add_AFE_HR_data(temp_HR_output);
					}
				}
				printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
				scheduler();
				current_pc[4] = 12;
				return;
			L_PB_Main_Task_12:
				break;

			case PB_POPUP_EVT:
				printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
				scheduler();
				current_pc[4] = 13;
				return;
			L_PB_Main_Task_13:
				break;

			case PB_ALARM_EVT:
				printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
				scheduler();
				current_pc[4] = 14;
				return;
			L_PB_Main_Task_14:
				break;

			case PB_LF_EVT:
#if(PB_LF_PNIP_ENABLE && (BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_LF || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_LF) )
				//					switch(Main_msgRxBuffer.status)
				//					{
				//						case PB_LF_IO_INT_EVT_ST :
				//							break;
				//						case PB_LF_DATA_EVT_ST :
				//						{
				//							PB_NXP_Uart_Rev_disable();
				//
				//							rev_LF_data = nxp_dataParsing((char*) &uartReadTempBuf[0], UART_READ_TEMP_SIZE - 2);
				//							//session_state = connected
				//							if(Get_session_state() == SESSION_CONNECTED)
				//							{
				//								//LF : session end
				//								if((rev_LF_data.data[1]&0x80) == 0x80)
				//								{
				//									if(get_PNIP_state() == false)
				//									{
				//										uint8_t* lf_distance = malloc(sizeof(uint8_t));
				//										lf_distance[0] = rev_LF_data.distance;
				//										PB_BLE_event_send(PB_BLE_CONTROL_EVT, PB_BLE_CONTROL_PNIP_START_ST, lf_distance);
				//									}
				//
				//									Session_stop();
				//								}
				//								//LF : session refresh
				//								else
				//								{
				//									Session_refresh();
				//									PB_Main_event_send(PB_PNIP_EVT, PB_PNIP_SESSION_REFRESH, NULL);
				//								}
				//							}
				//							//session_state = idle
				//							else
				//							{
				//								if(get_PNIP_state() == false)
				//								{
				//									uint8_t* lf_distance = malloc(sizeof(uint8_t));
				//									lf_distance[0] = rev_LF_data.distance;
				//									PB_BLE_event_send(PB_BLE_CONTROL_EVT, PB_BLE_CONTROL_PNIP_START_ST, lf_distance);
				//								}
				//							}
				//
				//							uint8_t* msg_buffer = malloc(3);
				//							memcpy(msg_buffer, rev_LF_data.data, 2);
				//							msg_buffer[2] = rev_LF_data.distance;
				//
				//							PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, msg_buffer);
				//						}
				//							break;
				//					}
#endif

				break;
			case PB_PNIP_EVT:
				switch (Main_msgRxBuffer.status) {
				case PB_PNIP_SESSION_TIMEOUT:
					//							Session_stop();
					printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
					PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, NULL);
					scheduler();
					current_pc[4] = 15;
					return;
				L_PB_Main_Task_15:
					break;

				case PB_PNIP_SESSION_REFRESH:
					printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
					PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, NULL);
					scheduler();
					current_pc[4] = 16;
					return;
				L_PB_Main_Task_16:
					break;
				}
				printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
				scheduler();
				current_pc[4] = 17;
				return;
			L_PB_Main_Task_17:
				break;

			case PB_ACTIVITY_EVT:
				printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
				scheduler();
				current_pc[4] = 18;
				return;
			L_PB_Main_Task_18:
				break;

			case PB_WATCHDOG_CLEAR_EVT:
				break;
			case PB_GLUCOSE_EVT:

				printf("Main task -> PB_UART_Read_Loop(Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				err = PB_UART_Read_Loop(Main_msgRxBuffer.status, Main_msgRxBuffer.msg);//msg send
				if (err == 1)
					PB_stop_BS_stable_timer();
				scheduler();
				current_pc[4] = 19;
				return;
			L_PB_Main_Task_19:
				break;
			case PB_AFE_CHECK_EVT:
				break;
			case PB_PAAR_TAG_EVT:

				printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
				scheduler();
				current_pc[4] = 20;
				return;
			L_PB_Main_Task_20:
				break;
			case PB_PEDOMETER_EVT:
				printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
				scheduler();
				current_pc[4] = 21;
				return;
			L_PB_Main_Task_21:
				break;

			case PB_SMART_CAR_TALK_EVT:
				switch (Main_msgRxBuffer.status) {
				case PB_SMART_CAR_TALK_ALARM_ST:
					printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
					PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
					scheduler();
					current_pc[4] = 22;
					return;
				L_PB_Main_Task_22:
					break;

				case PB_SMART_CAR_TALK_DATA_EVT_ST:
					printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
					PB_BLE_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
					scheduler();
					current_pc[4] = 23;
					return;
				L_PB_Main_Task_23:
					break;

				case PB_SMART_CAR_ACC_CHECK_EVT_ST:
					BMI160_ACC_avr_check();

					break;
				}

				break;
			case PB_TEST_MSG_EVT:
			{
				printf("Main task -> PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);\n\n");
				PB_UI_event_send(Main_msgRxBuffer.event, Main_msgRxBuffer.status, Main_msgRxBuffer.msg);
				scheduler();
				current_pc[4] = 24;
				return;
			L_PB_Main_Task_24:
				;
			}
			break;
			case PB_QC_EVT:
				switch (Main_msgRxBuffer.status)
				{
				case PB_QC_PACKET_REV_ST:
					printf("Main task -> PB_rev_qc_msg()\n\n");
					PB_rev_qc_msg();//sleep or msg send
					scheduler();
					current_pc[4] = 25;
					return;
				L_PB_Main_Task_25:
					break;

				case PB_QC_TEST_START_ST:
					break;
				case PB_QC_TEST_START_LCD_ST:
				case PB_QC_TEST_START_MOT_ST:
				case PB_QC_TEST_START_FLASH_ST:
				case PB_QC_TEST_START_RF_ST:
				case PB_QC_TEST_START_ACC_ST:
				case PB_QC_TEST_START_BS_ST:
				case PB_QC_TEST_START_ALL_ST:
				case PB_QC_TEST_END_ST:
					printf("Main task -> PB_process_qc_evt(Main_msgRxBuffer);\n\n", );
					PB_process_qc_evt(Main_msgRxBuffer);//msg send
					scheduler();
					current_pc[4] = 26;
					return;
				L_PB_Main_Task_26:
					break;
					//LCD test result
				case PB_QC_TEST_RESULT_SUCCESS_LCD_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_LCD_ST, true);\n\n", );
					PB_send_qc_result(PB_QC_TEST_START_LCD_ST, true); //msg send
					scheduler();
					current_pc[4] = 27;
					return;
				L_PB_Main_Task_27:

					break;
				case PB_QC_TEST_RESULT_FAIL_LCD_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_LCD_ST, true);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_LCD_ST, true);
					scheduler();
					current_pc[4] = 28;
					return;

					L_PB_Main_Task_28:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_LCD_ST, false);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_LCD_ST, false);
					scheduler();
					current_pc[4] = 29;
					return;

				L_PB_Main_Task_29:

					break;
					//MOT test result
				case PB_QC_TEST_RESULT_SUCCESS_MOT_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_MOT_ST, true);\n");
					PB_send_qc_result(PB_QC_TEST_START_MOT_ST, true);
					scheduler();
					current_pc[4] = 30;
					return;
				L_PB_Main_Task_30:
					break;
				case PB_QC_TEST_RESULT_FAIL_MOT_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_MOT_ST, false);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_MOT_ST, false);
					scheduler();
					current_pc[4] = 31;
					return;
				L_PB_Main_Task_31:
					break;
					//FLASH test result
				case PB_QC_TEST_RESULT_SUCCESS_FLASH_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_MOT_ST, true);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_FLASH_ST, true);
					scheduler();
					current_pc[4] = 32;
					return;
				L_PB_Main_Task_32:
					break;
				case PB_QC_TEST_RESULT_FAIL_FLASH_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_FLASH_ST, false);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_FLASH_ST, false);
					scheduler();
					current_pc[4] = 33;
					return;
				L_PB_Main_Task_33:
					break;
					//RF test result
				case PB_QC_TEST_RESULT_SUCCESS_RF_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_RF_ST, true);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_RF_ST, true);
					scheduler();
					current_pc[4] = 34;
					return;
				L_PB_Main_Task_34:
					break;
				case PB_QC_TEST_RESULT_FAIL_RF_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_RF_ST, false);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_RF_ST, false);
					scheduler();
					current_pc[4] = 35;
					return;
				L_PB_Main_Task_35:
					break;
					//ACC test result
				case PB_QC_TEST_RESULT_SUCCESS_ACC_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_ACC_ST, true);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_ACC_ST, true);
					scheduler();
					current_pc[4] = 36;
					return;
				L_PB_Main_Task_36:
					break;
				case PB_QC_TEST_RESULT_FAIL_ACC_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_ACC_ST, false);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_ACC_ST, false);
					scheduler();
					current_pc[4] = 37;
					return;
				L_PB_Main_Task_37:
					break;
					//ACC test result
				case PB_QC_TEST_RESULT_SUCCESS_BS_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_BS_ST, true);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_BS_ST, true);
					scheduler();
					current_pc[4] = 38;
					return;
				L_PB_Main_Task_38:
					break;
				case PB_QC_TEST_RESULT_FAIL_BS_ST:
					printf("Main task -> PB_send_qc_result(PB_QC_TEST_START_BS_ST, false);\n\n");
					PB_send_qc_result(PB_QC_TEST_START_BS_ST, false);
					scheduler();
					current_pc[4] = 39;
					return;
				L_PB_Main_Task_39:
					break;
				}
				break;
			case PB_WDT_REFRESH_EVT:
				//refresh WDT Value
//					nrf_wdt_reload_value_set(WDT_CONFIG_RELOAD_VALUE);
				break;
			}
		}
	L_PB_Main_Task_40:
		;
	}

	current_pc[4] = 0;
	TerminateTask();
	scheduler();
	return;
}

extern int8_t PB_UI_event_send(uint8_t UI_evt, uint8_t UI_evt_state, uint8_t* msg);
void PB_STOP_SMART_CT() {
	if (get_smart_ct_service_enable() == true) {
		set_smart_ct_service_enable(false);
		//		AFE4404_FUNC_ENABLE(false);
		//		app_timer_stop(PB_SMART_CT_data_timer);
		//		app_timer_stop(PB_SMART_CT_acc_avr_timer);
		PB_UI_event_send(PB_UI_REFRESH_EVT, NULL, NULL);
	}
}

void add_AFE_HR_data(uint32_t HR_data) {
	if (HR_data > 30) {
		PB_AFE_save.afe_sum += HR_data;
		PB_AFE_save.afe_count++;
	}
}

bool get_qc_test_all_enable() {
	return PB_qc_test_all_enable;
}

void set_qc_test_all_enable(bool val) {
	PB_qc_test_all_enable = val;
}
