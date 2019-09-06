/*
 * hw_config.h
 *
 *  Created on: 2016. 4. 15.
 *      Author: geoyun
 */

#ifndef KERNEL_DRIVER_ITF_PAARBAND_ITF_HW_CONFIG_H_
#define KERNEL_DRIVER_ITF_PAARBAND_ITF_HW_CONFIG_H_


 //enum{
 //	PB_BOARD_HW_VERSION_2_0_0_LF = 0,
 //	PB_BOARD_HW_VERSION_2_0_0_BS,
 //	PB_BOARD_HW_VERSION_2_0_1_LF,
 //	PB_BOARD_HW_VERSION_2_0_1_BS,
 //
 //};

#define PB_BOARD_HW_VERSION_2_0_0_LF	0
#define PB_BOARD_HW_VERSION_2_0_0_BS	1

#define PB_BOARD_HW_VERSION_2_0_1_LF	2
#define PB_BOARD_HW_VERSION_2_0_1_BS	3


//PB HW Version Setting
#define BOARD_HW_VERSION			PB_BOARD_HW_VERSION_2_0_1_BS

#if(BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_LF || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_0_BS)

//Board Xtal
#define BOARD_PIN_XL1						0
#define BOARD_PIN_XL2						1

//PB Battery ADC Enable - Level
#define BOARD_PIN_BAT_ADC_LV				2
#define BOARD_PIN_BAT_ADC_EN				3

//PB Battery Charge Interrupt
#define BOARD_PIN_CHARGE_ST_INT				4

//PB Sub Board Uart Interface
#define BOARD_PIN_MCU_TX_SUB_RX				5
#define BOARD_PIN_MCU_RX_SUB_TX				6

//PB External - RTC - SPO2 I2C Interface
#define BOARD_PIN_EXT_RTC_SPO2_I2C_SCL		7
#define BOARD_PIN_EXT_RTC_SPO2_I2C_SDA		8

//PB External I/O Interrupt
#define BOARD_PIN_EXT_INT					9

//PB AFE4404(SPO2) Interrupt
#define BOARD_PIN_SPO2_INT_ADC_RDY			10

//PB Sub Board Power Control
#define BOARD_PIN_SUB_PWR					11

//PB AFE4404(SPO2) Power Control
#define BOARD_PIN_SPO2_PWR					12

//PB Motor I/O
#define BOARD_PIN_MOTOR_PWR					13

//PB LCD Interface
#define BOARD_PIN_LCD_PWR					14
#define BOARD_PIN_LCD_SPI_MISO				15
#define BOARD_PIN_LCD_SPI_MOSI				16
#define BOARD_PIN_LCD_SPI_SCK				17
#define BOARD_PIN_LCD_SPI_CS				18
#define BOARD_PIN_LCD_IO_RESET				19
#define BOARD_PIN_LCD_IO_A0					20

//Debug Reset
#define BOARD_PIN_DBG_NRESET				21

//PB Button Interrupt
#define BOARD_PIN_BUTTON_INT				22

//PB Sub Board I/O Interface(LF - Blood Sugar)
#define BOARD_PIN_SUB_IO_IN					23
#define BOARD_PIN_SUB_IO_OUT				24

//PB External Flash - BMI160 SPI Interface
#define BOARD_PIN_FLASH_ACCEL_SPI_MISO		25
#define BOARD_PIN_FLASH_ACCEL_SPI_MOSI		26
#define BOARD_PIN_FLASH_ACCEL_SPI_SCK		27

//PB External Flash
#define BOARD_PIN_FLASH_SPI_CS				28

//PB BMI160 Accel
#define BOARD_PIN_ACCEL_SPI_CS				29
#define BOARD_PIN_ACCEL_INT1				30
#define BOARD_PIN_ACCEL_INT2				31

#elif(BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_LF || BOARD_HW_VERSION == PB_BOARD_HW_VERSION_2_0_1_BS)

//Board Xtal
#define BOARD_PIN_XL1							0
#define BOARD_PIN_XL2							1

//PB Battery ADC Enable - Level
#define BOARD_PIN_BAT_ADC_LV					2
#define BOARD_PIN_BAT_ADC_EN					3

//PB Battery Charge Interrupt
#define BOARD_PIN_CHARGE_ST_INT					4

//PB Sub Board Uart Interface
#define BOARD_PIN_MCU_TX_SUB_RX					5
#define BOARD_PIN_MCU_RX_SUB_TX					6

//PB External - RTC - SPO2 I2C Interface
#define BOARD_PIN_EXT_RTC_SPO2_I2C_SCL			7
#define BOARD_PIN_EXT_RTC_SPO2_I2C_SDA			8

#define BOARD_PIN_NFC1							9
#define BOARD_PIN_NFC2							10

//PB Sub Board Power Control
#define BOARD_PIN_SUB_PWR						11

//PB AFE4404(SPO2) Power Control
#define BOARD_PIN_SPO2_PWR						12

//PB Motor I/O
#define BOARD_PIN_MOTOR_PWR						13

//PB LCD Interface
#define BOARD_PIN_LCD_PWR						14

#define BOARD_PIN_EXT_INT						15
#define BOARD_PIN_SPO2_INT_ADC_RDY				16
#define BOARD_PIN_RTC_INT						17

#define BOARD_PIN_LCD_SPI_CS					18
#define BOARD_PIN_LCD_IO_RESET					19
#define BOARD_PIN_LCD_IO_A0						20

//Debug Reset
#define BOARD_PIN_DBG_NRESET					21

//PB Button Interrupt
#define BOARD_PIN_BUTTON_INT					22

//PB Sub Board I/O Interface(LF - Blood Sugar)
#define BOARD_PIN_SUB_IO_IN						23
#define BOARD_PIN_SUB_IO_OUT					24

//PB External Flash - BMI160 SPI Interface
#define BOARD_PIN_LCD_FLASH_ACCEL_SPI_MISO		25
#define BOARD_PIN_LCD_FLASH_ACCEL_SPI_MOSI		26
#define BOARD_PIN_LCD_FLASH_ACCEL_SPI_SCK		27

//PB External Flash
#define BOARD_PIN_FLASH_SPI_CS					28

//PB BMI160 Accel
#define BOARD_PIN_ACCEL_SPI_CS					29
#define BOARD_PIN_ACCEL_INT1					30
#define BOARD_PIN_ACCEL_INT2					31

#endif

#endif /* KERNEL_DRIVER_ITF_PAARBAND_ITF_HW_CONFIG_H_ */
