
#ifndef __HADL_SCHEDULER__
#define __HADL_SCHEDULER__

#include "hadl-custom.h"

typedef struct {
   char *portName;
   int portId;
   int interface;
   unsigned numberOfOperations;
   int *operations;
} HADL_Port_t;

typedef struct {
   HADL_Port_t *port;
   int isReusable;
} HADL_PortUsage_t;

typedef struct {
   char *name;
   unsigned numberOfSuccessors;
   unsigned *successors;
   unsigned numberOfPortUsages;
   HADL_PortUsage_t *portUsages;
} HADL_Stage_t;

typedef struct {
   char *name;
   unsigned numberOfStages;
   HADL_Stage_t *stages;
} HADL_Pipeline_t;

typedef struct {
   HADL_Pipeline_t *pipeline;
   HADL_Time_t **stages;
   HADL_Time_t **resources;
} HADL_PipelineData_t;

#define HADL_RESOURCE_EMPTY -1

HADL_PipelineData_t* HADL_Scheduler_newPipelineData(HADL_Pipeline_t* pipe, unsigned nstages, unsigned nres);
void HADL_Scheduler_schedule(HADL_PipelineData_t *pipe, HADL_Time_t *time, HADL_Time_t startTime, int *stage, void *instr, int iface, int op);

#endif

