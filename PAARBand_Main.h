#ifndef APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PAARBAND_MAIN_H_
#define APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PAARBAND_MAIN_H_

#include <stdint.h>
#include <stdbool.h>
#include "os.h"

//PB Main Event


enum
{
	PB_KEY_CHANGE_EVT = 0,
	PB_BATT_EVT,
	PB_LCD_TIMEOUT_EVT,
	PB_TIME_EVT,
	PB_BLE_EVT,
	PB_AFE_EVT,
	PB_ALARM_EVT,
	PB_POPUP_EVT,
	PB_LF_EVT,
	PB_PNIP_EVT,
	PB_ACTIVITY_EVT,
	PB_WATCHDOG_CLEAR_EVT,
	PB_BLE_PACKET_EVT,
	PB_GLUCOSE_EVT,
	PB_NO_ACT,
	PB_AFE_CHECK_EVT,
	BIO_INT_EVT,
	PB_HEALTHCARE_EVT,
	PB_BLE_CONTROL_EVT,

	PB_PAAR_TAG_EVT,
	PB_PEDOMETER_EVT,

	PB_SMART_CAR_TALK_EVT,
	PB_ACC_PERIOD_EVT,
	PB_AFE_PERIOD_EVT,

	PB_QC_EVT,

	PB_TEST_MSG_EVT,

	PB_UI_REFRESH_EVT,

	PB_WDT_REFRESH_EVT,

};

enum {
	PB_QC_PACKET_REV_ST = 0,
	PB_QC_TEST_START_ST,
	PB_QC_TEST_START_BUTTON_ST,
	PB_QC_TEST_START_LCD_ST,
	PB_QC_TEST_START_MOT_ST,
	PB_QC_TEST_START_ACC_ST,
	PB_QC_TEST_START_LF_ST,
	PB_QC_TEST_START_RF_ST,
	PB_QC_TEST_START_ALL_ST,
	PB_QC_TEST_START_BS_ST,
	PB_QC_TEST_START_FLASH_ST,

	PB_QC_TEST_RESULT_SUCCESS_BUTTON_ST,
	PB_QC_TEST_RESULT_SUCCESS_LCD_ST,
	PB_QC_TEST_RESULT_SUCCESS_MOT_ST,
	PB_QC_TEST_RESULT_SUCCESS_ACC_ST,
	PB_QC_TEST_RESULT_SUCCESS_LF_ST,
	PB_QC_TEST_RESULT_SUCCESS_RF_ST,
	PB_QC_TEST_RESULT_SUCCESS_ALL_ST,
	PB_QC_TEST_RESULT_SUCCESS_BS_ST,
	PB_QC_TEST_RESULT_SUCCESS_FLASH_ST,

	PB_QC_TEST_RESULT_FAIL_BUTTON_ST,
	PB_QC_TEST_RESULT_FAIL_LCD_ST,
	PB_QC_TEST_RESULT_FAIL_MOT_ST,
	PB_QC_TEST_RESULT_FAIL_ACC_ST,
	PB_QC_TEST_RESULT_FAIL_LF_ST,
	PB_QC_TEST_RESULT_FAIL_RF_ST,
	PB_QC_TEST_RESULT_FAIL_ALL_ST,
	PB_QC_TEST_RESULT_FAIL_BS_ST,
	PB_QC_TEST_RESULT_FAIL_FLASH_ST,

	PB_QC_TEST_END_ST,
};

enum
{
	PB_TEST_MSG_TEST1_ST = 0,
	PB_TEST_MSG_TEST2_ST,
};

enum
{
	PB_SMART_CAR_TALK_ALARM_ST = 0,
	PB_SMART_CAR_TALK_DATA_EVT_ST,
	PB_SMART_CAR_ACC_CHECK_EVT_ST,
};

//PB KeyChange Event State
enum
{
	PB_DOUBLE_TAP_EVT_ST = 0,
	PB_SINGLE_TAP_EVT_ST,
	PB_SHORT_KEY_EVT_ST,
	PB_LONG_KEY_EVT_ST,
};

