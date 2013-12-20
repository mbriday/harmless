
#include <stdio.h>
#include <hadl-types.h>
#include <hadl-custom.h>
#include <hadl-array.h>
#include <hadl-srec.h>

extern HADL_Array_t* Memory_mem;
extern HADL_Array_t* Registers_gpr;
extern HADL_Int16 Fetcher_pc;
extern HADL_Int8 StatusRegister_ccr;

#include <XGateRunnerHeader.hadl.cpp>

#define STEPS 200

int main()
{
   int i;
   
   XGate_create();

   FILE* file = fopen("fibo.srec", "r");
   HADL_Srec_readArrayFromFile(file, Memory_mem, 1, 1, 0);
   fclose(file);

   HADL_PipelineData_t* pipeData = XGate_pFE_init();

#if HADL_DEBUG
   HADL_Array_print<HADL_Int8>(Memory_mem);
   HADL_Array_print<HADL_Int16>(Registers_gpr);
#endif

   for(i=0;i<STEPS;i++)
   {
      
#if HADL_DEBUG
      printf("========================= STEP %d\n", i);
#endif

      XGate_pFE_step(pipeData, i);

#if HADL_DEBUG
      HADL_Array_print<HADL_Int8>(Memory_mem);
      HADL_Array_print<HADL_Int16>(Registers_gpr);
      printf("PC = %x\n", Fetcher_pc);
      printf("CCR = %x\n", StatusRegister_ccr);
#endif
   }

   return 0;
}

