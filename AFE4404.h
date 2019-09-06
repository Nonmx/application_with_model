/*
 * AFE4404.h
 *
 *  Created on: 2016. 6. 16.
 *      Author: Administrator
 */

#ifndef APPLICATION_PAARBAND_EXE_PAARBAND_SRC_AFE4404_H_
#define APPLICATION_PAARBAND_EXE_PAARBAND_SRC_AFE4404_H_

#ifndef KERNEL_DRIVER_LIB_AFE4404_ITF_LIB_AFE4404_H_
#define KERNEL_DRIVER_LIB_AFE4404_ITF_LIB_AFE4404_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "os.h"

#ifndef AFE4404_H_
#define AFE4404_H_

#define	USE_UI		0
#define AFE4404_TASK_STACK_SIZE 	512

 /*
  * LED1(GREEN)
  * LED2(RED)
  * LED3(IR)
  */
  /*Slave Address*/
#define AFE4404_Addr	0x58

/*Register Address*/
#define CONTROL0		0x00 //(W)
#define		REG_READ		0x01 //Enables the readout of write registers
#define 	TM_COUNT_RST	0x02 //Used to suspend the count and keep the counter in a reset state.
#define 	DIAG_EN			0x04 //Diagonostic mode enable
#define 	SW_RESET		0x08

#define LED2STC			0x01 //(R/W)15-0bit Sample LED2 start

#define LED2ENDC		0x02 //(R/W)15-0bit Sample LED2 end

#define LED1LEDSTC		0x03 //(R/W)15-0bit LED1 start

#define LED1LEDENDC		0x04 //(R/W)15-0bit LED1 end

#define ALED2STC		0x05 //(R/W)15-0bit Sample ambient 2(or sample LED3) start

#define ALED2ENDC		0x06 //(R/W)15-0bit Sample ambient 2(or sample LED3) end

#define	LED1STC			0x07 //(R/W)15-0bit Sample LED1 start

#define LED1ENDC		0x08 //(R/W)15-0bit Sample LED1 end

#define LED2LEDSTC		0x09 //(R/W)15-0bit LED2 start

#define LED2LEDENDC		0x0A //(R/W)15-0bit LED2 end

#define ALED1STC		0x0B //(R/W)15-0bit Sample ambient 1 start

#define ALED1ENDC		0x0C //(R/W)15-0bit Sample ambient 1 end

#define LED2CONVST		0x0D //(R/W)15-0bit LED2 convert phase start

#define LED2CONVEND		0x0E //(R/W)15-0bit LED2 convert phase end

#define ALED2CONVST		0x0F //(R/W)15-0bit Ambient 2(or LED3) convert phase start

#define ALED2CONVEND	0x10 //(R/W)15-0bit Ambient 2(or LED3) convert phase end

#define LED1CONVST		0x11 //(R/W)15-0bit LED1 convert phase start

#define LED1CONVEND		0x12 //(R/W)15-0bit LED1 convert phase end

#define ALED1CONVST		0x13 //(R/W)15-0bit Ambient 1 convert phase start

#define ALED1CONVEND	0x14 //(R/W)15-0bit Ambient 1 convert phase end

#define ADCRSTSTCT0		0x15 //(R/W)15-0bit ADC reset phase 0 start

#define ADCRSTENDCT0	0x16 //(R/W)15-0bit ADC reset phase 0 end

#define ADCRSTSTCT1		0x17 //(R/W)15-0bit ADC reset phase 1 start

#define ADCRSTENDCT1	0x18 //(R/W)15-0bit ADC reset phase 1 end

#define ADCRSTSTCT2		0x19 //(R/W)15-0bit ADC reset phase 2 start

#define ADCRSTENDCT2	0x1A //(R/W)15-0bit ADC reset phase 2 end

#define ADCRSTSTCT3		0x1B //(R/W)15-0bit ADC reset phase 3 start

#define ADCRSTENDCT3	0x1C //(R/W)15-0bit ADC reset phase 3 end

#define PRPCT			0x1D //(R/W)15-0bit The count value for the counter that sets the PRF
//				Counter automatically  counts until PRPCT and then
//				back to 0 to start the next count

#define CONTROL1		0x1E //(R/W)8bit & 3-0bit
//NUMAV : Determine the number of AC averages (NUMAV + 1)
#define		NUMAV0			0x00
#define		NUMAV1			0x01
#define 	NUMAV2			0x02
#define 	NUMAV3			0x03
#define 	NUMAV4			0x04
#define 	NUMAV5			0x05
#define		NUMAV6			0x06
#define 	NUMAV7			0x07
#define		NUMAV8			0x08
#define 	NUMAV9			0x09
#define 	NUMAV10			0x0A
#define 	NUMAV11			0x0B
#define 	NUMAV12			0x0C
#define 	NUMAV13			0x0D
#define 	NUMAV14			0x0E
#define 	NUMAV15			0x0F
//TIMEREN
#define 	TIMERDIS		0b0<<8
#define 	TIMEREN			0b1<<8

