/*
 * sw_config.h
 *
 *  Created on: 2016. 5. 25.
 *      Author: Administrator
 */

#ifndef APPLICATION_PAARBAND_ITF_PAARBAND_ITF_SW_CONFIG_H_
#define APPLICATION_PAARBAND_ITF_PAARBAND_ITF_SW_CONFIG_H_

#include "hw_config.h"
 //#include "../../../../kernel/porting/bsp_armcortexm_nrf52dk/itf/bsp_option.h"

  //PB External Flash Font Download Enable
#define PB_FONT_DOWNLOAD_ENABLE		0

//PB LCD Timeout Func Enable
#define PB_LCD_TIMEOUT_ENABLE		1

//PB LF(NXP) Func Enable
#define PB_LF_PNIP_ENABLE			0

//PB Blood Sugar Check Enable
#define PB_BS_CHECK_EANBLE			1

#define PB_SW_VERSION_INFO			PB_SW_VERSION_BS_MICO
#define PB_SW_VERSION_BS_ISENS		0
#define PB_SW_VERSION_BS_MICO		1
#define PB_SW_VERSION_LF			2
#define PB_SW_VERSION_BS_MICO_ST	3 //Mico Smart car talk

#define ISENS_TEST_MODE				1		// ISENS_TEST_MODE ( GLUCOSE_DISPLAY_MEASURE DATA )
#define MEALS_SELECT_ON				0		// glucose Meals select on/off
#define BS_KOREAN_VER				0

//PB ACC Tap Func Enable
#define PB_ACC_TAP_ENABLE			0

#define PB_SCHEDULE_ENABLE			1

#define PB_NOTI_ENABLE				1

#define PB_ACTIVITIY_MAX_COUNT		3000

#define PB_ACTIVITY_SAVE_ENALBE 		1

#define PB_DISPLAY_LF_EVT_ENABLE 		1

#define PB_PNIP_SESSION_DISPLAY_ENABLE	1

#define PB_AFE_EQUALIZER_DISPLAY_ENABLE	1

#define BLE_CON_DIS_DISPLAY_ENABLE		0

#define PB_POWER_MANAGER_ENABLE			1

#define PAAR_DEVICE_ID0		0xB4
#define PAAR_DEVICE_ID1		0xA0
#define PAAR_DEVICE_ID2		0xFF
#define PAAR_DEVICE_ID3		0x58

#define PB_QC_FUNC_ENABLE				0

#define PB_QC_INIT_FORCED				0

#endif /* APPLICATION_PAARBAND_ITF_PAARBAND_ITF_SW_CONFIG_H_ */
