#include "tpl_os.h"

FUNC(int, OS_APPL_CODE) main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

DeclareEvent(ev1);

unsigned long un = 0;    //Un
unsigned long unp1 = 1;  //Un+1
TASK(extendedTask)
{
	while(1)
	{
		WaitEvent(ev1);
		ClearEvent(ev1);
		unsigned long unp2 = unp1+un;
		un = unp1;
		unp1 = unp2;
	}
	//TerminateTask();
}

unsigned long val;
TASK(basicTask)
{
	val++;
	SetEvent(extendedTask, ev1); //besicTask is preempted by extendedTask.
	TerminateTask();
}

TASK(masterTask)
{
	un = 0;
	unp1 = 1;
	val = 0;
	//master is preempted by basicTask.
	for(unsigned int i = 0; i < 10; i++) ActivateTask(basicTask);
	//fin oscillo
	ChainTask(masterTask);
}

