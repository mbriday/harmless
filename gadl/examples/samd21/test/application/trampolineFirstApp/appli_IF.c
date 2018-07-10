#include "tpl_os.h"

DeclareTask (T2);
DeclareTask (T3);
DeclareTask (T4);
DeclareTask (T5);
DeclareTask (T6);

DeclareEvent (event1);
DeclareEvent (event2);

DeclareResource(res1);

int cpt_cycle = 1;
int cpt_cycle_isr = 0;
int j = 0;
int tab_trace[200]={0};

FUNC(int, OS_APPL_CODE) main(void)
{
	StartOS(OSDEFAULTAPPMODE);
	return 0;
}

#define APP_Task_T1_START_SEC_CODE
#include "tpl_memmap.h"

TASK(T1)
{
	tab_trace[j] = 1 + 100 * (cpt_cycle - 1);
	j++;
	//doSysTickIt();		// IT pour alarme 1/2
	ActivateTask(T2);
	tab_trace[j] = 4 + 100 * (cpt_cycle - 1);
	j++;
	WaitEvent(event1);
	tab_trace[j] = 5 + 100 * (cpt_cycle - 1);
	j++;
	ClearEvent(event1);
	tab_trace[j] = 6 + 100 * (cpt_cycle - 1);
	j++;
	ActivateTask(T3);
	tab_trace[j] = 7 + 100 * (cpt_cycle - 1);
	j++;
	WaitEvent(event2);
	tab_trace[j] = 18 + 100 * (cpt_cycle - 1);
	j++;
	WaitEvent(event1);
	tab_trace[j] = 20 + 100 * (cpt_cycle - 1);
	j++;
	TerminateTask();
}
#define APP_Task_T1_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_Task_T2_START_SEC_CODE
#include "tpl_memmap.h"
TASK(T2)
{
	tab_trace[j] = 2 + 100 * (cpt_cycle - 1);
	j++;
	SetEvent(T1,event1);
	tab_trace[j] = 3 + 100 * (cpt_cycle - 1);
	j++;
	TerminateTask();
}
#define APP_Task_T2_STOP_SEC_CODE
#include "tpl_memmap.h"


#define APP_Task_T3_START_SEC_CODE
#include "tpl_memmap.h"
TASK(T3)
{
	tab_trace[j] = 8 + 100 * (cpt_cycle - 1);
	j++;
	GetResource(res1);
	tab_trace[j] = 9 + 100 * (cpt_cycle - 1);
	j++;
	SetEvent(T1,event2);
	tab_trace[j] = 10 + 100 * (cpt_cycle - 1);
	j++;
	ActivateTask(T4);//doSysTickIt();		// IT pour alarme 2/2
	tab_trace[j] = 17 + 100 * (cpt_cycle - 1);
	j++;
	ReleaseResource(res1);
	tab_trace[j] = 19 + 100 * (cpt_cycle - 1);
	j++;
	SetEvent(T1,event1);
	tab_trace[j] = 21 + 100 * (cpt_cycle - 1);
	j++;
	TerminateTask();
}
#define APP_Task_T3_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_Task_T4_START_SEC_CODE
#include "tpl_memmap.h"
TASK(T4)
{
	tab_trace[j] = 11 + 100 * (cpt_cycle - 1);
	j++;
	Schedule();
	tab_trace[j] = 12 + 100 * (cpt_cycle - 1);
	j++;
	ActivateTask(T5);
	tab_trace[j] = 13 + 100 * (cpt_cycle - 1);
	j++;
	Schedule();
	tab_trace[j] = 16 + 100 * (cpt_cycle - 1);
	j++;
	TerminateTask();
}
#define APP_Task_T4_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_Task_T5_START_SEC_CODE
#include "tpl_memmap.h"
TASK(T5)
{
	tab_trace[j] = 14 + 100 * (cpt_cycle - 1);
	j++;
	ChainTask(T6);
}
#define APP_Task_T5_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_Task_T6_START_SEC_CODE
#include "tpl_memmap.h"
TASK(T6)
{
	tab_trace[j] = 15 + 100 * (cpt_cycle - 1);
	j++;
	TerminateTask();
}
#define APP_Task_T6_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_Task_Tfond_START_SEC_CODE
#include "tpl_memmap.h"
TASK(Tfond)
{
	tab_trace[j] = 22 + 100 * (cpt_cycle - 1);
	j++;
	cpt_cycle++;
	ActivateTask(T1);
	tab_trace[j] = 22 + 100 * (cpt_cycle - 1);
	j++;
	cpt_cycle++;
	ActivateTask(T1);
	tab_trace[j] = 22 + 100 * (cpt_cycle - 1);
	j++;
	cpt_cycle++;
	ActivateTask(T1);
	tab_trace[j] = 22 + 100 * (cpt_cycle - 1);
	j++;
	cpt_cycle++;
	ActivateTask(T1);
	tab_trace[j] = 22 + 100 * (cpt_cycle - 1);
	j++;
	TerminateTask();
}
#define APP_Task_Tfond_STOP_SEC_CODE
#include "tpl_memmap.h"