#define TIAGAIN			0x20 //(R/W)15bit & 5-0bit
//ENSEPGAIN
#define DISSEPGAIN			0b0<<15
#define ENSEPGAIN			0b1<<15
//TIA_CF_SEP
#define TIA_CF_SEP_5pF		0b000<<3
#define TIA_CF_SEP_2_5pF	0b001<<3
#define TIA_CF_SEP_10pF		0b010<<3
#define TIA_CF_SEP_7_5pF	0b011<<3
#define TIA_CF_SEP_20pF		0b100<<3
#define TIA_CF_SEP_17_5pF	0b101<<3
#define TIA_CF_SEP_25pF		0b110<<3
#define TIA_CF_SEP_22_5pF	0b111<<3
//TIA_GAIN_SEP
#define TIA_GAIN_SEP_500k	0b000
#define TIA_GAIN_SEP_250k	0b001
#define TIA_GAIN_SEP_100k	0b010
#define TIA_GAIN_SEP_50k	0b011
#define TIA_GAIN_SEP_25k	0b100
#define TIA_GAIN_SEP_10k	0b101
#define TIA_GAIN_SEP_1M		0b110
#define TIA_GAIN_SEP_2M		0b111

#define TIA_AMP_GAIN	0x21 //(R/W)5-0bit
//TIA_CF
#define TIA_CF_5pF		0b000<<3
#define TIA_CF_2_5pF	0b001<<3
#define TIA_CF_10pF		0b010<<3
#define TIA_CF_7_5pF	0b011<<3
#define TIA_CF_20pF		0b100<<3
#define TIA_CF_17_5pF	0b101<<3
#define TIA_CF_25pF		0b110<<3
#define TIA_CF_22_5pF	0b111<<3
//TIA_GAIN
#define TIA_GAIN_500k	0b000
#define TIA_GAIN_250k	0b001
#define TIA_GAIN_100k	0b010
#define TIA_GAIN_50k	0b011
#define TIA_GAIN_25k	0b100
#define TIA_GAIN_10k	0b101
#define TIA_GAIN_1M		0b110
#define TIA_GAIN_2M		0b111

#define LEDCNTRL		0x22 //(R/W)17-0bit
//ILED1 : LED1 current control (5-0bit)
//ILED2 : LED2 current control (11-6bit)
//IRLE3 : LED3 current control (17-12bit)

#define CONTROL2		0x23
#define		PDNAFE			0b1<<0 //Entire AFE is powered down
#define 	PDNRX			0b1<<1 //RX portion of the AFE is powered down

#define 	DYNAMIC4		0b1<<3 //Rest of ADC is powered down in dynamic power-down mode
#define 	DYNAMIC3		0b1<<4 //TIA is powered down in dynamic power-down mode

#define		EXTERN_ENABLE	0b0<<9 //External clock mode(default)
#define 	OSC_ENABLE		0b1<<9 //Enables oscillator mode(4-MHz internal oscillator)

#define 	DYNAMIC2		0b1<<14//ADC is powered down in dynamic power-down mode

#define		ILED_2X_DIS		0b0<<17//LED current range is 0mA to 50mA
#define 	ILED_2X_EN		0b1<<17//LED current range is 0mA to 100mA

#define 	DYNAMIC1		0b1<<20//Transmitter is powered down in dynamic power-down mode

#define CLKDIV1			0x29 //(R/W)9bit & 4-1bit
#define 	ENABLE_CLKOUT		0b1<<9 //Enables CLKOUT generation and buffering on the CLK pin

#define 	CLKDIV_CLKOUT_1		0b0000<<1//4MHz
#define 	CLKDIV_CLKOUT_2		0b0001<<1//2MHz
#define 	CLKDIV_CLKOUT_4		0b0010<<1//1MHz
#define 	CLKDIV_CLKOUT_8		0b0011<<1//0.5MHz
#define 	CLKDIV_CLKOUT_16	0b0100<<1//0.25MHz
#define 	CLKDIV_CLKOUT_32	0b0101<<1//0.125MHz
#define		CLKDIV_CLKOUT_64	0b0110<<1//0.0624MHz
#define 	CLKDIV_CLKOUT_128	0b0111<<1//0.03125MHz

#define	LED2VAL			0x2A //(R) LED2 output code in 24bit, twos complement format

#define ALED2VAL		0x2B //(R) Ambient2(or LED3) output code in 24bit, twos complement format

#define LED1VAL			0x2C //(R) LED1 output code in 24bit, twos complement format

#define	ALED1VAL		0x2D //(R) Ambient1 output code in 24bit, twos complement format

#define LED2_ALED2VAL	0x2E //(R) LED2-Ambient2 output code in 24bit, twos complement format

#define	LED1_ALED1VAL	0x2F //(R) LED1-Ambient1 output code in 24bit, twos complement format

#define CONTROL3		0x31
#define 	CLKDIV_EXTMODE_1	0b101<<0//4-6MHz
#define 	CLKDIV_EXTMODE_2	0b000<<0//8-12MHz
#define		CLKDIV_EXTMODE_4	0b100<<0//16-24MHz
#define 	CLKDIV_EXTMODE_6	0b110<<0//24-36MHz
#define		CLKDIV_EXTMODE_8	0b001<<0//32-48MHz
#define 	CLKDIV_EXTMODE_12	0b011<<0//48-60MHz