//PB Battery Event State
enum
{
	PB_BATT_END_EVT_ST = 0,
	PB_BATT_CHR_EVT_ST,
};

//PB Time Event State
enum
{
	PB_CLOCK_EVT_ST = 0,
	PB_LCD_TIMEOUT_EVT_ST,
	PB_AFE_EQZ_EVT_ST,
	PB_AFE_NO_SIG_EVT_ST,
	PB_AFE_ERROR_ST,
};

//PB BLE Event State
enum
{
	PB_BLE_NOTI_EVT_ST = 0,
	PB_BLE_NOTI_EVT_SMS_ST,
	PB_BLE_NOTI_EVT_MMS_ST,
	PB_BLE_NOTI_EVT_CALL_ST,
	PB_BLE_MSG_TIMESYNC,
	PB_BLE_REG_EVT,
	PB_BLE_TEST_MSG,

	PB_BLE_CONNECTION_EVT_ST,
	PB_BLE_DISCONNECTION_EVT_ST,
	PB_BLE_PACKET_REV_EVT_ST,
	PB_BLE_ACTIVITY_SEND_FAIL_EVT_ST,

	PB_BLE_SMART_CT_DATA_SEND_EVT_ST,

};

enum
{
	PB_BLE_CONTROL_PNIP_START_ST,
	PB_BLE_CONTROL_PNIP_STOP_ST,
	PB_BLE_TIMEOUT_ST,
	PB_BLE_ACTIVITY_SEND_TIMEOUT_ST,
	PB_BLE_REFRESH,
};

//PB AFE Event State
enum
{
	PB_AFE_CHECK_STATE_IDLE = 0x00,
	PB_AFE_CHECK_STATE_ON,
	PB_AFE_CHECK_PERIOD_ST,
	PB_AFE_CHECK_DURATION_ST,
};

//PB Alarm Event State
enum
{
	PB_ALARM_SYNC_START_ST = 0x00,
	PB_ALARM_SYNC_END_ST,
	PB_ALARM_CHECK_DISPLAY_ST,
	PB_ALARM_DATA_REV_ST,
};

//PB LF Event State
enum
{
	PB_LF_IO_INT_EVT_ST = 0,
	PB_LF_DATA_EVT_ST,
	SESSION_TIMEOUT_EVT,
};

//PB PNIP Event State
enum
{
	PB_PNIP_TIMEOUT_EVT = 0,
	PB_PNIP_SESSION_START,
	PB_PNIP_SESSION_TIMEOUT,
	PB_PNIP_SESSION_REFRESH,
};

//PB ACTIVITY Event State
enum
{
	PB_ACTIVITY_BLOOD_PRESURE = 0,
	PB_ACTIVITY_WEIGHT,
	PB_ACTIVITY_GLUCOSE,
	PB_ACTIVITY_MEDICATION,
	PB_ACTIVITY_ENTERANCE,
	PB_ACTIVITY_STOVE,
	PB_ACTIVITY_FITNESS,
	PB_ACTIVITY_FITNESS_MULTIUSER,
	PB_ACTIVITY_COFFEE,
	PB_ACTIVITY_PEDOMETER,
	PB_ACTIVITY_BODYFAT,
	PB_ACTIVITY_SPO2,
	PB_ACTIVITY_DRIVE_INFO,

	PB_ACTIVITY_STYLEX,
};

// PB Glucose Event State
enum
{
	PB_GLUCOSE_UART_WAKEUP_EVT_ST = 0,
	PB_GLUCOSE_UART_RX_EVT_ST,
	PB_GLUCOSE_UART_TX_EVT_ST,

