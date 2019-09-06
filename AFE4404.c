#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
//#include "os.h"
#include "AFE4404.h"
//ys modify
#include "absconfig.h"
#include "PAARBand_Main.h"
//
#include "UI.h"

extern int scheduler();
//2015.11.20 cms For Heartrate
//#define RAW_MIN 700000 //Raw data min
#define RAW_MIN 400000 //Raw data min
#define RAW_MAX 1300000 //Raw data max
#define MINHR 50
#define MAXHR 150
#define HR_ERROR 130 //HR error value
#define sMIN -9999999 // super min
#define sMAX 9999999 // super max
#define LOWPF 10   // low pass filter
#define HIGHPF 1000 // high pass filter
#define INIT 0   // initial setup data
#define UP 1
#define DOWN 2
#define SKIP 3     // illegal noise data
#define STABLE 20  //read 150 raw data and fix basline
#define NOISE 10   // initial noise range

/****** for PPG wave ***/
#define MINPEAKERROR 400 // minimum threshold between min and max(about 50%)
#define MINRE 15   // minimum number of points within raising edge(10)
#define MINFE 15   // minimum number of points within falling edge(50)

/****** for Smooth State ****/
#define Smooth_INIT		0 //HR_Smooth�� ä���� �ִ� ����
#define Smooth_MAX_OV	1 //HR_Smooth�� MAX�� Overwriting ����
#define Smooth_MIN_OV	2 //HR_Smooth�� MIN�� Overwriting ����
#define Smooth_Ready	3 //HeartRate �����غ� �Ϸ� ����

/****** Data Size ******/
#define	TRANSFER_DATA_SIZE	3

//test_code
#define MIN_HIGHPEAK_DISTANCE		40

#define MAX_NORMAL_EQZ_LEV			10
#define STEP_NORMAL_EQZ_DATA		400

#define CHECK_WEAR_TIMEOUT	100

typedef struct {
	/* High Pass Filter Parameter */
	float A[5];
	float B[5];

	/* Filtered Data */
	float x[5];					///< Original Data
	float y[5];					///< Differentiated data
} butter_filter_t;

enum {
	ADC_RDY_OFF = 0, ADC_RDY_ON
};

int r;

bool PB_ui_afe_enable = false;
bool PB_smart_ct_service_enable = false;
static mutex_pt mutex_AFE;
mutex_pt prms_AFE;
sem_pt hAfe4404Sem;
bool afe4404_enabled = false;
static char test_AFE_enable = false;
uint32_t raw_data = 0;
int HR_value = 0;
int temp_HR_value = 0;
int HR_output = 0;
uint8_t EQZ_value = 0;
int temp_scale_lf_hp = 0;

void PM_fpu_clear();
int32_t Butter_Calculation(butter_filter_t* f, int32_t data);
uint8_t nomarlizedEQZ(int pulsewidth);

static void ADC_RDY_Callback(uint32_t pin, uint32_t action) {
	/* send ADC ready signal to afe4404 task and read data from afe4404's module */
	sem_give(hAfe4404Sem);
}

uint8_t nomarlizedEQZ(int pulsewidth) {
	uint8_t divide_width = 0;

	divide_width = pulsewidth / STEP_NORMAL_EQZ_DATA; //�޽����� 400���� ���� ���� 400������ ���ϴ� ���������� ������ ��Ÿ���� �ִ�.

	if (divide_width > MAX_NORMAL_EQZ_LEV)
		divide_width = MAX_NORMAL_EQZ_LEV;

	return divide_width;
}

int32_t Butter_Calculation(butter_filter_t* f, int32_t data) {
	f->x[0] = (float)data;

	f->y[0] = f->B[0] * (f->x[0]);
	f->y[0] += f->B[1] * (f->x[1]);
	f->y[0] += f->B[2] * (f->x[2]);

	f->y[0] -= f->A[1] * (f->y[1]);
	f->y[0] -= f->A[2] * (f->y[2]);

	f->x[2] = f->x[1];
	f->y[2] = f->y[1];
	f->x[1] = f->x[0];
	f->y[1] = f->y[0];

	return ((int32_t)f->y[0]);
}

void PM_fpu_clear() {}

void set_ui_afe_enable(bool enable) {
	PB_ui_afe_enable = enable;
}

void set_smart_ct_service_enable(bool enable) {
	PB_smart_ct_service_enable = enable;
}

void AFE4404_Interface_Init(void) {
	int r;

	r = sem_create(&hAfe4404Sem);
	if (0 != r) {
#if DEBUG
		printf("fail at hAfe4404Sem's semaphore\n");
#endif
	}

	//	nrf_gpio_cfg_output(BOARD_PIN_SPO2_PWR);

	//	nrf_gpio_pin_set(BOARD_PIN_SPO2_PWR);


		/* configure afe4404's adc interrupt pin
		 * io dircetion : input
		 * */
		 //	nrf_drv_gpiote_in_config_t afe_in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(false);
}


