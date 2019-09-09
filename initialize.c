#include "ubinos.h"
task_static_config task_static_info[NUM_OF_TASKS + 1];
task_dynamic_stat task_dyn_info[NUM_OF_TASKS + 1];
Sem sem_list[NUM_OF_SEMS + 1];
Msgq msgq_list[NUM_OF_MSGQS + 1];
Mutex mutex_list[NUM_OF_MUTEXS + 1];
unsigned char task_state[NUM_OF_TASKS + 1] = { 0 };
unsigned char Ceiling_Prio[2];



void initialize() {
	//PB_ble_stack_task
	task_static_info[1].max_act_cnt = 1;
	task_static_info[1].prio = 2;
	task_dyn_info[1].dyn_prio = task_static_info[1].prio;

	//PB_ble_control_task
	task_static_info[2].max_act_cnt = 1;
	task_static_info[2].prio = 2;
	task_dyn_info[2].dyn_prio = task_static_info[2].prio;

	//PB_UI_Task
	task_static_info[3].max_act_cnt = 1;
	task_static_info[3].prio = 1;
	task_dyn_info[3].dyn_prio = task_static_info[3].prio;

	//PB_Main_Task
	task_static_info[4].max_act_cnt = 1;
	task_static_info[4].prio = 1;
	task_dyn_info[4].dyn_prio = task_static_info[4].prio;

	//PB_PulseTask
	task_static_info[5].max_act_cnt = 1;
	task_static_info[5].prio = 2;
	task_dyn_info[5].dyn_prio = task_static_info[5].prio;






	for (int i = 1; i < NUM_OF_MUTEXS + 1; i++)
	{
		mutex_list[i].flag = 0;
		mutex_list[i].Front = 0;
		mutex_list[i].Rear = 0;
		mutex_list[i].prio_inheri_flag = 0;
		mutex_list[i].block_flag = 0;
		mutex_list[i].owner = 0;
		mutex_list[i].lock_counter = 0;
		mutex_list[i].timed_flag = -1;
		mutex_list[i].inheri_prio = -1;

	}


	for (int i = 1; i < NUM_OF_SEMS + 1; i++)
	{
		sem_list[i].Front = 0;
		sem_list[i].Rear = 0;
		sem_list[i].counter = 0;
	}

	for (int i = 1; i < NUM_OF_MSGQS + 1; i++)
	{
		msgq_list[i].Front = 0;
		msgq_list[i].Rear = 0;
		msgq_list[i].F = 0;
		msgq_list[i].R = 0;
		msgq_list[i].counter = 0;


	}



	for (int i = 1; i < NUM_OF_TASKS + 1; i++)
	{

		task_dyn_info[i].dyn_prio = task_static_info[i].prio;
		task_dyn_info[i].In_MsgqQ = 0;
		task_dyn_info[i].In_MutexQ = 0;
		task_dyn_info[i].In_ReadyQ = 0;
		task_dyn_info[i].In_SemQ = 0;
		task_dyn_info[i].In_SleepQ = 0;

		task_dyn_info[i].Msgq_Id = 0;
		task_dyn_info[i].Mutex_Id = 0;
		task_dyn_info[i].Sem_Id = 0;

		//task_dyn_info[i].buf[i].event = -1;
		//task_dyn_info[i].buf[i].status = -1;
		//task_dyn_info[i].buf[i].msg = NULL;

		sem_list[1].sem_timed_info[i] = -1;
		sem_list[1].sem_timed_flag[i] = -1;
		sem_list[1].semQ[i].tid = 0;
		sem_list[2].sem_timed_info[i] = -1;
		sem_list[2].sem_timed_flag[i] = -1;
		sem_list[2].semQ[i].tid = 0;
		sem_list[3].sem_timed_info[i] = -1;
		sem_list[3].sem_timed_flag[i] = -1;
		sem_list[3].semQ[i].tid = 0;


		msgq_list[1].msgqQ[i].tid = 0;
		msgq_list[2].msgqQ[i].tid = 0;
		msgq_list[3].msgqQ[i].tid = 0;

		mutex_list[1].mutex_timed_flag[i] = -1;
		mutex_list[1].mutex_timed_info[i] = -1;
		mutex_list[1].mutexQ[i].tid = 0;
		mutex_list[2].mutex_timed_flag[i] = -1;
		mutex_list[2].mutex_timed_info[i] = -1;
		mutex_list[2].mutexQ[i].tid = 0;
		mutex_list[3].mutex_timed_flag[i] = -1;
		mutex_list[3].mutex_timed_info[i] = -1;
		mutex_list[3].mutexQ[i].tid = 0;

	}

}