#define		ENABLE_INPUT_SHORT	0b1<<5	//INP, INN are shorted to VCM whenever the TIA is in powerdown

#define		PD_DISCONNECT		0b1<<10	//Disconnects the PD signals (INP, INN) from the TIA inputs

#define PDNCYCLEST		0x32 //(R/W)15-0bit PDN_CYCLE start

#define PDNCYCLEEND		0x33 //(R/W)15-0bit	PDN_CYCLE end

#define PROG_TG_STC		0x34 //(R/W)15-0bit Start time for programmable timing engine signal

#define	PROG_TG_ENDC	0x35 //(R/W)15-0bit End time for programmable timing engine signal

#define LED3LEDSTC		0x36 //(R/W)15-0bit LED3 start

#define LED3LEDENDC		0x37 //(R/W)15-0bit LED3 end

#define	CLKDIV2			0x39 //(R/W)2-0bit Clock division ratio for the clock to the timing engine
#define		CLKDIV_PRF_1		0b000<<0
#define		CLKDIV_PRF_2		0b100<<0
#define		CLKDIV_PRF_4		0b101<<0
#define		CLKDIV_PRF_8		0b110<<0
#define		CLKDIV_PRF_16		0b111<<0

#define	OFFDAC			0x3A //(R/W)19-0bit Offset cancellation DAC

extern uint32_t raw_data; // SPO2 sampling real-data

//2015.11.20 cms
#define PRF	100 //sampling frequency 100Hz

//extern int HR_value; // HR value
extern int HR_output;
extern uint8_t EQZ_value;

/*
 * AFE4404 �ʱ�ȭ�ϴ� �Լ�
 *
 * TI���� �������ִ� AFE4404 EVM GUI���� ����ϴ� �⺻ ������ �������Ͱ� ����
 * TIMING CLOCK 4MHz
 */
 //extern void AFE4404_Init(void);

 /*
  * AFE4404 TIMING CLOCK 250KHz�� �ʱ�ȭ �ϴ� �Լ�
  */
void AFE4404_Init_DIV16(void);

/*
 * AFE4404 hardware-powerdown ���� �����ϴ� �Լ�
 *
 * RESETZ pin�� ���¸� low�� 200usec�̻� �����ϸ� hardware-powerdown ���� �����Ѵ�
 */
void AFE4404_HW_PWDN(void);

/*
 * AFE4404 LED ���� ���� �Լ�
 *
 * ��LED���� ���ð����� �� 0b00000000~0b00111111
 *
 * @param	LED_Green	green LED�� �帣�� ������ ����
 *
 * @param	LED_Red		red LED�� �帣�� ������ ����
 *
 * @param	LED_IR		IR LED�� �帣�� ������ ����
 */
extern void AFE4404_LED_Set(uint8_t LED_Green, uint8_t LED_Red, uint8_t LED_IR);

/*
 * AFE4404 Timer ���� �Լ�
 *
 * �� �Լ��� ����Ǿ� AFE4404�� ������ ������.
 */
extern void AFE4404_Timer_EN(void);

extern void AFE4404_Timer_DIS(void);

//void AFE4404_HR(uint32_t sample, int* heart_rate);

extern void PB_PulseTask_int(void);


extern void AFE4404_Interface_Init(void);

extern void Board_AFE4404_Enable(bool val);

extern void Board_AFE4404_ISR_Enable(uint8_t val);

extern void Board_AFE4404_Enable_test();

extern void AEF4404_ADC_RDY_pin_init(uint8_t option);

uint8_t get_EQZ_value();
int get_HR_output();
int get_HR_value();
int get_HR_str();

extern void PB_AFE_flag_enable(bool enable);

extern bool get_AFE_init_state();

mutex_pt get_AFE_gate_handle();

//test_code
#define AFE4404_NOT_DISABLE		0

enum {
	button_OFF_State = 0,
	button_OFF_SMOOTH_State,
	button_ON_State
};

void set_ui_afe_enable(bool enable);
void set_smart_ct_service_enable(bool enable);

bool get_smart_ct_service_enable();

//extern uint8_t button_flag;
uint8_t button_flag;
//extern I2C_Handle pbI2cHandle;
//extern I2C_Transaction pbI2C_Transaction;
//extern Semaphore_Handle hI2C_sem;

//test_code : AFE_save
enum {
	AFE_FUNC_ENABLE = 0x00,
	AFE_FUNC_DISABLE,
};

void AFE4404_FUNC_ENABLE(uint8_t enable);

#endif
#endif /* KERNEL_DRIVER_LIB_AFE4404_ITF_LIB_AFE4404_H_ */

static void ADC_RDY_Callback(uint32_t pin, uint32_t action);

#endif /* APPLICATION_PAARBAND_EXE_PAARBAND_SRC_AFE4404_H_ */
