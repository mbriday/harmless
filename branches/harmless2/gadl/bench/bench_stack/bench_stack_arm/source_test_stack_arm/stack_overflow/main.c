#include "tpl_os.h"
#include "tpl_app_config.h"
#include "LPC22xx.h"

DeclareTask(thirdTask);
DeclareTask(secondTask);
DeclareTask(fourthTask);
DeclareTask(eventTask);

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
		ActivateTask(fourthTask);
	}
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

//#define APP_Task_task1_STOP_SEC_CODE
//#include "tpl_memmap.h"
