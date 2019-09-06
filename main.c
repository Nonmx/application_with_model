#include "PB_ble.h"
#include "UI.h"
#include "PAARBand_Main.h"
#include "AFE4404.h"
#include <stdio.h>
#include "os.h"


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

	ubik_comp_start();
	
	return 0;
}

void running()
{
	while (current_tid >= 0)
	{
		if (current_tid == 1)//PB_ble_stack_task
			PB_ble_stack();
		else if (current_tid == 2) //PB_ble_control_task
			PB_ble_control();
		else if (current_tid == 3) // PB_PulseTask
			PB_Pulse();
		else if (current_tid == 4) // PB_Main_Task
			PB_Main();
		else if (current_tid == 5) // PB_UI_Task
			PB_UI();

	}
}