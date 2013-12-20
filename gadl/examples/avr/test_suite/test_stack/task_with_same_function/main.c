 #include "tpl_os.h"
#include "tpl_app_config.h"
#include <avr/io.h>

DeclareTask(thirdTask);
DeclareTask(secondTask);
DeclareTask(fourthTask);
DeclareTask(eventTask);
DeclareEvent(EV1);

void functionOfBothTask(int num);

/*ISR(boutonISR)
{
	PORTA ^= 0x20;
	TerminateISR ();
}*/

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

	while(1);
}

TASK(secondTask){
	functionOfBothTask(2);
	TerminateTask();
}

TASK(thirdTask){
	functionOfBothTask(3);
	TerminateTask();
}


TASK(fourthTask){
	functionOfBothTask(4);
	TerminateTask();
}

void functionOfBothTask(int num){
	int i=1;
	if(num==3 || num==2)ActivateTask(fourthTask);
}

