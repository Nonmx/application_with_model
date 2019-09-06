/*
 * PB_Glucose_uart.h
 *
 *  Created on: 2016. 6. 07.
 *      Author: YeongJune Jeon
 */
#include "stdint.h"

#ifndef APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_GLUCOSE_UART_H_
#define APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_GLUCOSE_UART_H_


 //#define UART_READ_TEMP_SIZE 		23
#define UART_BS_READ_SIZE		16

#define STRIP_CODE_DEFAULT		20
#define STRIP_CODE_MAX			63

typedef enum
{
	_STATE_GLUCOSE_NONE = 0,
	_STATE_GLUCOSE_INIT,
	_STATE_GLUCOSE_SELECT_TIME,					// select the before meal / after meal by user's action(button)
	_STATE_GLUCOSE_CHECK_TIME, 				// confirmed the user's action
	_STATE_GLUCOSE_CHECK_TEMPERATURE, 		// check temperature
	_STATE_GLUCOSE_WAIT_1500MS,    			// set w : 268 mv, D : 268 mv
	_STATE_GLUCOSE_CHECK_USED_STRIP, 			// check used strip
	_STATE_GLUCOSE_CHECK_STRIP_CODE,
	_STATE_GLUCOSE_BLOOD_DROP_READY,
	_STATE_GLUCOSE_BLOOD_DROP,				// blink blood icon and wait blood injection
	_STATE_GLUCOSE_WAIT_900MS,   			// set w : 110 mv, D : 268 mv
	_STATE_GLUCOSE_CHECK_BLOOD_AMOUNT,    					// check enough blood injection
	_STATE_GLUCOSE_DISPLAY_RESULT_WAIT_CNT,		// display 5 and set w : 350 mv, D : 0 mv
	_STATE_GLUCOSE_KEEP_268MV,    			//  Keep 268mV for 0.5sec
	_STATE_GLUCOSE_CALC_RESULT, 				// measure the blood adc for 128 times on the 0.5 sec
	_STATE_GLUCOSE_DISP_RESULT,					// display the blood adc result
	_STATE_GLUCOSE_ERROR,
}GlucoseState;

// GLUCOSE => 2640 & M4 UART MSG

extern uint32_t	g_glucose_state;
extern uint8_t b_glucose_error;

extern uint32_t uart_msg_start_num;

extern uint8_t glucose_strip_code;
extern uint8_t glucose_strip_code_select;

extern uint8_t PB_CodeExist[STRIP_CODE_MAX];

uint8_t adc_value_49[4];
uint8_t temp_value[2];

uint32_t	g_glucose_result_data;

//정의 없다
extern uint8_t g_glucose_result_array[];

typedef struct _glucose_message_data {
	uint8_t startDescriptor;
	uint8_t stx;
	uint8_t type;
	uint8_t data[3];
	uint8_t etx;
	uint8_t endDescriptor;
} GLUCOSE_MDATA;

// todo Glucose Enable �� �� �� �ٸ� �κ��� ������ �ȵǰ� �ϴ� ��.
uint8_t b_Glucose_Strip_Out;
uint8_t b_Glucose_Enable;

void PB_BS_UART_Init();

void PB_Glucose_MainLoop(uint8_t status);

uint32_t PB_UART_Read_Check();
uint32_t PB_UART_Write(uint8_t msg_type, uint8_t value);

uint32_t PB_UART_Read_Loop(uint8_t status, uint8_t* readData);

int UART_send(uint8_t* send_msg, uint8_t msg_len);

void Glucose_Meals_State_Change(uint8_t status);
void PB_Glucose_Go_State_Init();

//int uitoa( int value, uint8_t* buf, uint32_t max) ;

uint8_t get_meal_state();

void test_set_meal_state();

uint8_t get_glucose_state();

void PB_Glucose_Key_Check_State(uint8_t state);

uint32_t get_glucose_result_data();

#endif /* APPLICATION_PAARBAND_EXE_PAARBAND_SRC_PB_GLUCOSE_UART_H_ */