#define JUMP_PB_PulseTask(){\
	switch (current_pc[3])\
	{\
		case 0:\
			goto L_PB_PulseTask_0;break;\
		case 1:\
			goto L_PB_PulseTask_1;break;\
		case 2:\
			goto L_PB_PulseTask_2;break;\
		case 3:\
			goto L_PB_PulseTask_3;break;\
		case 4:\
			goto L_PB_PulseTask_4;break;\
		case 5:\
			goto L_PB_PulseTask_5;break;\
		case 6:\
			goto L_PB_PulseTask_6;break;\
		case 7:\
			goto L_PB_PulseTask_7;break;\
		case 8:\
			goto L_PB_PulseTask_8;break;\
		case 9:\
			goto L_PB_PulseTask_9;break;\
		case 10:\
			goto L_PB_PulseTask_10; break; \
	}\
}
/*=====================PulseTask local var================================*/
uint8_t vRegAddress = 0;
uint8_t writeBuffer[TRANSFER_DATA_SIZE] = { 0, };
uint8_t readBuffer[TRANSFER_DATA_SIZE] = { 0, };

//	AFE4404_LED_Set(0b00000000, 0b00000000, 0b00000000);

	//2015.11.20 cms For Heartrate
unsigned int x = 0;
int sum_y = 0;
int new_y;				// old y, new y , and delta = (newy - oldy);
int lmin_y, lmin_x = 0; //local min peak value and location
int lmax_y, lmax_x = 0; // local max peak value and location
int gmin_x = 0, gmin_y = 0, gmax_x = 0, gmax_y = 0; // global min max
int hrcnt = 0; // heart rate count
int lenRE = MINRE, lenFE = MINFE; // Thresholds for signal value change and frequency
int scale_lp_hp;

int wf = INIT; // wave flag : DOWN : init. mode, UP : raising mode,2:falling mode

int start_point = 0, end_point = 0;

//2015.11.23 cms HR smooth
//	int HR_Smooth[5] = { 0, };
	//test_code
int HR_Smooth[10] = { 0, };

int hr_idx = 0, smooth_flag = 0, hr_sum = 0;
int max_idx = 0, min_idx = 0, loop_idx = 0;
int old_HR_value = 0;

butter_filter_t* lf;
butter_filter_t* hf;

//uint32_t raw_data = 0;
int32_t low_Green = 0;
int32_t filtered_data = 0;

int check_wear = 0;