	PB_GLUCOSE_DISPLAY_MEALS_SELECT_EVT,
	PB_GLUCOSE_DISPLAY_TEMP_CHECK_EVT,
	PB_GLUCOSE_DISPLAY_STRIP_CODE,
	PB_GLUCOSE_DISPLAY_WAIT_BLOOD_DROP_EVT,
	PB_GLUCOSE_DISPLAY_COUNT_1_EVT,
	PB_GLUCOSE_DISPLAY_COUNT_2_EVT,
	PB_GLUCOSE_DISPLAY_COUNT_3_EVT,
	PB_GLUCOSE_DISPLAY_COUNT_4_EVT,
	PB_GLUCOSE_DISPLAY_COUNT_5_EVT,
	PB_GLUCOSE_DISPLAY_RESULT_EVT,
	PB_GLUCOSE_DISPLAY_END_EVT,

	//TEST
	PB_GLUCOSE_DISPLAY_ADC,
	PB_GLUCOSE_DISPLAY_TEMP,

	PB_GLUCOSE_DISPLAY_ERROR_START,
	PB_GLUCOSE_DISPLAY_ERROR_USED_STRIP,
	PB_GLUCOSE_DISPLAY_ERROR_TEMPERATURE,
	PB_GLUCOSE_DISPLAY_ERROR_BLOOD_AMOUNT,
	PB_GLUCOSE_DISPLAY_ERROR_RES_HI,
	PB_GLUCOSE_DISPLAY_ERROR_RES_LO,
	PB_GLUCOSE_DISPLAY_ERROR_TIMEOUT,
	PB_GLUCOSE_DISPLAY_ERROR_STRIP_OUT_STATE,
	PB_GLUCOSE_DISPLAY_ERROR_INVALID_STATE,
	PB_GLUCOSE_DISPLAY_ERROR_INJECT,
	PB_GLUCOSE_DISPLAY_ERROR_MSG_ERROR,
	PB_GLUCOSE_DISPLAY_ERROR_ADC_ERROR,
	UART_MSG_DATA_ERROR_STATE_OUT,
	PB_GLUCOSE_DISPLAY_ERROR_STRIP_CODE,
};

enum {
	PB_PEDOMETER_STEP_ST,
};
typedef struct {
	uint64_t afe_sum;
	uint32_t afe_count;
}pb_afe_save;

typedef struct
{
	uint8_t event;
	uint8_t status;
	uint8_t* msg;
}pbMainEvt_t;

#define PB_ACTIVITY_PACKET_SIZE			19

#define PB_ACTIVITY_DATA_SIZE 			32

#define PB_PACKET_TYPE_M2M					0x88
#define PB_PACKET_TYPE_PNIP_BAND			0x40

#define PB_ACTI_DATA_INDEX_SERVICE_ID		0
#define PB_ACTI_DATA_INDEX_LENGTH			1
#define PB_ACTI_DATA_INDEX_CMD				2
#define PB_ACTI_DATA_INDEX_BOUNDARY			30

#define PB_ACTI_DATA_PADDING_PATTERN		0x00
#define PB_ACTI_DATA_BOUNDARY_PATTERN		0xB5A0

#define PB_ACTI_DATA_SIZE					32
#define PB_ACTI_DATA_FLASH_PAGE_SIZE		256
#define PB_ACTI_NUM_TEMP_DATA				8
#define PB_ACTI_DATA_NUM_TEMP_BUFFER		PB_ACTI_DATA_FLASH_PAGE_SIZE/PB_ACTI_DATA_SIZE //8
#define MAX_ACTIVITY_FLASH_PAGE				250

#define PB_SCHDULE_DATA_SIZE				44
#define PB_SCHDULE_DATA_FLASH_UNIT_SIZE		64
#define PB_SCH_DATA_BOUNDARY_PATTERN_SIZE	2
#define PB_SCH_DATA_BOUNDARY_PATTERN_H		0xB5
#define PB_SCH_DATA_BOUNDARY_PATTERN_L		0xA0

#define PB_ACTIVITY_MSG_TIME_SIZE		0x0C
#define PB_ACTIVITY_MSG_CMD				0x03

