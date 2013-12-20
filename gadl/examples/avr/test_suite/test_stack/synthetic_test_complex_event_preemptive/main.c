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
int main(void)
{

    StartOS(OSDEFAULTAPPMODE);
    return 0;
}


TASK(thirdTask){
	SetEvent(eventTask,EV1);
	TerminateTask();
}



TASK(startTask)
{
	ActivateTask(eventTask);
	ActivateTask(secondTask);
	ActivateTask(thirdTask);
	while(1);
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
