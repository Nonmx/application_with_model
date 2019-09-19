#include "PB_ble.h"
#include "UI.h"
#include "PAARBand_Main.h"
#include "AFE4404.h"
#include <stdio.h>
#include "os.h"
#include <assert.h>

int main()
{
	printf("PB_BLE_init\n\n");
	PB_BLE_init();

	printf("PB_UI_init\n\n");
	PB_UI_init();

	printf("PB_PAARBand_Main_init\n\n");
	PB_PAARBand_Main_init();

	printf("PB_PulseTask_init\n\n");
	PB_PulseTask_int();

	printf("ubik_comp_start\n\n");
	ubik_comp_start();
	
	return 0;
}

int tick = 0;
int timeout_checker;

extern msgq_pt BLE_Msgq;
extern msgq_pt Main_Msgq;
extern msgq_pt uiMsgq;

extern sem_pt hAfe4404Sem;
extern sem_pt _uart_tx_evt_sem;
extern sem_pt _ble_evt_sem;

extern mutex_pt mutex_AFE;
extern mutex_pt prms_AFE;
void running(){
	while (current_tid >= 0)
	{

		//running할 때 한 task만 running할 수 있다.
		assert(task_state[1] == Running ? !(task_state[2] == Running && task_state[3] == Running && task_state[4] == Running && task_state[5] == Running) : 1);
		assert(task_state[2] == Running ? !(task_state[1] == Running && task_state[3] == Running && task_state[4] == Running && task_state[5] == Running) : 1);
		assert(task_state[3] == Running ? !(task_state[1] == Running && task_state[2] == Running && task_state[4] == Running && task_state[5] == Running) : 1);
		assert(task_state[4] == Running ? !(task_state[1] == Running && task_state[2] == Running && task_state[3] == Running && task_state[5] == Running) : 1);
		assert(task_state[5] == Running ? !(task_state[1] == Running && task_state[2] == Running && task_state[3] == Running && task_state[4] == Running) : 1);

		//모든 task 다 수행한 적이 있다
		assert(!(current_pc[1] > 0)); //false
		assert(!(current_pc[2] > 0)); //false
		assert(!(current_pc[3] > 0)); //false
		assert(!(current_pc[4] > 0)); //false
		assert(!(current_pc[5] > 0)); //false

		//msgq waitQ Front 및 Rear check
		//msgq -> BLE_Msgq
		assert(!(msgq_list[BLE_Msgq].Front > 0));
		assert(!(msgq_list[BLE_Msgq].Rear > 0));

		//msgq -> Main_Msgq
		assert(!(msgq_list[Main_Msgq].Front > 0));
		assert(!(msgq_list[Main_Msgq].Rear) > 0);

		//msgq -> uiMsgq
		assert(!(msgq_list[uiMsgq].Front > 0));
		assert(!(msgq_list[uiMsgq].Rear > 0));


		//msg send하는지 check
		//msgq -> BLE_Msgq
		assert(!(msgq_list[BLE_Msgq].F > 0));
		assert(!(msgq_list[BLE_Msgq].R > 0));

		//msgq -> Main_Msgq
		assert(!(msgq_list[Main_Msgq].F > 0));
		assert(!(msgq_list[Main_Msgq].R > 0));

		//msgq -> uiMsgq
		assert(!(msgq_list[uiMsgq].F > 0));
		assert(!(msgq_list[uiMsgq].R > 0));


		//waitingQ에 있는 태스크의 우선순위 자동 적으로 sort
		//msgq waitQ -> BLE_Msgq
		assert((msgq_list[BLE_Msgq].Rear - msgq_list[BLE_Msgq].Front + NUM_OF_TASKS) % NUM_OF_TASKS > 1 && task_dyn_info[msgq_list[BLE_Msgq].msgqQ
			[(msgq_list[BLE_Msgq].Front + 1) % NUM_OF_TASKS].tid].dyn_prio > 0 ? task_dyn_info[msgq_list[BLE_Msgq].msgqQ[msgq_list[BLE_Msgq].Front + 1].tid
			].dyn_prio >= task_dyn_info[msgq_list[BLE_Msgq].msgqQ[(msgq_list[BLE_Msgq].Front + 1) % NUM_OF_TASKS].tid].dyn_prio : 1);

		//msgq waitQ -> Main_Msgq
		assert((msgq_list[Main_Msgq].Rear - msgq_list[Main_Msgq].Front + NUM_OF_TASKS) % NUM_OF_TASKS > 1 && task_dyn_info[msgq_list[Main_Msgq].msgqQ
			[(msgq_list[Main_Msgq].Front + 1) % NUM_OF_TASKS].tid].dyn_prio > 0 ? task_dyn_info[msgq_list[Main_Msgq].msgqQ[msgq_list[Main_Msgq].Front + 1].tid
			].dyn_prio >= task_dyn_info[msgq_list[Main_Msgq].msgqQ[(msgq_list[Main_Msgq].Front + 1) % NUM_OF_TASKS].tid].dyn_prio : 1);

		//msgq_waitQ -> uiMsgq
		assert((msgq_list[uiMsgq].Rear - msgq_list[uiMsgq].Front + NUM_OF_TASKS) % NUM_OF_TASKS > 1 && task_dyn_info[msgq_list[uiMsgq].msgqQ
			[(msgq_list[uiMsgq].Front + 1) % NUM_OF_TASKS].tid].dyn_prio > 0 ? task_dyn_info[msgq_list[uiMsgq].msgqQ[msgq_list[uiMsgq].Front + 1].tid
			].dyn_prio >= task_dyn_info[msgq_list[uiMsgq].msgqQ[(msgq_list[uiMsgq].Front + 1) % NUM_OF_TASKS].tid].dyn_prio : 1);

		
		//sem waitQ
		//sem -> hAfe4404Sem
		assert((sem_list[hAfe4404Sem].Rear - sem_list[hAfe4404Sem].Front+ NUM_OF_TASKS)% NUM_OF_TASKS
		 > 1 && task_dyn_info[sem_list[hAfe4404Sem].semQ[(sem_list[hAfe4404Sem].Front+1)%NUM_OF_TASKS].tid].dyn_prio > 0 ? task_dyn_info[sem_list[hAfe4404Sem
		 ].semQ[sem_list[hAfe4404Sem].Front+1].tid].dyn_prio >= task_dyn_info[sem_list[hAfe4404Sem]
		 .semQ[(sem_list[hAfe4404Sem].Front+1)%NUM_OF_TASKS].tid].dyn_prio:1);

		//sem -> uart_tx_evt_sem
		assert((sem_list[_uart_tx_evt_sem].Rear - sem_list[_uart_tx_evt_sem].Front + NUM_OF_TASKS) % NUM_OF_TASKS
		 > 1 && task_dyn_info[sem_list[_uart_tx_evt_sem].semQ[(sem_list[_uart_tx_evt_sem].Front + 1) % NUM_OF_TASKS].tid].dyn_prio > 0 ? task_dyn_info[sem_list[_uart_tx_evt_sem
		 ].semQ[sem_list[_uart_tx_evt_sem].Front + 1].tid].dyn_prio >= task_dyn_info[sem_list[_uart_tx_evt_sem]
			.semQ[(sem_list[_uart_tx_evt_sem].Front + 1) % NUM_OF_TASKS].tid].dyn_prio : 1);

		//sem -> _ble_evt_sem
		assert((sem_list[_ble_evt_sem].Rear - sem_list[_ble_evt_sem].Front + NUM_OF_TASKS) % NUM_OF_TASKS
		 > 1 && task_dyn_info[sem_list[_ble_evt_sem].semQ[(sem_list[_ble_evt_sem].Front + 1) % NUM_OF_TASKS].tid].dyn_prio > 0 ? task_dyn_info[sem_list[_ble_evt_sem
		 ].semQ[sem_list[_ble_evt_sem].Front + 1].tid].dyn_prio >= task_dyn_info[sem_list[_ble_evt_sem]
			.semQ[(sem_list[_ble_evt_sem].Front + 1) % NUM_OF_TASKS].tid].dyn_prio : 1);

		//sem Rear and Front check
		assert(!(sem_list[hAfe4404Sem].Rear > 0));
		assert(!(sem_list[hAfe4404Sem].Front > 0));

		assert(!(sem_list[_uart_tx_evt_sem].Rear > 0));
		assert(!(sem_list[_uart_tx_evt_sem].Front > 0));

		assert(!(sem_list[_ble_evt_sem].Rear > 0));
		assert(!(sem_list[_ble_evt_sem].Front > 0));

		//mutex waitQ
		assert((mutex_list[mutex_AFE].Rear - mutex_list[mutex_AFE].Front + NUM_OF_TASKS)%NUM_OF_TASKS > 1
		&& task_dyn_info[mutex_list[mutex_AFE].mutexQ[(mutex_list[mutex_AFE].Front+1)%NUM_OF_TASKS].tid].dyn_prio > 0 ?
		task_dyn_info[mutex_list[mutex_AFE].mutexQ[mutex_list[mutex_AFE].Front].tid].dyn_prio >= task_dyn_info[
		mutex_list[mutex_AFE].mutexQ[(mutex_list[mutex_AFE].Front+1)%NUM_OF_TASKS].tid].dyn_prio+1 :1);

		//prms_AFE
		assert((mutex_list[prms_AFE].Rear - mutex_list[prms_AFE].Front + NUM_OF_TASKS) % NUM_OF_TASKS > 1
		&& task_dyn_info[mutex_list[prms_AFE].mutexQ[(mutex_list[prms_AFE].Front + 1) % NUM_OF_TASKS].tid].dyn_prio > 0 ?
		task_dyn_info[mutex_list[prms_AFE].mutexQ[mutex_list[prms_AFE].Front].tid].dyn_prio >= task_dyn_info[
		mutex_list[prms_AFE].mutexQ[(mutex_list[prms_AFE].Front + 1) % NUM_OF_TASKS].tid].dyn_prio + 1 : 1);

		//
		assert(!(mutex_list[prms_AFE].Rear > 0));
		assert(!(mutex_list[prms_AFE].Front > 0));

		assert(!(mutex_list[mutex_AFE].Rear) > 0);
		assert(!(mutex_list[mutex_AFE].Front) > 0);

		tick++;
		timeout_checker++;
		if (tick == 1000) //sec
		{
			

			ble_evt_handler();

			PB_wdt_refresh_handler();

			tick = 0;

		}
		
		if (timeout_checker == 60000) //1 min
		{
			UI_timeout_handler();

			timeout_checker = 0;
		}
		

		if (current_tid == 1)//PB_ble_stack_task
			PB_ble_stack();
		else if (current_tid == 2) //PB_ble_control_task
			PB_ble_control();
		else if (current_tid == 3) //PB_UI_Task 	
			PB_UI();
		else if (current_tid == 4) // PB_Main_Task
			PB_Main();
		else if (current_tid == 5) // PB_PulseTask
			PB_Pulse();

		if (current_tid == 0)
		{
			scheduler();
		}
	}
}