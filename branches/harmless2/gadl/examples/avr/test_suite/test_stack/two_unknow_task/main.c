#include "tpl_os.h"
#include "tpl_app_config.h"

DeclareTask(thirdTask);
DeclareTask(secondTask);
DeclareTask(fourthTask);
DeclareTask(eventTask);
//DeclareEvent(EV1);

void functionOfBothTask(int num);



//remove trampoline def of ISR..
#undef ISR
//#include <avr/interrupt.h>
//and add GCC def of ISR :-/
//
int main(void){

    StartOS(OSDEFAULTAPPMODE);
    return 0;
}


TASK(startTask)
{
	ActivateTask(secondTask);
	ActivateTask(thirdTask);
	ActivateTask(fourthTask);
	while(1);
}

TASK(secondTask){
	TerminateTask();
}

TASK(thirdTask){
	TerminateTask();
}


TASK(fourthTask){
	TerminateTask();
}

