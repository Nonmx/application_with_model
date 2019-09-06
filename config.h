#ifndef CONFIG_H_
#define CONFIG_H_

#define TASK(t) TASK_##t()


#define NUM_OF_TASKS 5
#define MIN_TASK_ID 1
#define MAX_TASK_ID 5
#define MAX_PRIORITY 2

#define NUM_OF_SEMS 3
#define NUM_OF_MSGQS 3
#define NUM_OF_MUTEXS 3


#define PB_ble_stack_task 1 //2
#define PB_ble_control_task 2 //2
#define PB_PulseTask 3 //2
#define PB_Main_Task 4 //1
#define PB_UI_Task 5 // 1



#define testalarm 1
#endif
