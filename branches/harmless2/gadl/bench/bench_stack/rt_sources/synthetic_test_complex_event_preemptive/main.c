#include "tpl_os.h"
#include "tpl_app_config.h"

DeclareTask(thirdTask);
DeclareTask(secondTask);
DeclareTask(fourthTask);
DeclareTask(eventTask);
DeclareEvent(EV1);

void functionOfBothTask(int num);

//remove trampoline def of ISR..
#undef ISR
//#include <avr/interrupt.h>
//and add GCC def of ISR :-/
//

//#define APP_Task_task1_START_SEC_CODE
//#include "tpl_memmap.h"

FUNC(int, OS_APPL_CODE) main(void){


    StartOS(OSDEFAULTAPPMODE);
    return 0;
}


TASK(thirdTask){
	SetEvent(eventTask,EV1);
	TerminateTask();
}



TASK(startTask)
{
	while(1){
		ActivateTask(eventTask);
		ActivateTask(secondTask);
		ActivateTask(thirdTask);
	}
}

TASK(secondTask)
{
	SetEvent(eventTask,EV1);
	TerminateTask();
}

TASK(fourthTask){
	TerminateTask();
}

TASK(eventTask){
	EventMaskType event_got;
	while(1){
		WaitEvent(EV1);
		GetEvent(eventTask, &event_got);
		if(event_got & EV1){
			ActivateTask(fourthTask);
		}
		ClearEvent(EV1);
	}
	
	TerminateTask();
}



void functionOfBothTask(int num){
	SetEvent(eventTask,EV1);
}

//#define APP_Task_task1_STOP_SEC_CODE
//#include "tpl_memmap.h"

