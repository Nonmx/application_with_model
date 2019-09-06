#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "absconfig.h"

#include "PB_ble.h"
//#include "ubik_sem.h"
//#include "ubik_msgq.h"
#include "PAARBand_Main.h"
#include "softdevice_handler.h"

#define BLE_MAX_MSGQ_COUNT	20

int flag;

uint8_t PB_BLE_event_send(uint8_t UI_evt, uint8_t UI_evt_state, uint8_t* msg);

static sem_pt _ble_evt_sem = NULL;
static msgq_pt BLE_Msgq;

int r;
void PB_BLE_init() {
	int r;

	// OS
	printf("create PB_ble_stack_task\n\n");
	r = task_create(1);//PB_ble_stack_task
	if (r != 0) {

#if DEBUG
		printf("fail at task_create\n");
#endif
	}

	// OS
	printf("create PB_ble_control_task\n\n");
	r = task_create(2);//PB_ble_control_task
	if (r != 0) {
#if DEBUG
		printf("fail at task_create\n");
#endif
	}

	// sem create
	// OS
	printf("sem create ble_evt_sem\n\n");
	r = sem_create(&_ble_evt_sem);
	if (0 != r) {
#if DEBUG
		printf("fail to sem_create\n\r");
#endif
	}

	//msgq_create : UI msgq
	// OS
	printf("create msgq\n\n");
	r = msgq_create(&BLE_Msgq, sizeof(pbBLEEvt_t), BLE_MAX_MSGQ_COUNT);
	if (0 != r) {
#if DEBUG
		printf("fail at msgq_create\n\r");
#endif
	}
}

// task (modify)
#define JUMP_PB_ble_stack_task(){\
	switch (current_pc[1])\
	{\
		case 0:\
			goto L_PB_ble_stack_task_0;break;\
		case 1:\
			goto L_PB_ble_stack_task_1;break;\
		case 2:\
			goto L_PB_ble_stack_task_2;break;\
	}\
}

//static void TASK(1) { // PB_ble_stack_task
void PB_ble_stack()
{

	JUMP_PB_ble_stack_task();
L_PB_ble_stack_task_0:
	// Enter ble stack main handling loop.
	for (;;) {
		// OS
		current_pc[1] = 1;
		printf("task PB_ble_stack_task take sem\n\n");
		sem_take(_ble_evt_sem);
		scheduler();
		return;
	L_PB_ble_stack_task_1:

		current_pc[1] = 2;
		printf("task PB_ble_stack_task send message\n\n");
		intern_softdevice_events_execute(); // msg send
		scheduler();
		return;

	L_PB_ble_stack_task_2:
		;
	}

	current_pc[1] = 0;
	TerminateTask();
	scheduler();
	return;
}

// external ble(-receive) event handler.
// environment
void ble_evt_handler(void) {
	// OS
	sem_give(_ble_evt_sem);
}

//ys modified
//static void on_ble_evt()
void on_ble_evt() {
	srand(time(NULL));
	int random = rand() % 3;

	switch (random) {
	case 0:
		PB_BLE_event_send(PB_BLE_EVT, PB_BLE_CONNECTION_EVT_ST, NULL);
		break;
	case 1:
		PB_BLE_event_send(PB_BLE_EVT, PB_BLE_DISCONNECTION_EVT_ST, NULL);
		break;
	case 2:
		// not considering the value of temp_msg
		//	PB_BLE_event_send(PB_BLE_EVT, PB_BLE_PACKET_REV_EVT_ST, temp_msg);
		PB_BLE_event_send(PB_BLE_EVT, PB_BLE_PACKET_REV_EVT_ST, NULL);
		break;
	default:
		break;
	}
}

uint8_t PB_BLE_event_send(uint8_t UI_evt, uint8_t UI_evt_state, uint8_t* msg) {
	pbBLEEvt_t temp_msg;
	temp_msg.event = UI_evt;
	temp_msg.status = UI_evt_state;
	temp_msg.msg = msg;

	// OS
	msgq_send(BLE_Msgq, (unsigned char*)& temp_msg);

	return 0;

}