#define PB_SERVICE_ID_SCHEDULE			0x31
#define PB_SERVICE_ID_TIMESYNC			0xFF
#define PB_SERVICE_ID_REGISTRATION		0xE1

//test_code
#define PB_SERVICE_ID_TEST				0xE3
#define PB_SERVICE_ID_PAAR_TAG			0x22

#define PB_SERVICE_ID_BIO_SETTING		0xE2

#define PB_SERVICE_ID_CALL_NOTI			0x09
#define PB_SERVICE_ID_ACTIVITY			0x2F
#define PB_SERVICE_ID_FITNESS			0x07//LEXCO
#define PB_SERVICE_ID_SESSION			0xF0
#define PB_SERVICE_ID_BODYFAT			0x0D


//test smart car talk
#define PB_SERVICE_ID_SMART_CAR_TALK	0x52

#define PB_SERVICE_CMD_SMART_CT_STREAMING_REQ		0x01

#define PB_SERVICE_CMD_SMART_CT_STREAMING_DAT		0x02

#define PB_SERVICE_CMD_SMART_CT_ALARM				0x03

#define PB_SERVICE_CMD_SMART_CT_STREAMING_STOP_REQ	0x04


#define PB_ACTIVITY_ID_BLOOD_PRESURE	0x01
#define PB_ACTIVITY_ID_WEIGHT			0x02
#define PB_ACTIVITY_ID_GLUCOSE			0x03
#define PB_ACTIVITY_ID_MEDICATION		0x04
#define PB_ACTIVITY_ID_ENTERANCE		0x05
#define PB_ACTIVITY_ID_STOVE			0x06
#define PB_ACTIVITY_ID_FITNESS			0x07//LEXCO
#define PB_ACTIVITY_ID_COFFEE			0x0B
#define PB_ACTIVITY_ID_PEDOMETER		0x0C
#define PB_ACTIVITY_ID_BODYFAT			0x0D
#define PB_ACTIVITY_ID_SPO2				0x0E



#define DEFAULT_LOCATION_ADDR0		0x00
#define DEFAULT_LOCATION_ADDR1		0x00
#define DEFAULT_LOCATION_ADDR2		0x00
#define DEFAULT_LOCATION_ADDR3		0x00
#define ACTIVITY_PACKET_SAVE_HEADER_LEN		3

//test_code
#define PB_ACTIVITY_ID_SPO2_HR			0x0E

#define PB_ACTIVITY_ID_DRIVE_INFO		0x51

#define PB_ACTIVITY_ID_STYLEX_Q			0x10

#define PB_ACTIVITY_PACKET_SIZE			19

typedef struct {
	uint8_t data[PB_ACTIVITY_DATA_SIZE];
}activity_msg;

#define PB_BLE_PACKET_SIZE 19

typedef struct {
	uint8_t data[PB_BLE_PACKET_SIZE];
}ble_packet_msg;

#define PB_LEXCO_PRECONFIG_DATA_SIZE	32

typedef struct {
	uint8_t data[PB_LEXCO_PRECONFIG_DATA_SIZE];
}lexco_preconfig_msg;

typedef struct
{
	bool is_qc_completed;
	uint8_t pb_paar_id[4];
	uint8_t is_font_download;
}pbQC_t;

typedef struct
{
	uint8_t cmd;
	uint8_t seq;
	uint16_t year;

	uint8_t mon;
	uint8_t day;
	uint8_t hour;
	uint8_t min;

	uint8_t sec;
	uint8_t preAlarm;
	uint8_t weeklyRepeat;
	uint8_t method;

	uint8_t snooze;
	uint8_t reserved[2];
	uint8_t alarmFlags;

	uint8_t infoStr[28];

}pbSchedule_t;

#define PB_SCH_SNOOZE_5MIN		0x02
#define PB_SCH_SNOOZE_10MIN		0x01

typedef struct
{
	uint8_t test_data[10];// unit : ms
}qc_flash_test_t;

