
#include "hadl-scheduler.h"
#include "hadl-debug.h"

#include <stdlib.h>

HADL_PipelineData_t* HADL_Scheduler_newPipelineData(HADL_Pipeline_t* pipe, unsigned nstages, unsigned nres) {
   int t,r;
   HADL_PipelineData_t *result = (HADL_PipelineData_t*)malloc(sizeof(HADL_PipelineData_t));
   
   result->pipeline = pipe;
   result->stages = (HADL_Time_t**)malloc(HADL_SIMULATION_CYCLES*sizeof(HADL_Time_t*));
   result->resources = (HADL_Time_t**)malloc(HADL_SIMULATION_CYCLES*sizeof(HADL_Time_t*));

   for(t=0;t<HADL_SIMULATION_CYCLES;t++) {
      result->stages[t] = (HADL_Time_t*)malloc(nstages*sizeof(HADL_Time_t));

      for(r=0;r<nstages;r++)
         result->stages[t][r] = (HADL_Time_t)HADL_RESOURCE_EMPTY;
      
      result->resources[t] = (HADL_Time_t*)malloc(nres*sizeof(HADL_Time_t));

      for(r=0;r<nres;r++)
         result->resources[t][r] = (HADL_Time_t)HADL_RESOURCE_EMPTY;
   }

   return result;
}

/* TODO multiple-branch pipelines */
static void HADL_Scheduler_nextStage(HADL_Pipeline_t*pipe, int *stage) {
   *stage = pipe->stages[*stage].successors[0];
}

static int HADL_Scheduler_hasOperation(HADL_PipelineData_t* pipe, HADL_Time_t time, HADL_Time_t startTime, int stage, int iface, int op) {
   int u,q;
   HADL_Stage_t *stageRep = &pipe->pipeline->stages[stage];
   for(u=0;u<stageRep->numberOfPortUsages;u++)
      if(stageRep->portUsages[u].port->interface == iface)
         for(q=0;q<stageRep->portUsages[u].port->numberOfOperations;q++)
            if(stageRep->portUsages[u].port->operations[q] == op) {
               int portId = stageRep->portUsages[u].port->portId;
               /*
                * If resource is already taken by the same instruction,
                * and resource is not reusable,
                * ignore it
                * else, OK
                */
               if(pipe->resources[time][portId] == HADL_RESOURCE_EMPTY ||  /* if resource is not taken OR */
                  pipe->resources[time][portId] != startTime ||            /* resource is taken by someone else OR */
                  stageRep->portUsages[u].isReusable)                      /* resource is reusable */
                  return 1;                                                /* then resource found */
            }

   return 0;
}

static int HADL_Scheduler_takeResource(HADL_PipelineData_t* pipe, HADL_Time_t time, HADL_Time_t startTime, int stage, int iface, int op) {
   int u,q;
   HADL_Stage_t *stageRep = &pipe->pipeline->stages[stage];
   for(u=0;u<stageRep->numberOfPortUsages;u++)
      if(stageRep->portUsages[u].port->interface == iface)
         for(q=0;q<stageRep->portUsages[u].port->numberOfOperations;q++)
            if(stageRep->portUsages[u].port->operations[q] == op) {
               int portId = stageRep->portUsages[u].port->portId;
               if(pipe->resources[time][portId] == HADL_RESOURCE_EMPTY) {
                  printf("Port : %s | ", pipe->pipeline->stages[stage].portUsages[u].port->portName);
                  pipe->resources[time][portId] = startTime;
                  return 1;
               }
            }

   return 0;
}

void HADL_Scheduler_schedule(HADL_PipelineData_t *pipe, HADL_Time_t *time, HADL_Time_t startTime, int *stage, void *instr, int iface, int op) {
   if(*stage != -1) {
      /*
       * Determine if current stage has the given operation.
       * If not, try next stage and increment time.
       */
      while(!HADL_Scheduler_hasOperation(pipe, *time, startTime, *stage, iface, op)) {
         HADL_Scheduler_nextStage(pipe->pipeline, stage);
         ++ *time;
      }

      /*
       * If stage is already occupied by another instruction, wait.
       */
      while(pipe->stages[*time][*stage] != HADL_RESOURCE_EMPTY &&
            pipe->stages[*time][*stage] != startTime)
         ++ *time;

      /*
       * Occupy stage.
       */
      pipe->stages[*time][*stage] = startTime;
      
      printf("(SCH) Stage: %s | ", pipe->pipeline->stages[*stage].name);

      /*
       * Wait for a resource to be available and take it.
       */
      while(!HADL_Scheduler_takeResource(pipe, *time, startTime, *stage, iface, op)) {
         ++ *time;
         pipe->stages[*time][*stage] = startTime;
      }
   }

   HADL_Debug_printTime("Time: ", *time);
}