// task
#define JUMP_PB_ble_control_task(){\
	switch (current_pc[2])\
	{\
		case 0:\
			goto L_PB_ble_control_task_0;break;\
		case 1:\
			goto L_PB_ble_control_task_1;break;\
		case 2:\
			goto L_PB_ble_control_task_2;break;\
		case 3:\
			goto L_PB_ble_control_task_3;break;\
		case 4:\
			goto L_PB_ble_control_task_4;break;\
		case 5:\
			goto L_PB_ble_control_task_5;break;\
		case 6:\
			goto L_PB_ble_control_task_6;break;\
	}\
}

pbBLEEvt_t BLE_msgRxBuffer;

//static void TASK(2) { // PB_control_task
void PB_ble_control()
{
JUMP_PB_ble_control_task();
L_PB_ble_control_task_0:

	for (;;) {
		// OS
		current_pc[2] = 1;
		msgq_receive(BLE_Msgq, (unsigned char*)& BLE_msgRxBuffer);
		scheduler();
		return;
	L_PB_ble_control_task_1:

		if (0 != r) {
#if DEBUG
			printf("fail at msgq_receive\r\n");
#endif
		}
		else {
			switch (BLE_msgRxBuffer.event) {
			case PB_BLE_EVT: {
				switch (BLE_msgRxBuffer.status) {
				case PB_BLE_CONNECTION_EVT_ST:
					PB_Main_event_send(PB_BLE_EVT, PB_BLE_CONNECTION_EVT_ST, NULL);
					scheduler();
					current_pc[2] = 2;
					return; //?
				L_PB_ble_control_task_2:
					break;

				case PB_BLE_DISCONNECTION_EVT_ST: {
					PB_Main_event_send(PB_BLE_EVT, PB_BLE_DISCONNECTION_EVT_ST, NULL);
					scheduler();
					current_pc[2] = 3;
					return;
				L_PB_ble_control_task_3:
					break;
				}

				case PB_BLE_PACKET_REV_EVT_ST: {
					// temporary call of PB_Main_event_send instead of PB_IncomingPacketHandler
					// PB_IncomingPacketHandler(BLE_msgRxBuffer.msg);
					PB_Main_event_send(PB_BLE_EVT, PB_BLE_PACKET_REV_EVT_ST, NULL);
					scheduler();
					current_pc[2] = 4;
					return;
				L_PB_ble_control_task_4:

					if (BLE_msgRxBuffer.msg != NULL)
						free(BLE_msgRxBuffer.msg);

					break;
				}

				case PB_BLE_SMART_CT_DATA_SEND_EVT_ST: {
					// temporary call of PB_Main_event_send instead of PB_smart_ct_data_send
					// PB_IncomingPacketHandler(BLE_msgRxBuffer.msg);
					// PB_smart_ct_data_send(BLE_msgRxBuffer.msg);
					PB_Main_event_send(PB_BLE_EVT, PB_BLE_SMART_CT_DATA_SEND_EVT_ST, NULL);
					scheduler();
					current_pc[2] = 5;
				L_PB_ble_control_task_5:

					break;
				}
				}

				break;
			}

			case PB_BLE_CONTROL_EVT: {
				switch (BLE_msgRxBuffer.status) {
				case PB_BLE_CONTROL_PNIP_START_ST:

					break;
				case PB_BLE_CONTROL_PNIP_STOP_ST:

					break;
				case PB_BLE_TIMEOUT_ST:

					break;
				case PB_BLE_ACTIVITY_SEND_TIMEOUT_ST:

					break;
				case PB_BLE_REFRESH:
					break;
				}

				break;
			}

			case PB_SMART_CAR_TALK_EVT:
				break;
			default:
				break;
			}
		}

		if (BLE_msgRxBuffer.msg != NULL)
			free(BLE_msgRxBuffer.msg);

	L_PB_ble_control_task_6:
		;
	}

	current_pc[2] = 0;
	flag = TerminateTask();
	scheduler();
	return;

}