typedef struct
{
	uint32_t Save_period;// unit : ms
	uint32_t Save_duration;//unit : ms
	uint8_t Enabled;
}pbBioSave_conf_t;

typedef struct
{
	uint8_t user_id[8];// unit : ms
	uint8_t start_hour;//unit : ms
	uint8_t start_min;
	uint8_t duration_hour;
	uint8_t duration_min;
	uint8_t weakly_repeat;
}pbHealthsetting_conf_t;

enum {
	I2C_MUX_ISR_CH0_ENABLED = 0x01,
	I2C_MUX_ISR_CH1_ENABLED,
	I2C_MUX_ISR_CH0CH1_ENABLED,
	I2C_MUX_ISR_NO_ENABLED,
};

/*********************************************************************
 * @fn      PB_Activity_flash_save
 *
 * @brief
 *
 * @param   None.
 *
 * @return  None.
 */
int PB_Activity_flash_save(uint8_t* buf);

/*********************************************************************
 * @fn      PB_init_activity_flash
 *
 * @brief
 *
 * @param   None.
 *
 * @return  None.
 */
int PB_init_Activity_flash();

int PB_init_Schedule_flash();
int PB_Schedule_flash_save(uint8_t* buf, uint8_t index);
int PB_Schedule_flash_delete(uint8_t index);
bool PB_Schedule_flash_read(pbSchedule_t* schedule_buf, uint8_t* boundary, uint16_t index);
int PB_GetSchedule_avail();

bool PB_Activity_flash_read(activity_msg* activity_buf, uint32_t count);
uint16_t get_current_activity_count();

bool PB_BioSaveConf_init();
bool PB_BioSaveConf_flash_write(pbBioSave_conf_t bio_save_conf);
bool PB_BioSaveConf_flash_read(pbBioSave_conf_t* bio_save_conf);

uint8_t get_AFE_save_state();
void add_AFE_HR_data(uint32_t HR_data);

void PB_PAARBand_Main_init();

void LFwakeup_pin_enable();
void LFwakeup_pin_disable();
uint8_t get_main_task_init_ready();

void PB_set_time(uint16_t year, uint8_t mon, uint8_t day, uint8_t hours, uint8_t min, uint8_t sec);
void PB_set_time_nopedo(uint16_t year, uint8_t mon, uint8_t day, uint8_t hours, uint8_t min, uint8_t sec);

uint16_t check_battery_voltage();

sem_pt get_bs_tx_evt_sem();

int save_activity_data(activity_msg* activity_data);

void PB_NXP_Uart_Trx_enable();
void PB_NXP_Uart_Trx_disable();

void PB_BS_GPIO_ENABLE();

void g_enable_init();

void PB_START_SMART_CT(uint16_t service_period);
void PB_STOP_SMART_CT();

void PB_START_SMART_CT_ACC_TEST();
void PB_STOP_SMART_CT_ACC_TEST();

bool PB_is_qc_complete();
pbQC_t get_PB_current_qc_info();

void PB_stop_BS_stable_timer();

uint8_t PB_Main_event_send(uint8_t Main_evt, uint8_t Main_evt_state, uint8_t* msg);

void PB_QC_conf_set(bool is_qc_comp, uint8_t paar_id0, uint8_t paar_id1, uint8_t paar_id2, uint8_t paar_id3, bool is_font_download, bool is_flash_write);
bool PB_QC_flash_test_init();
bool PB_QC_flash_test_flash_write();
bool PB_QC_flash_test_flash_read();

void PB_QC_conf_end_save();

void set_qc_test_all_enable(bool val);
bool get_qc_test_all_enable();

void set_qc_test_bs_enable(bool val, uint16_t min, uint16_t max);
bool get_qc_test_bs_enable();
bool check_qc_test_bs(uint16_t val);

//static void PB_wdt_refresh_handler(); yangsong modify
void PB_wdt_refresh_handler();


#endif /* APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PAARBAND_MAIN_H_ */