char wear_enable = 0;
/*========================================================================*/
//static void TASK(3) {//PB_PulseTask
void PB_Pulse()
{
JUMP_PB_PulseTask();
L_PB_PulseTask_0:

	while (get_main_task_init_ready() == 0)
	{
		current_pc[3] = 1;
		// OS
		task_sleep(100);
		scheduler();
		return;
	L_PB_PulseTask_1:
		;
	}

	current_pc[3] = 2;
	AFE4404_Interface_Init();
	scheduler();
	return;

L_PB_PulseTask_2:

	//	nrf_gpio_pin_clear(BOARD_PIN_SPO2_PWR);

		// OS
	current_pc[3] = 3;
	task_sleep(100);
	scheduler();
	return;

L_PB_PulseTask_3:
	//	nrf_gpio_pin_set(BOARD_PIN_SPO2_PWR);

		// OS
	current_pc[3] = 4;
	task_sleep(100);
	scheduler();
	return;

L_PB_PulseTask_4:

	//	Board_AFE4404_Enable(false);

		// OS
	current_pc[3] = 5;
	task_sleep(100);
	scheduler();
	return;

L_PB_PulseTask_5:
	;



	//	uint32_t i;

		//==============remove warning========================
	if (gmin_x != 0)
		gmin_x = 0;

	if (sum_y != 0)
		sum_y = 0;
	//==============remove warning========================

	//2015.11.09 cms For Filter

	//정의 없다
	//lf = Butter_init(0);
	//hf = Butter_init(1);

	x = 0;
	sum_y = 0;
	lmax_y = sMIN;
	lmin_y = sMAX;
#if 1
	set_ui_afe_enable(false);
	set_smart_ct_service_enable(false);

	afe4404_enabled = true;

	//no implement 
	//AFE4404_FUNC_ENABLE(false);
#endif

	PM_fpu_clear();


	for (;;)
	{
		// OS
		current_pc[3] = 6;
		r = sem_take(hAfe4404Sem);
		if (0 != r) {
#if DEBUG
			printf("fail at hAfe4404Sem's sem_take\n");
#endif
		}
		scheduler();
		return;
	L_PB_PulseTask_6:

		current_pc[3] = 7;
		// OS
		mutex_lock(mutex_AFE);
		scheduler();
		return;

	L_PB_PulseTask_7:

#if 1
		switch (button_flag) {
		case button_ON_State:

			if (test_AFE_enable == false) {
				break;
			}

			writeBuffer[0] = 0x00;
			writeBuffer[1] = 0x00;
			writeBuffer[2] = 0x00;
#if (1 == USE_UI)
			//			if ((PB_Get_UI_state() != UI_STATE_AFE || test_AFE_enable == false)
			//					&& (get_AFE_save_state() == PB_AFE_CHECK_STATE_IDLE)) {
			//				break;
			//			}
#endif
			vRegAddress = LED1VAL;

			//			PB_i2c_read(AFE4404_Addr, &vRegAddress, 1, readBuffer, 3);

			raw_data = 0;

			raw_data |= readBuffer[0] << 16;
			raw_data |= readBuffer[1] << 8;
			raw_data |= readBuffer[2];

			if ((raw_data > RAW_MIN) && (raw_data < RAW_MAX)) { //raw_dataũ��� ���뿩�� �Ǵ�
				low_Green = Butter_Calculation(lf, raw_data);
				filtered_data = Butter_Calculation(hf, low_Green);

				x++;					//must be resetting regularly
				new_y = filtered_data;

				switch (wf) {

				case INIT:				//skip until STABLE

					if (x <= STABLE) {//not stable range, just set up some value
						if ((new_y > lmax_y)) {
							lmax_y = new_y;
							lmax_y = x;
						}
						if ((new_y <= lmin_y)) {
							lmin_y = new_y;
							lmin_y = x;
						}
					}
					else {	//now stable, start to count the heart rate
						if ((lmin_x - lmax_x) >= 0) {//check current direction and turn to reverse
							//�ִ밪 ���� �ּҰ��� ��ϵ� ����. ������ UP����.
							wf = UP;
							gmin_y = lmin_y;
							gmin_x = lmin_x;
							gmax_y = lmax_y;
							gmax_x = lmax_x;
							lmax_x = x;
							lmax_y = new_y;
						}
						else {
							wf = DOWN;
							gmin_y = lmin_y;
							gmin_x = lmin_x;
							gmax_y = lmax_y;
							gmax_x = lmax_x;
							lmin_x = x;
							lmin_y = new_y;
						}
					}
					break;

				case DOWN: //DOWN state
					if (new_y <= lmin_y) { //find min value
						lmin_y = new_y;
						lmin_x = x;
					}
					else if (new_y > gmax_y) { //great than current lmax
						lmax_y = new_y;
						lmax_x = x;
					}

					if ((new_y >= lmin_y) && ((x - lmin_x) > lenRE)) {
						scale_lp_hp = abs(gmax_y - lmin_y);
						if (scale_lp_hp > MINPEAKERROR) {
							wf = UP; // raising edge start

							gmin_x = lmin_x;
							gmin_y = lmin_y;

							lmax_x = x;
							lmax_y = new_y;

						}
						else {
							if ((x - lmin_x) > lenRE + 10) {
								wf = INIT;
								hrcnt = 0;
							}
						}
					}
					break;

				case UP: //UP state
					if (new_y >= lmax_y) {
						lmax_y = new_y;
						lmax_x = x;
					}
					else if (new_y < gmin_y) { //little than current lmin
						lmin_y = new_y;
						lmin_x = x;
					}

					if ((new_y < lmax_y) && ((x - lmax_x) > lenFE)) {
						scale_lp_hp = abs(gmin_y - lmax_y);
						if (scale_lp_hp > MINPEAKERROR) {

							wf = DOWN; // falling edge start
							lmin_x = x;		//current data index
							lmin_y = new_y;	//current data value

							//test_code
							if ((lmax_x - gmax_x) < MIN_HIGHPEAK_DISTANCE)//2015.12.31 cms, check highpeak distance
							{
								break;
							}

							gmax_x = lmax_x;//High peak index
							gmax_y = lmax_y;//High peak value

							hrcnt++; //find peak point

							temp_scale_lf_hp = scale_lp_hp;
							EQZ_value = nomarlizedEQZ(scale_lp_hp); // NOMARLIZED scale_lp_hp(range : 2..10)

							PB_Main_event_send(PB_AFE_EVT, PB_AFE_EQZ_EVT_ST, NULL);
							scheduler();
							current_pc[3] = 8;
							return;
						L_PB_PulseTask_8:


							switch (hrcnt) {
							case 1:
								start_point = gmax_x;
								break;
							case 4:
								end_point = gmax_x;

								//test_code
								if ((end_point - start_point) > 0)
								{
									HR_value = (PRF * 60 * 3) / (end_point - start_point);
								}
								else
								{
									HR_value = 0;
								}

								if ((MINHR < HR_value) && (MAXHR > HR_value)) {
									old_HR_value = HR_value;
								}
								else {
									HR_value = old_HR_value;
								}

								//Heart Rate Smooth
								switch (smooth_flag) {
								case Smooth_INIT: //HR_Smooth�� ä��� �ִ� ����
									HR_Smooth[hr_idx] = HR_value;

									temp_HR_value = HR_value;

									hr_idx++;
									if (hr_idx == 5) {
										hr_idx = 0; //index �ʱ�ȭ
										smooth_flag = Smooth_Ready; //HR���� 5�� ������ smoothing����
									}
									break;

									//max_idx�� min_idx�� �������� max_idx���� overwriting�Ѵ�.
								case Smooth_MAX_OV: //HR_Smooth�� MAX�� Overwriting ����
									HR_Smooth[max_idx] = HR_value;

									temp_HR_value = HR_value;

									smooth_flag = Smooth_MIN_OV;
									break;

								case Smooth_MIN_OV: //HR_Smooth�� MIN�� Overwriting ����
									HR_Smooth[min_idx] = HR_value;

									temp_HR_value = HR_value;

									smooth_flag = Smooth_Ready;
									break;

								default:
									break;
								}

								hrcnt = 0;

								break;

							default:
								break;

							} //end inner switch
						}
						else {
							//not find state or noise peak state
							if ((x - lmax_x) > lenFE + 10) {
								wf = INIT;
								hrcnt = 0;
							}
						}
					}
					break;

				default:
					break;
				} //end of switch

				if (smooth_flag == Smooth_Ready) { //HeartRate ����غ� �Ϸ� ����
					smooth_flag = Smooth_MAX_OV;

					max_idx = 0;
					min_idx = 0;
					for (loop_idx = 1; loop_idx < 5; loop_idx++) {
						if (HR_Smooth[max_idx] <= HR_Smooth[loop_idx]) {
							//find max HR_value
							max_idx = loop_idx;
						}
						if (HR_Smooth[min_idx] > HR_Smooth[loop_idx]) {
							//find min HR_value
							min_idx = loop_idx;
						}
					}

					for (loop_idx = 0; loop_idx < 5; loop_idx++) { //�ִ� �ּҰ� ���� �ϰ� ���
						if ((loop_idx != max_idx) && (loop_idx != min_idx))
							hr_sum += HR_Smooth[loop_idx];
					}

					HR_output = hr_sum / 3;

					temp_HR_value = HR_output;

					hr_sum = 0;
				}

				//test_code : Reset Check ware
				check_wear = 0;
				wear_enable = 1;

			}
			else { //������ ����
				raw_data = 0;
				check_wear++;
				if (check_wear == CHECK_WEAR_TIMEOUT) {
					check_wear = 0;
					HR_output = 0;//2015.12.28 cms

					//test_code smart car talk
					temp_scale_lf_hp = 0;
					temp_HR_value = 0;

					if (PB_Get_UI_state() == UI_STATE_AFE && wear_enable == 1)
					{
						PB_Main_event_send(PB_AFE_EVT, PB_AFE_NO_SIG_EVT_ST, NULL);
						wear_enable = 0;
					}
				}
			}
			break;

		case button_OFF_SMOOTH_State:
			button_flag = button_OFF_State;

			// OS
			task_sleep(100);
			scheduler();
			current_pc[3] = 9;
			return;
		L_PB_PulseTask_9:

			break;
		case button_OFF_State:
			break;
		}
#endif
		// OS
		current_pc[3] = 10;
		mutex_unlock(mutex_AFE);
		scheduler();
		return;

	L_PB_PulseTask_10:
		;
	}


	current_pc[3] = 0;
	TerminateTask();
	scheduler();
	return;
}


void PB_PulseTask_int(void) {
	int r;

	// OS
	r = task_create(3);
	if (0 != r) {
#if DEBUG
		printf("fail at AFE4404's task_create\n");
#endif
	}

	// OS
	r = mutex_create(&mutex_AFE);
	if (0 != r) {
#if DEBUG
		printf("fail at mutex_AFE's mutex_create\n");
#endif
	}

	// OS
	r = mutex_create(&prms_AFE);
	if (0 != r) {
#if DEBUG
		printf("fail at task_create");
#endif
	}
}

bool get_smart_ct_service_enable() {
	return PB_smart_ct_service_enable;
}


// ys modified
/*void set_smart_ct_service_enable(bool enable) {
	PB_smart_ct_service_enable = enable;
}*/

