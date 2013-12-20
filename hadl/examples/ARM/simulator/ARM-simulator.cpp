
#include <stdio.h>
#include "hadl-types.h"
#include "hadl-custom.h"
#include "hadl-array.h"
#include "hadl-srec.h"

extern HADL_Array_t* Memory_memory;
extern HADL_Array_t* Registers_gpr;

#include <ARMRunnerHeader.hadl.cpp>

int main()
{
   int i;
   
   ARM_create();

   FILE* file = fopen("fibo.srec", "r");
   HADL_Srec_readArrayFromFile(file, Memory_memory, 1, 0, 0);
   fclose(file);

   HADL_PipelineData_t* pipeData = ARM_pFDE_init();

#if HADL_DEBUG
   HADL_Array_print<HADL_Int8>(Memory_memory);
   HADL_Array_print<HADL_Int32>(Registers_gpr);
#endif

   for(i=0;i<80;i++)
   {
      
#if HADL_DEBUG
      printf("========================= STEP %d\n", i);
#endif

      ARM_pFDE_step(pipeData, i);

#if HADL_DEBUG
      HADL_Array_print<HADL_Int8>(Memory_memory);
      HADL_Array_print<HADL_Int32>(Registers_gpr);
#endif
   }

   return 0;
}

