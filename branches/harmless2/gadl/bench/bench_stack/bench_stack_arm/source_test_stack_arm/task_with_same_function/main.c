#include "tpl_os.h"
#include "tpl_app_config.h"
#include "LPC22xx.h"

DeclareTask(thirdTask);
DeclareTask(secondTask);
DeclareTask(fourthTask);
DeclareTask(eventTask);
DeclareEvent(EV1);

void functionOfBothTask(int num);


//#define APP_Task_task1_START_SEC_CODE
//#include "tpl_memmap.h"

FUNC(int, OS_APPL_CODE) main(void){

    StartOS(OSDEFAULTAPPMODE);
    return 0;
}


TASK(startTask)
{
	while(1){
		ActivateTask(secondTask);
		ActivateTask(thirdTask);
	}
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

//#define APP_Task_task1_STOP_SEC_CODE
//#include "tpl_memmap.h"

