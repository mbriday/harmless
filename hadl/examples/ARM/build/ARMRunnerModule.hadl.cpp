#ifndef ARMRunnerModule
   
#define ARMRunnerModule
   


#include "stdlib.h"

#include "hadl-fields.h"

#include "hadl-array.h"

#include "hadl-debug.h"

#include "ARMDisassemblerHeader.hadl.cpp"

#include "ARMDecoderHeader.hadl.cpp"

#include "ARMRunnerHeader.hadl.cpp"

HADL_Int32 StatusRegister_cpsr;

HADL_Array_t * Registers_gpr;

HADL_Array_t * Memory_memory;

HADL_Int32 ARM_StatusRegister_getNFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: StatusRegister.getNFlag");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_StatusRegister_iface, ARM_StatusRegister_getNFlag_op);
   
   {
      {
         int _r24[1 ][ 3]= {{31, 31, 1}};
         return HADL_Field_getValue<HADL_Int32,HADL_Int32>(StatusRegister_cpsr, _r24, 1, 0, 0, 1, 0);
      }
   }
}

void ARM_StatusRegister_setNFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 flag) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: StatusRegister.setNFlag");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_StatusRegister_iface, ARM_StatusRegister_setNFlag_op);
   
   {
      {
         int _r37[1 ][ 3]= {{31, 31, 1}};
         HADL_Field_setValue(&StatusRegister_cpsr, flag, _r37, 1);
      }
   }
}

HADL_Int32 ARM_StatusRegister_getZFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: StatusRegister.getZFlag");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_StatusRegister_iface, ARM_StatusRegister_getZFlag_op);
   
   {
      {
         int _r85[1 ][ 3]= {{30, 30, 1}};
         return HADL_Field_getValue<HADL_Int32,HADL_Int32>(StatusRegister_cpsr, _r85, 1, 0, 0, 1, 0);
      }
   }
}

void ARM_StatusRegister_setZFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 flag) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: StatusRegister.setZFlag");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_StatusRegister_iface, ARM_StatusRegister_setZFlag_op);
   
   {
      {
         int _r33[1 ][ 3]= {{30, 30, 1}};
         HADL_Field_setValue(&StatusRegister_cpsr, flag, _r33, 1);
      }
   }
}

HADL_Int32 ARM_StatusRegister_getCFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: StatusRegister.getCFlag");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_StatusRegister_iface, ARM_StatusRegister_getCFlag_op);
   
   {
      {
         int _r22[1 ][ 3]= {{29, 29, 1}};
         return HADL_Field_getValue<HADL_Int32,HADL_Int32>(StatusRegister_cpsr, _r22, 1, 0, 0, 1, 0);
      }
   }
}

void ARM_StatusRegister_setCFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 flag) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: StatusRegister.setCFlag");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_StatusRegister_iface, ARM_StatusRegister_setCFlag_op);
   
   {
      {
         int _r31[1 ][ 3]= {{29, 29, 1}};
         HADL_Field_setValue(&StatusRegister_cpsr, flag, _r31, 1);
      }
   }
}

HADL_Int32 ARM_StatusRegister_getVFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: StatusRegister.getVFlag");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_StatusRegister_iface, ARM_StatusRegister_getVFlag_op);
   
   {
      {
         int _r89[1 ][ 3]= {{28, 28, 1}};
         return HADL_Field_getValue<HADL_Int32,HADL_Int32>(StatusRegister_cpsr, _r89, 1, 0, 0, 1, 0);
      }
   }
}

void ARM_StatusRegister_setVFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 flag) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: StatusRegister.setVFlag");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_StatusRegister_iface, ARM_StatusRegister_setVFlag_op);
   
   {
      {
         int _r7[1 ][ 3]= {{28, 28, 1}};
         HADL_Field_setValue(&StatusRegister_cpsr, flag, _r7, 1);
      }
   }
}

HADL_Int32 ARM_Registers_getValue(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 index) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Registers.getValue");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Registers_iface, ARM_Registers_getValue_op);
   
   {
      {
         
         if(index==15) {
            {
               return HADL_Array_getValue<unsigned HADL_Int32,HADL_Int32>(Registers_gpr, index, _time)+4;
            }
         }
         else {
            {
               return HADL_Array_getValue<unsigned HADL_Int32,HADL_Int32>(Registers_gpr, index, _time);
            }
         }
      }
   }
}

HADL_Int32 ARM_Registers_getPC(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Registers.getPC");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Registers_iface, ARM_Registers_getPC_op);
   
   {
      {
         return HADL_Array_getValue<unsigned HADL_Int32,HADL_Int32>(Registers_gpr, 15, _time);
      }
   }
}

void ARM_Registers_setValue(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 index, HADL_Int32 value) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Registers.setValue");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Registers_iface, ARM_Registers_setValue_op);
   
   {
      {
         HADL_Array_setValue(Registers_gpr, index, value, _time);
      }
   }
}

HADL_Int32 ARM_Memory_getByte(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int8 ext) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Memory.getByte");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Memory_iface, ARM_Memory_getByte_op);
   
   {
      {
         
         if(ext) {
            {
               return HADL_Array_getValue<HADL_Int8,HADL_Int32>(Memory_memory, address, _time);
            }
         }
         else {
            {
               return HADL_Array_getValue<unsigned HADL_Int8,HADL_Int32>(Memory_memory, address, _time);
            }
         }
      }
   }
}

HADL_Int32 ARM_Memory_getHalfWord(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int8 ext) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Memory.getHalfWord");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Memory_iface, ARM_Memory_getHalfWord_op);
   
   {
      {
         
         if(ext) {
            {
               return HADL_Array_getValue<unsigned HADL_Int8,HADL_Int32>(Memory_memory, address, _time)|HADL_Array_getValue<HADL_Int8,HADL_Int32>(Memory_memory, address+1, _time)<<8;
            }
         }
         else {
            {
               return HADL_Array_getValue<unsigned HADL_Int8,HADL_Int32>(Memory_memory, address, _time)|HADL_Array_getValue<unsigned HADL_Int8,HADL_Int32>(Memory_memory, address+1, _time)<<8;
            }
         }
      }
   }
}

HADL_Int32 ARM_Memory_getWord(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Memory.getWord");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Memory_iface, ARM_Memory_getWord_op);
   
   {
      {
         return HADL_Array_getValue<unsigned HADL_Int8,HADL_Int32>(Memory_memory, address, _time)|HADL_Array_getValue<unsigned HADL_Int8,HADL_Int32>(Memory_memory, address+1, _time)<<8|HADL_Array_getValue<unsigned HADL_Int8,HADL_Int32>(Memory_memory, address+2, _time)<<16|HADL_Array_getValue<unsigned HADL_Int8,HADL_Int32>(Memory_memory, address+3, _time)<<24;
      }
   }
}

void ARM_Memory_setByte(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int8 value) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Memory.setByte");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Memory_iface, ARM_Memory_setByte_op);
   
   {
      {
         int _r94[1 ][ 3]= {{7, 0, 1}};
         HADL_Array_setValue(Memory_memory, address, HADL_Field_getValue<HADL_Int8,HADL_Int32>(value, _r94, 1, 0, 0, 1, 0), _time);
      }
   }
}

void ARM_Memory_setHalfWord(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int16 value) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Memory.setHalfWord");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Memory_iface, ARM_Memory_setHalfWord_op);
   
   {
      {
         int _r92[1 ][ 3]= {{7, 0, 1}};
         HADL_Array_setValue(Memory_memory, address, HADL_Field_getValue<HADL_Int16,HADL_Int32>(value, _r92, 1, 0, 0, 1, 0), _time);
      }
      {
         int _r82[1 ][ 3]= {{15, 8, 1}};
         HADL_Array_setValue(Memory_memory, address+1, HADL_Field_getValue<HADL_Int16,HADL_Int32>(value, _r82, 1, 0, 0, 1, 0), _time);
      }
   }
}

void ARM_Memory_setWord(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int32 value) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Memory.setWord");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Memory_iface, ARM_Memory_setWord_op);
   
   {
      {
         int _r98[1 ][ 3]= {{7, 0, 1}};
         HADL_Array_setValue(Memory_memory, address, HADL_Field_getValue<HADL_Int32,HADL_Int32>(value, _r98, 1, 0, 0, 1, 0), _time);
      }
      {
         int _r48[1 ][ 3]= {{15, 8, 1}};
         HADL_Array_setValue(Memory_memory, address+1, HADL_Field_getValue<HADL_Int32,HADL_Int32>(value, _r48, 1, 0, 0, 1, 0), _time);
      }
      {
         int _r73[1 ][ 3]= {{23, 16, 1}};
         HADL_Array_setValue(Memory_memory, address+2, HADL_Field_getValue<HADL_Int32,HADL_Int32>(value, _r73, 1, 0, 0, 1, 0), _time);
      }
      {
         int _r30[1 ][ 3]= {{31, 24, 1}};
         HADL_Array_setValue(Memory_memory, address+3, HADL_Field_getValue<HADL_Int32,HADL_Int32>(value, _r30, 1, 0, 0, 1, 0), _time);
      }
   }
}

void ARM_ALU_updateCpsrWithResult(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 r) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.updateCpsrWithResult");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_updateCpsrWithResult_op);
   
   {
      {
         ARM_StatusRegister_setNFlag(_pipeData, _time, _startTime, _stage, _instr, 0, r<0);
      }
      {
         ARM_StatusRegister_setZFlag(_pipeData, _time, _startTime, _stage, _instr, 0, r==0);
      }
   }
}

void ARM_ALU_clearCpsrCV(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.clearCpsrCV");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_clearCpsrCV_op);
   
   {
      {
         ARM_StatusRegister_setCFlag(_pipeData, _time, _startTime, _stage, _instr, 0, 0);
      }
      {
         ARM_StatusRegister_setVFlag(_pipeData, _time, _startTime, _stage, _instr, 0, 0);
      }
   }
}

HADL_Int32 ARM_ALU_movOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.movOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_movOp_op);
   
   {
      {
         return a;
      }
   }
}

HADL_Int32 ARM_ALU_movOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.movOpUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_movOpUpdateCpsr_op);
   
   {
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, a);
      }
      {
         ARM_ALU_clearCpsrCV(_pipeData, _time, _startTime, _stage, _instr, 1);
      }
      {
         return a;
      }
   }
}

HADL_Int32 ARM_ALU_notOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.notOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_notOp_op);
   
   {
      {
         return~a;
      }
   }
}

HADL_Int32 ARM_ALU_notOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.notOpUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_notOpUpdateCpsr_op);
   
   {
      {
         result=~a;
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         ARM_ALU_clearCpsrCV(_pipeData, _time, _startTime, _stage, _instr, 1);
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_ALU_andOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.andOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_andOp_op);
   
   {
      {
         return a&b;
      }
   }
}

HADL_Int32 ARM_ALU_andOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.andOpUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_andOpUpdateCpsr_op);
   
   {
      {
         result=a&b;
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         ARM_ALU_clearCpsrCV(_pipeData, _time, _startTime, _stage, _instr, 1);
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_ALU_orOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.orOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_orOp_op);
   
   {
      {
         return a|b;
      }
   }
}

HADL_Int32 ARM_ALU_orOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.orOpUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_orOpUpdateCpsr_op);
   
   {
      {
         result=a|b;
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         ARM_ALU_clearCpsrCV(_pipeData, _time, _startTime, _stage, _instr, 1);
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_ALU_eorOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.eorOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_eorOp_op);
   
   {
      {
         return a^b;
      }
   }
}

HADL_Int32 ARM_ALU_eorOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.eorOpUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_eorOpUpdateCpsr_op);
   
   {
      {
         result=a^b;
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         ARM_ALU_clearCpsrCV(_pipeData, _time, _startTime, _stage, _instr, 1);
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_ALU_bicOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.bicOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_bicOp_op);
   
   {
      {
         return a&~b;
      }
   }
}

HADL_Int32 ARM_ALU_bicOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.bicOpUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_bicOpUpdateCpsr_op);
   
   {
      {
         result=a&~b;
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         ARM_ALU_clearCpsrCV(_pipeData, _time, _startTime, _stage, _instr, 1);
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_ALU_subOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.subOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_subOp_op);
   
   {
      {
         return a-b;
      }
   }
}

HADL_Int32 ARM_ALU_subOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.subOpUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_subOpUpdateCpsr_op);
   
   {
      {
         result=a-b;
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         int _r70[1 ][ 3]= {{31, 31, 1}};
         int _r41[1 ][ 3]= {{31, 31, 1}};
         int _r84[1 ][ 3]= {{31, 31, 1}};
         int _r8[1 ][ 3]= {{31, 31, 1}};
         int _r66[1 ][ 3]= {{31, 31, 1}};
         ARM_StatusRegister_setCFlag(_pipeData, _time, _startTime, _stage, _instr, 0, (HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r70, 1, 0, 0, 1, 0)|~HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r41, 1, 0, 0, 1, 0))&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r84, 1, 0, 0, 1, 0)|HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r8, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r66, 1, 0, 0, 1, 0));
      }
      {
         int _r60[1 ][ 3]= {{31, 31, 1}};
         int _r61[1 ][ 3]= {{31, 31, 1}};
         int _r34[1 ][ 3]= {{31, 31, 1}};
         int _r87[1 ][ 3]= {{31, 31, 1}};
         int _r47[1 ][ 3]= {{31, 31, 1}};
         int _r35[1 ][ 3]= {{31, 31, 1}};
         ARM_StatusRegister_setVFlag(_pipeData, _time, _startTime, _stage, _instr, 0, HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r60, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r61, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r34, 1, 0, 0, 1, 0)|~HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r87, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r47, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r35, 1, 0, 0, 1, 0));
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_ALU_subOpWithCarry(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.subOpWithCarry");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_subOpWithCarry_op);
   
   {
      {
         return a-b+ARM_StatusRegister_getCFlag(_pipeData, _time, _startTime, _stage, _instr, 0)-1;
      }
   }
}

HADL_Int32 ARM_ALU_subOpWithCarryUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.subOpWithCarryUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_subOpWithCarryUpdateCpsr_op);
   
   {
      {
         result=a-b+ARM_StatusRegister_getCFlag(_pipeData, _time, _startTime, _stage, _instr, 0)-1;
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         int _r54[1 ][ 3]= {{31, 31, 1}};
         int _r39[1 ][ 3]= {{31, 31, 1}};
         int _r71[1 ][ 3]= {{31, 31, 1}};
         int _r62[1 ][ 3]= {{31, 31, 1}};
         int _r63[1 ][ 3]= {{31, 31, 1}};
         ARM_StatusRegister_setCFlag(_pipeData, _time, _startTime, _stage, _instr, 0, (HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r54, 1, 0, 0, 1, 0)|~HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r39, 1, 0, 0, 1, 0))&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r71, 1, 0, 0, 1, 0)|HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r62, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r63, 1, 0, 0, 1, 0));
      }
      {
         int _r3[1 ][ 3]= {{31, 31, 1}};
         int _r86[1 ][ 3]= {{31, 31, 1}};
         int _r17[1 ][ 3]= {{31, 31, 1}};
         int _r57[1 ][ 3]= {{31, 31, 1}};
         int _r45[1 ][ 3]= {{31, 31, 1}};
         int _r65[1 ][ 3]= {{31, 31, 1}};
         ARM_StatusRegister_setVFlag(_pipeData, _time, _startTime, _stage, _instr, 0, HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r3, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r86, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r17, 1, 0, 0, 1, 0)|~HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r57, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r45, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r65, 1, 0, 0, 1, 0));
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_ALU_addOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.addOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_addOp_op);
   
   {
      {
         return a+b;
      }
   }
}

HADL_Int32 ARM_ALU_addOpWithCarry(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.addOpWithCarry");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_addOpWithCarry_op);
   
   {
      {
         return a+b+ARM_StatusRegister_getCFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
      }
   }
}

HADL_Int32 ARM_ALU_addOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.addOpUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_addOpUpdateCpsr_op);
   
   {
      {
         result=a+b;
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         int _r10[1 ][ 3]= {{31, 31, 1}};
         int _r29[1 ][ 3]= {{31, 31, 1}};
         int _r74[1 ][ 3]= {{31, 31, 1}};
         int _r81[1 ][ 3]= {{31, 31, 1}};
         int _r16[1 ][ 3]= {{31, 31, 1}};
         ARM_StatusRegister_setCFlag(_pipeData, _time, _startTime, _stage, _instr, 0, (HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r10, 1, 0, 0, 1, 0)|HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r29, 1, 0, 0, 1, 0))&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r74, 1, 0, 0, 1, 0)|HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r81, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r16, 1, 0, 0, 1, 0));
      }
      {
         int _r53[1 ][ 3]= {{31, 31, 1}};
         int _r25[1 ][ 3]= {{31, 31, 1}};
         int _r28[1 ][ 3]= {{31, 31, 1}};
         int _r32[1 ][ 3]= {{31, 31, 1}};
         int _r27[1 ][ 3]= {{31, 31, 1}};
         int _r64[1 ][ 3]= {{31, 31, 1}};
         ARM_StatusRegister_setVFlag(_pipeData, _time, _startTime, _stage, _instr, 0, HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r53, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r25, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r28, 1, 0, 0, 1, 0)|~HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r32, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r27, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r64, 1, 0, 0, 1, 0));
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_ALU_addOpWithCarryUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: ALU.addOpWithCarryUpdateCpsr");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_ALU_iface, ARM_ALU_addOpWithCarryUpdateCpsr_op);
   
   {
      {
         result=a+b+ARM_StatusRegister_getCFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
      }
      {
         ARM_ALU_updateCpsrWithResult(_pipeData, _time, _startTime, _stage, _instr, 1, result);
      }
      {
         int _r2[1 ][ 3]= {{31, 31, 1}};
         int _r38[1 ][ 3]= {{31, 31, 1}};
         int _r72[1 ][ 3]= {{31, 31, 1}};
         int _r52[1 ][ 3]= {{31, 31, 1}};
         int _r4[1 ][ 3]= {{31, 31, 1}};
         ARM_StatusRegister_setCFlag(_pipeData, _time, _startTime, _stage, _instr, 0, (HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r2, 1, 0, 0, 1, 0)|HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r38, 1, 0, 0, 1, 0))&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r72, 1, 0, 0, 1, 0)|HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r52, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r4, 1, 0, 0, 1, 0));
      }
      {
         int _r58[1 ][ 3]= {{31, 31, 1}};
         int _r76[1 ][ 3]= {{31, 31, 1}};
         int _r19[1 ][ 3]= {{31, 31, 1}};
         int _r23[1 ][ 3]= {{31, 31, 1}};
         int _r20[1 ][ 3]= {{31, 31, 1}};
         int _r21[1 ][ 3]= {{31, 31, 1}};
         ARM_StatusRegister_setVFlag(_pipeData, _time, _startTime, _stage, _instr, 0, HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r58, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r76, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r19, 1, 0, 0, 1, 0)|~HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r23, 1, 0, 0, 1, 0)&~HADL_Field_getValue<HADL_Int32,HADL_Int32>(b, _r20, 1, 0, 0, 1, 0)&HADL_Field_getValue<HADL_Int32,HADL_Int32>(result, _r21, 1, 0, 0, 1, 0));
      }
      {
         return result;
      }
   }
}

HADL_Int32 ARM_Shifter_lslOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Shifter.lslOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Shifter_iface, ARM_Shifter_lslOp_op);
   
   {
      {
         return a<<b;
      }
   }
}

HADL_Int32 ARM_Shifter_lsrOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Shifter.lsrOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Shifter_iface, ARM_Shifter_lsrOp_op);
   
   {
      {
         int _r77[1 ][ 3]= {{31, b, 1}};
         return HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r77, 1, 0, 0, 1, 0);
      }
   }
}

HADL_Int32 ARM_Shifter_asrOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Shifter.asrOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Shifter_iface, ARM_Shifter_asrOp_op);
   
   {
      {
         return a>>b;
      }
   }
}

HADL_Int32 ARM_Shifter_rorOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Shifter.rorOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Shifter_iface, ARM_Shifter_rorOp_op);
   
   {
      {
         int _r95[1 ][ 3]= {{31, b, 1}};
         return HADL_Field_getValue<HADL_Int32,HADL_Int32>(a, _r95, 1, 0, 0, 1, 0)|a<<32-b;
      }
   }
}

HADL_Int32 ARM_Shifter_rrxOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Shifter.rrxOp");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Shifter_iface, ARM_Shifter_rrxOp_op);
   
   {
      
   }
}

void ARM_Fetcher_reset(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline) {
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Fetcher.reset");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Fetcher_iface, ARM_Fetcher_reset_op);
   
   {
      {
         ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, 15, 0);
      }
   }
}

HADL_Int32 ARM_Fetcher_next(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline) {
   HADL_Int32 pc;
   {
      HADL_Debug_printMessage("(OPR) Executing operation: Fetcher.next");
   }
   
   if(_inline)HADL_Scheduler_schedule(_pipeData, _time, _startTime, _stage, _instr, ARM_Fetcher_iface, ARM_Fetcher_next_op);
   
   {
      {
         pc=ARM_Registers_getPC(_pipeData, _time, _startTime, _stage, _instr, 0);
      }
      {
         ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, 15, pc+4);
      }
      {
         return ARM_Memory_getWord(_pipeData, _time, _startTime, _stage, _instr, 0, pc);
      }
   }
}

void ARM_pFDE_step(HADL_PipelineData_t * _pipeData, HADL_Time_t _dtime) {
   int _dstage=ARM_pFDE_Fetch_stage;
   int * _stage=&_dstage;
   HADL_Time_t * _time=&_dtime;
   HADL_Time_t _startTime=_dtime;
   void * _instr=NULL;
   struct ARM_Instruction_st * _idata=ARM_Instruction_decode(ARM_Fetcher_next(_pipeData, _time, _startTime, _stage, _instr, 0), NULL, ARM_Root_path);
   char _buffer[HADL_BUFFER_SIZE];
   ARM_Instruction_disassemble(_idata, _buffer, 0, NULL);
   HADL_Debug_asmDump(_buffer);
   ARM_Instruction_run(_pipeData, _time, _startTime, _stage, _idata, _idata);
}

void ARM_Instruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_Instruction_st * _this) {
   HADL_Int8 condIsTrue;
   {
      HADL_Debug_printMessage("(FRG) Running behavior: Instruction");
   }
   ARM_Condition_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_Condition_st * )(_this->chunk_ARM_Condition_st), &condIsTrue);
   
   if(condIsTrue)ARM_InstructionKind_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_InstructionKind_st * )(_this->chunk_ARM_InstructionKind_st));
   
}

void ARM_Condition_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_Condition_st * _this, HADL_Int8 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: Condition");
   }
   switch(_this->_choice) {
      case ARM_Condition_EQ_choice:
         {
            {
               * result=ARM_StatusRegister_getZFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_NE_choice:
         {
            {
               * result=!ARM_StatusRegister_getZFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_CS_choice:
         {
            {
               * result=ARM_StatusRegister_getCFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_CC_choice:
         {
            {
               * result=!ARM_StatusRegister_getCFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_MI_choice:
         {
            {
               * result=ARM_StatusRegister_getNFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_PL_choice:
         {
            {
               * result=!ARM_StatusRegister_getNFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_VS_choice:
         {
            {
               * result=ARM_StatusRegister_getVFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_VC_choice:
         {
            {
               * result=!ARM_StatusRegister_getVFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_HI_choice:
         {
            {
               * result=ARM_StatusRegister_getCFlag(_pipeData, _time, _startTime, _stage, _instr, 0)&&!ARM_StatusRegister_getZFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_LS_choice:
         {
            {
               * result=!ARM_StatusRegister_getCFlag(_pipeData, _time, _startTime, _stage, _instr, 0)||ARM_StatusRegister_getZFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_GE_choice:
         {
            {
               * result=ARM_StatusRegister_getNFlag(_pipeData, _time, _startTime, _stage, _instr, 0)==ARM_StatusRegister_getVFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_LT_choice:
         {
            {
               * result=ARM_StatusRegister_getNFlag(_pipeData, _time, _startTime, _stage, _instr, 0)!=ARM_StatusRegister_getVFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_GT_choice:
         {
            {
               * result=!ARM_StatusRegister_getZFlag(_pipeData, _time, _startTime, _stage, _instr, 0)&&ARM_StatusRegister_getNFlag(_pipeData, _time, _startTime, _stage, _instr, 0)==ARM_StatusRegister_getVFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_LE_choice:
         {
            {
               * result=ARM_StatusRegister_getZFlag(_pipeData, _time, _startTime, _stage, _instr, 0)||ARM_StatusRegister_getNFlag(_pipeData, _time, _startTime, _stage, _instr, 0)!=ARM_StatusRegister_getVFlag(_pipeData, _time, _startTime, _stage, _instr, 0);
            }
         }
         break;
      
      case ARM_Condition_AL_choice:
         {
            {
               * result=1;
            }
         }
         break;
      
      case ARM_Condition_NV_choice:
         {
            {
               * result=0;
            }
         }
         break;
      
   }
}

void ARM_InstructionKind_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_InstructionKind_st * _this) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: InstructionKind");
   }
   switch(_this->_choice) {
      case ARM_InstructionKind_DataProcessingInstruction_choice:
         ARM_DataProcessingInstruction_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_DataProcessingInstruction_st * )(_this->_target));
         break;
      
      case ARM_InstructionKind_LoadStoreInstruction_choice:
         ARM_LoadStoreInstruction_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_LoadStoreInstruction_st * )(_this->_target));
         break;
      
      case ARM_InstructionKind_LoadStoreMultipleInstruction_choice:
         ARM_LoadStoreMultipleInstruction_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_LoadStoreMultipleInstruction_st * )(_this->_target));
         break;
      
      case ARM_InstructionKind_BranchInstruction_choice:
         ARM_BranchInstruction_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_BranchInstruction_st * )(_this->_target));
         break;
      
   }
}

void ARM_DataProcessingInstruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_DataProcessingInstruction_st * _this) {
   HADL_Int32 valueOfRn;
   HADL_Int32 valueOfOperand2;
   {
      HADL_Debug_printMessage("(FRG) Running behavior: DataProcessingInstruction");
   }
   ARM_GprRead_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_GprRead_st * )(_this->chunk_ARM_GprRead_st), &valueOfRn);
   ARM_FlexibleOperand2_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_FlexibleOperand2_st * )(_this->chunk_ARM_FlexibleOperand2_st), &valueOfOperand2);
   ARM_DataProcessingOperation_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_DataProcessingOperation_st * )(_this->chunk_ARM_DataProcessingOperation_st), valueOfRn, valueOfOperand2);
}

void ARM_GprRead_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_GprRead_st * _this, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: GprRead");
   }
   {
      {
         * result=ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, _this->reg);
      }
   }
}

void ARM_DataProcessingOperation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_DataProcessingOperation_st * _this, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: DataProcessingOperation");
   }
   switch(_this->_choice) {
      case ARM_DataProcessingOperation_CalculationOperation_choice:
         ARM_CalculationOperation_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_CalculationOperation_st * )(_this->_target), a, b);
         break;
      
      case ARM_DataProcessingOperation_ComparisonOperation_choice:
         ARM_ComparisonOperation_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_ComparisonOperation_st * )(_this->_target), a, b);
         break;
      
   }
}

void ARM_CalculationOperation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_CalculationOperation_st * _this, HADL_Int32 a, HADL_Int32 b) {
   HADL_Int32 result;
   {
      HADL_Debug_printMessage("(FRG) Running behavior: CalculationOperation");
   }
   switch(_this->_choice) {
      case ARM_CalculationOperation_AND_choice:
         {
            {
               result=ARM_ALU_andOp(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_ANDS_choice:
         {
            {
               result=ARM_ALU_andOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_EOR_choice:
         {
            {
               result=ARM_ALU_eorOp(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_EORS_choice:
         {
            {
               result=ARM_ALU_eorOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_SUB_choice:
         {
            {
               result=ARM_ALU_subOp(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_SUBS_choice:
         {
            {
               result=ARM_ALU_subOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_RSB_choice:
         {
            {
               result=ARM_ALU_subOp(_pipeData, _time, _startTime, _stage, _instr, 0, b, a);
            }
         }
         break;
      
      case ARM_CalculationOperation_RSBS_choice:
         {
            {
               result=ARM_ALU_subOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, b, a);
            }
         }
         break;
      
      case ARM_CalculationOperation_ADD_choice:
         {
            {
               result=ARM_ALU_addOp(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_ADDS_choice:
         {
            {
               result=ARM_ALU_addOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_ADC_choice:
         {
            {
               result=ARM_ALU_addOpWithCarry(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_ADCS_choice:
         {
            {
               result=ARM_ALU_addOpWithCarryUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_SBC_choice:
         {
            {
               result=ARM_ALU_subOpWithCarry(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_SBCS_choice:
         {
            {
               result=ARM_ALU_subOpWithCarryUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_RSC_choice:
         {
            {
               result=ARM_ALU_subOpWithCarry(_pipeData, _time, _startTime, _stage, _instr, 0, b, a);
            }
         }
         break;
      
      case ARM_CalculationOperation_RSCS_choice:
         {
            {
               result=ARM_ALU_subOpWithCarryUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, b, a);
            }
         }
         break;
      
      case ARM_CalculationOperation_ORR_choice:
         {
            {
               result=ARM_ALU_orOp(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_ORRS_choice:
         {
            {
               result=ARM_ALU_orOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_MOV_choice:
         {
            {
               result=ARM_ALU_movOp(_pipeData, _time, _startTime, _stage, _instr, 0, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_MOVS_choice:
         {
            {
               result=ARM_ALU_movOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_BIC_choice:
         {
            {
               result=ARM_ALU_bicOp(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_BICS_choice:
         {
            {
               result=ARM_ALU_bicOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_MVN_choice:
         {
            {
               result=ARM_ALU_notOp(_pipeData, _time, _startTime, _stage, _instr, 0, b);
            }
         }
         break;
      
      case ARM_CalculationOperation_MVNS_choice:
         {
            {
               result=ARM_ALU_notOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, b);
            }
         }
         break;
      
   }
   {
      {
         ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, _this->rd, result);
      }
   }
}

void ARM_ComparisonOperation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ComparisonOperation_st * _this, HADL_Int32 a, HADL_Int32 b) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: ComparisonOperation");
   }
   switch(_this->_choice) {
      case ARM_ComparisonOperation_TST_choice:
         {
            {
               ARM_ALU_andOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_ComparisonOperation_TEQ_choice:
         {
            {
               ARM_ALU_eorOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_ComparisonOperation_CMP_choice:
         {
            {
               ARM_ALU_subOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
      case ARM_ComparisonOperation_CMN_choice:
         {
            {
               ARM_ALU_addOpUpdateCpsr(_pipeData, _time, _startTime, _stage, _instr, 0, a, b);
            }
         }
         break;
      
   }
}

void ARM_FlexibleOperand2_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_FlexibleOperand2_st * _this, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: FlexibleOperand2");
   }
   switch(_this->_choice) {
      case ARM_FlexibleOperand2_Immediate_choice:
         ARM_Immediate_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_Immediate_st * )(_this->_target), result);
         break;
      
      case ARM_FlexibleOperand2_RotatedImmediate_choice:
         ARM_RotatedImmediate_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_RotatedImmediate_st * )(_this->_target), result);
         break;
      
      case ARM_FlexibleOperand2_GprRead_choice:
         ARM_GprRead_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_GprRead_st * )(_this->_target), result);
         break;
      
      case ARM_FlexibleOperand2_ShiftedRegister_choice:
         ARM_ShiftedRegister_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_ShiftedRegister_st * )(_this->_target), result);
         break;
      
   }
}

void ARM_Immediate_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_Immediate_st * _this, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: Immediate");
   }
   {
      {
         * result=_this->val;
      }
   }
}

void ARM_RotatedImmediate_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_RotatedImmediate_st * _this, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: RotatedImmediate");
   }
   {
      {
         * result=ARM_Shifter_rorOp(_pipeData, _time, _startTime, _stage, _instr, 0, _this->val, _this->rot);
      }
   }
}

void ARM_ShiftedRegister_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftedRegister_st * _this, HADL_Int32 * result) {
   HADL_Int32 valueOfRm;
   {
      HADL_Debug_printMessage("(FRG) Running behavior: ShiftedRegister");
   }
   ARM_GprRead_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_GprRead_st * )(_this->chunk_ARM_GprRead_st), &valueOfRm);
   ARM_ShiftSpecification_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_ShiftSpecification_st * )(_this->chunk_ARM_ShiftSpecification_st), valueOfRm, result);
}

void ARM_ShiftSpecification_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftSpecification_st * _this, HADL_Int32 value, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: ShiftSpecification");
   }
   switch(_this->_choice) {
      case ARM_ShiftSpecification_RRX_choice:
         {
            {
               * result=ARM_Shifter_rrxOp(_pipeData, _time, _startTime, _stage, _instr, 0, value);
            }
         }
         break;
      
      case ARM_ShiftSpecification_ShiftOperation_choice:
         ARM_ShiftOperation_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_ShiftOperation_st * )(_this->_target), value, result);
         break;
      
   }
}

void ARM_ShiftOperation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftOperation_st * _this, HADL_Int32 value, HADL_Int32 * result) {
   HADL_Int32 amount;
   {
      HADL_Debug_printMessage("(FRG) Running behavior: ShiftOperation");
   }
   ARM_ShiftAmount_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_ShiftAmount_st * )(_this->chunk_ARM_ShiftAmount_st), &amount);
   ARM_ShiftOperationKind_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_ShiftOperationKind_st * )(_this->chunk_ARM_ShiftOperationKind_st), value, amount, result);
}

void ARM_ShiftAmount_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftAmount_st * _this, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: ShiftAmount");
   }
   switch(_this->_choice) {
      case ARM_ShiftAmount_Immediate_choice:
         ARM_Immediate_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_Immediate_st * )(_this->_target), result);
         break;
      
      case ARM_ShiftAmount_GprRead_choice:
         ARM_GprRead_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_GprRead_st * )(_this->_target), result);
         break;
      
   }
}

void ARM_ShiftOperationKind_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftOperationKind_st * _this, HADL_Int32 value, HADL_Int32 amount, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: ShiftOperationKind");
   }
   switch(_this->_choice) {
      case ARM_ShiftOperationKind_LSL_choice:
         {
            {
               * result=ARM_Shifter_lslOp(_pipeData, _time, _startTime, _stage, _instr, 0, value, amount);
            }
         }
         break;
      
      case ARM_ShiftOperationKind_LSR_choice:
         {
            {
               * result=ARM_Shifter_lsrOp(_pipeData, _time, _startTime, _stage, _instr, 0, value, amount);
            }
         }
         break;
      
      case ARM_ShiftOperationKind_ASR_choice:
         {
            {
               * result=ARM_Shifter_asrOp(_pipeData, _time, _startTime, _stage, _instr, 0, value, amount);
            }
         }
         break;
      
      case ARM_ShiftOperationKind_ROR_choice:
         {
            {
               * result=ARM_Shifter_rorOp(_pipeData, _time, _startTime, _stage, _instr, 0, value, amount);
            }
         }
         break;
      
   }
}

void ARM_LoadStoreInstruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreInstruction_st * _this) {
   HADL_Int32 offset;
   HADL_Int32 base;
   HADL_Int32 calculatedAddress;
   HADL_Int32 effectiveAddress;
   {
      HADL_Debug_printMessage("(FRG) Running behavior: LoadStoreInstruction");
   }
   ARM_LoadStoreOffset_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_LoadStoreOffset_st * )(_this->chunk_ARM_LoadStoreOffset_st), &offset);
   ARM_LoadStoreAddressCalculation_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_LoadStoreAddressCalculation_st * )(_this->chunk_ARM_LoadStoreAddressCalculation_st), _this->rn, offset, &base, &calculatedAddress);
   ARM_LoadStoreAddressingMode_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_LoadStoreAddressingMode_st * )(_this->chunk_ARM_LoadStoreAddressingMode_st), _this->rn, base, calculatedAddress, &effectiveAddress);
   ARM_LoadStoreTransfer_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_LoadStoreTransfer_st * )(_this->chunk_ARM_LoadStoreTransfer_st), effectiveAddress, _this->rd);
}

void ARM_LoadStoreOffset_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreOffset_st * _this, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: LoadStoreOffset");
   }
   switch(_this->_choice) {
      case ARM_LoadStoreOffset_Immediate_choice:
         ARM_Immediate_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_Immediate_st * )(_this->_target), result);
         break;
      
      case ARM_LoadStoreOffset_ShiftedRegister_choice:
         ARM_ShiftedRegister_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_ShiftedRegister_st * )(_this->_target), result);
         break;
      
      case ARM_LoadStoreOffset_GprRead_choice:
         ARM_GprRead_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_GprRead_st * )(_this->_target), result);
         break;
      
   }
}

void ARM_LoadStoreAddressCalculation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreAddressCalculation_st * _this, HADL_Int8 rn, HADL_Int32 offset, HADL_Int32 * base, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: LoadStoreAddressCalculation");
   }
   {
      {
         * base=ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, rn);
      }
   }
   switch(_this->_choice) {
      case ARM_LoadStoreAddressCalculation_UP_choice:
         {
            {
               * result=ARM_ALU_addOp(_pipeData, _time, _startTime, _stage, _instr, 0, * base, offset);
            }
         }
         break;
      
      case ARM_LoadStoreAddressCalculation_DOWN_choice:
         {
            {
               * result=ARM_ALU_subOp(_pipeData, _time, _startTime, _stage, _instr, 0, * base, offset);
            }
         }
         break;
      
   }
}

void ARM_LoadStoreAddressingMode_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreAddressingMode_st * _this, HADL_Int8 rn, HADL_Int32 base, HADL_Int32 address, HADL_Int32 * result) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: LoadStoreAddressingMode");
   }
   switch(_this->_choice) {
      case ARM_LoadStoreAddressingMode_PREINDEXED_choice:
         {
            {
               * result=address;
            }
         }
         break;
      
      case ARM_LoadStoreAddressingMode_AUTOINDEXED_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, rn, address);
            }
            {
               * result=address;
            }
         }
         break;
      
      case ARM_LoadStoreAddressingMode_POSTINDEXED_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, rn, address);
            }
            {
               * result=base;
            }
         }
         break;
      
   }
}

void ARM_LoadStoreTransfer_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreTransfer_st * _this, HADL_Int32 addr, HADL_Int8 rd) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: LoadStoreTransfer");
   }
   switch(_this->_choice) {
      case ARM_LoadStoreTransfer_LDR_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, rd, ARM_Memory_getWord(_pipeData, _time, _startTime, _stage, _instr, 0, addr));
            }
         }
         break;
      
      case ARM_LoadStoreTransfer_LDRH_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, rd, ARM_Memory_getHalfWord(_pipeData, _time, _startTime, _stage, _instr, 0, addr, 0));
            }
         }
         break;
      
      case ARM_LoadStoreTransfer_LDRSH_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, rd, ARM_Memory_getHalfWord(_pipeData, _time, _startTime, _stage, _instr, 0, addr, 1));
            }
         }
         break;
      
      case ARM_LoadStoreTransfer_LDRB_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, rd, ARM_Memory_getByte(_pipeData, _time, _startTime, _stage, _instr, 0, addr, 0));
            }
         }
         break;
      
      case ARM_LoadStoreTransfer_LDRSB_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, rd, ARM_Memory_getByte(_pipeData, _time, _startTime, _stage, _instr, 0, addr, 1));
            }
         }
         break;
      
      case ARM_LoadStoreTransfer_STR_choice:
         {
            {
               ARM_Memory_setWord(_pipeData, _time, _startTime, _stage, _instr, 0, addr, ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, rd));
            }
         }
         break;
      
      case ARM_LoadStoreTransfer_STRH_choice:
         {
            {
               ARM_Memory_setHalfWord(_pipeData, _time, _startTime, _stage, _instr, 0, addr, ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, rd));
            }
         }
         break;
      
      case ARM_LoadStoreTransfer_STRB_choice:
         {
            {
               ARM_Memory_setByte(_pipeData, _time, _startTime, _stage, _instr, 0, addr, ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, rd));
            }
         }
         break;
      
   }
}

void ARM_LoadStoreMultipleInstruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreMultipleInstruction_st * _this) {
   HADL_Int32 finalAddress;
   {
      HADL_Debug_printMessage("(FRG) Running behavior: LoadStoreMultipleInstruction");
   }
   ARM_LoadStoreMultipleTransfer_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_LoadStoreMultipleTransfer_st * )(_this->chunk_ARM_LoadStoreMultipleTransfer_st), _this->rn, _this->rl, _this->sr, &finalAddress);
   ARM_LoadStoreMultipleWriteBack_run(_pipeData, _time, _startTime, _stage, _instr, (struct ARM_LoadStoreMultipleWriteBack_st * )(_this->chunk_ARM_LoadStoreMultipleWriteBack_st), _this->rn, finalAddress);
}

void ARM_LoadStoreMultipleTransfer_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreMultipleTransfer_st * _this, HADL_Int8 rn, HADL_Int16 regList, HADL_Int8 sr, HADL_Int32 * finalAddress) {
   HADL_Int32 currentAddress;
   HADL_Int32 nextAddress;
   HADL_Int32 effectiveAddress;
   HADL_Int8 first;
   HADL_Int8 last;
   {
      HADL_Debug_printMessage("(FRG) Running behavior: LoadStoreMultipleTransfer");
   }
   {
      {
         currentAddress=ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, rn);
      }
      {
         
         if(_this->inc) {
            {
               first=0;
            }
            {
               last=15;
            }
         }
         else {
            {
               first=15;
            }
            {
               last=0;
            }
         }
      }
   }
   switch(_this->_choice) {
      case ARM_LoadStoreMultipleTransfer_LOAD_choice:
         {
            int index;
            int _i;
            for(_i=0; (0<=0)?(_i<=0):(_i>=0); (0<=0)?(_i+=1):(_i -= 1)) {
               int _r67[1 ][ 3]= {{first, last, 1}};
               for(index=_r67[_i ][ 0]; (_r67[_i ][ 0]<=_r67[_i ][ 1])?(index<=_r67[_i ][ 1]):(index>=_r67[_i ][ 1]); (_r67[_i ][ 0]<=_r67[_i ][ 1])?(index+=_r67[_i ][ 2]):(index -= _r67[_i ][ 2])) {
                  {
                     int _r90[1 ][ 3]= {{index, index, 1}};
                     
                     if(HADL_Field_getValue<HADL_Int16,HADL_Int32>(regList, _r90, 1, 0, 0, 1, 0)) {
                        {
                           
                           if(_this->inc) {
                              {
                                 nextAddress=currentAddress+4;
                              }
                           }
                           else {
                              {
                                 nextAddress=currentAddress-4;
                              }
                           }
                        }
                        {
                           
                           if(_this->bfore) {
                              {
                                 effectiveAddress=nextAddress;
                              }
                           }
                           else {
                              {
                                 effectiveAddress=currentAddress;
                              }
                           }
                        }
                        {
                           ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, index, ARM_Memory_getWord(_pipeData, _time, _startTime, _stage, _instr, 0, effectiveAddress));
                        }
                        {
                           currentAddress=nextAddress;
                        }
                     }
                     
                  }
               }
            }
         }
         break;
      
      case ARM_LoadStoreMultipleTransfer_STORE_choice:
         {
            int index;
            int _i;
            for(_i=0; (0<=0)?(_i<=0):(_i>=0); (0<=0)?(_i+=1):(_i -= 1)) {
               int _r96[1 ][ 3]= {{first, last, 1}};
               for(index=_r96[_i ][ 0]; (_r96[_i ][ 0]<=_r96[_i ][ 1])?(index<=_r96[_i ][ 1]):(index>=_r96[_i ][ 1]); (_r96[_i ][ 0]<=_r96[_i ][ 1])?(index+=_r96[_i ][ 2]):(index -= _r96[_i ][ 2])) {
                  {
                     int _r56[1 ][ 3]= {{index, index, 1}};
                     
                     if(HADL_Field_getValue<HADL_Int16,HADL_Int32>(regList, _r56, 1, 0, 0, 1, 0)) {
                        {
                           
                           if(_this->inc) {
                              {
                                 nextAddress=currentAddress+4;
                              }
                           }
                           else {
                              {
                                 nextAddress=currentAddress-4;
                              }
                           }
                        }
                        {
                           
                           if(_this->bfore) {
                              {
                                 effectiveAddress=nextAddress;
                              }
                           }
                           else {
                              {
                                 effectiveAddress=currentAddress;
                              }
                           }
                        }
                        {
                           ARM_Memory_setWord(_pipeData, _time, _startTime, _stage, _instr, 0, effectiveAddress, ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, index));
                        }
                        {
                           currentAddress=nextAddress;
                        }
                     }
                     
                  }
               }
            }
         }
         break;
      
   }
}

void ARM_LoadStoreMultipleWriteBack_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreMultipleWriteBack_st * _this, HADL_Int8 rn, HADL_Int32 addr) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: LoadStoreMultipleWriteBack");
   }
   switch(_this->_choice) {
      case ARM_LoadStoreMultipleWriteBack_WRITE_BACK_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, rn, addr);
            }
         }
         break;
      
      case ARM_LoadStoreMultipleWriteBack_NO_WRITE_BACK_choice:
         {
            
         }
         break;
      
   }
}

void ARM_BranchInstruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_BranchInstruction_st * _this) {
   {
      HADL_Debug_printMessage("(FRG) Running behavior: BranchInstruction");
   }
   switch(_this->_choice) {
      case ARM_BranchInstruction_B_choice:
         {
            
         }
         break;
      
      case ARM_BranchInstruction_BL_choice:
         {
            {
               ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, 14, ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, 15));
            }
         }
         break;
      
   }
   {
      {
         ARM_Registers_setValue(_pipeData, _time, _startTime, _stage, _instr, 0, 15, ARM_ALU_addOp(_pipeData, _time, _startTime, _stage, _instr, 0, ARM_Registers_getValue(_pipeData, _time, _startTime, _stage, _instr, 0, 15), _this->offset));
      }
   }
}

void ARM_create() {
   StatusRegister_cpsr=HADL_UNDEFINED;
   Registers_gpr=HADL_Array_new();
   Memory_memory=HADL_Array_new();
}

int ARM_ARMGeneric_gpr_pc_r_port_op[1]= {ARM_Registers_getPC_op};

int ARM_ARM9_memory_dcache_port_op[6]= {ARM_Memory_getByte_op, ARM_Memory_getHalfWord_op, ARM_Memory_getWord_op, ARM_Memory_setByte_op, ARM_Memory_setHalfWord_op, ARM_Memory_setWord_op};

int ARM_ARM9_memory_icache_port_op[1]= {ARM_Memory_getWord_op};

int ARM_ARMGeneric_cpsr_v_w_port_op[1]= {ARM_StatusRegister_setVFlag_op};

int ARM_ARMGeneric_gpr_rd_port_op[1]= {ARM_Registers_setValue_op};

int ARM_ARMGeneric_cpsr_c_r_port_op[1]= {ARM_StatusRegister_getCFlag_op};

int ARM_ARMGeneric_gpr_pc_w_port_op[1]= {ARM_Registers_setValue_op};

int ARM_ARMGeneric_cpsr_v_r_port_op[1]= {ARM_StatusRegister_getVFlag_op};

int ARM_ARMGeneric_gpr_rn_port_op[1]= {ARM_Registers_getValue_op};

int ARM_ARMGeneric_cpsr_z_r_port_op[1]= {ARM_StatusRegister_getZFlag_op};

int ARM_ARM7_memory_all_port_op[6]= {ARM_Memory_getByte_op, ARM_Memory_getHalfWord_op, ARM_Memory_getWord_op, ARM_Memory_setByte_op, ARM_Memory_setHalfWord_op, ARM_Memory_setWord_op};

int ARM_ARMGeneric_gpr_rm_port_op[1]= {ARM_Registers_getValue_op};

int ARM_ARMGeneric_shifter_all_port_op[5]= {ARM_Shifter_lslOp_op, ARM_Shifter_lsrOp_op, ARM_Shifter_asrOp_op, ARM_Shifter_rorOp_op, ARM_Shifter_rrxOp_op};

int ARM_ARMGeneric_fetcher_all_port_op[2]= {ARM_Fetcher_reset_op, ARM_Fetcher_next_op};

int ARM_ARMGeneric_gpr_rs_port_op[1]= {ARM_Registers_getValue_op};

int ARM_ARMGeneric_cpsr_c_w_port_op[1]= {ARM_StatusRegister_setCFlag_op};

int ARM_ARMGeneric_cpsr_n_w_port_op[1]= {ARM_StatusRegister_setNFlag_op};

int ARM_ARMGeneric_cpsr_n_r_port_op[1]= {ARM_StatusRegister_getNFlag_op};

int ARM_ARMGeneric_alu_all_port_op[22]= {ARM_ALU_updateCpsrWithResult_op, ARM_ALU_clearCpsrCV_op, ARM_ALU_movOp_op, ARM_ALU_movOpUpdateCpsr_op, ARM_ALU_notOp_op, ARM_ALU_notOpUpdateCpsr_op, ARM_ALU_andOp_op, ARM_ALU_andOpUpdateCpsr_op, ARM_ALU_orOp_op, ARM_ALU_orOpUpdateCpsr_op, ARM_ALU_eorOp_op, ARM_ALU_eorOpUpdateCpsr_op, ARM_ALU_bicOp_op, ARM_ALU_bicOpUpdateCpsr_op, ARM_ALU_subOp_op, ARM_ALU_subOpUpdateCpsr_op, ARM_ALU_subOpWithCarry_op, ARM_ALU_subOpWithCarryUpdateCpsr_op, ARM_ALU_addOp_op, ARM_ALU_addOpWithCarry_op, ARM_ALU_addOpUpdateCpsr_op, ARM_ALU_addOpWithCarryUpdateCpsr_op};

int ARM_ARMGeneric_cpsr_z_w_port_op[1]= {ARM_StatusRegister_setZFlag_op};

HADL_Port_t ARM_ARMGeneric_gpr_pc_r_port= {"gpr.pc_r", ARM_ARMGeneric_gpr_pc_r_res, ARM_Registers_iface, 1, ARM_ARMGeneric_gpr_pc_r_port_op};

HADL_Port_t ARM_ARM9_memory_dcache_port= {"memory.dcache", ARM_ARM9_memory_dcache_res, ARM_Memory_iface, 6, ARM_ARM9_memory_dcache_port_op};

HADL_Port_t ARM_ARM9_memory_icache_port= {"memory.icache", ARM_ARM9_memory_icache_res, ARM_Memory_iface, 1, ARM_ARM9_memory_icache_port_op};

HADL_Port_t ARM_ARMGeneric_cpsr_v_w_port= {"cpsr.v_w", ARM_ARMGeneric_cpsr_v_w_res, ARM_StatusRegister_iface, 1, ARM_ARMGeneric_cpsr_v_w_port_op};

HADL_Port_t ARM_ARMGeneric_gpr_rd_port= {"gpr.rd", ARM_ARMGeneric_gpr_rd_res, ARM_Registers_iface, 1, ARM_ARMGeneric_gpr_rd_port_op};

HADL_Port_t ARM_ARMGeneric_cpsr_c_r_port= {"cpsr.c_r", ARM_ARMGeneric_cpsr_c_r_res, ARM_StatusRegister_iface, 1, ARM_ARMGeneric_cpsr_c_r_port_op};

HADL_Port_t ARM_ARMGeneric_gpr_pc_w_port= {"gpr.pc_w", ARM_ARMGeneric_gpr_pc_w_res, ARM_Registers_iface, 1, ARM_ARMGeneric_gpr_pc_w_port_op};

HADL_Port_t ARM_ARMGeneric_cpsr_v_r_port= {"cpsr.v_r", ARM_ARMGeneric_cpsr_v_r_res, ARM_StatusRegister_iface, 1, ARM_ARMGeneric_cpsr_v_r_port_op};

HADL_Port_t ARM_ARMGeneric_gpr_rn_port= {"gpr.rn", ARM_ARMGeneric_gpr_rn_res, ARM_Registers_iface, 1, ARM_ARMGeneric_gpr_rn_port_op};

HADL_Port_t ARM_ARMGeneric_cpsr_z_r_port= {"cpsr.z_r", ARM_ARMGeneric_cpsr_z_r_res, ARM_StatusRegister_iface, 1, ARM_ARMGeneric_cpsr_z_r_port_op};

HADL_Port_t ARM_ARM7_memory_all_port= {"memory.all", ARM_ARM7_memory_all_res, ARM_Memory_iface, 6, ARM_ARM7_memory_all_port_op};

HADL_Port_t ARM_ARMGeneric_gpr_rm_port= {"gpr.rm", ARM_ARMGeneric_gpr_rm_res, ARM_Registers_iface, 1, ARM_ARMGeneric_gpr_rm_port_op};

HADL_Port_t ARM_ARMGeneric_shifter_all_port= {"shifter.all", ARM_ARMGeneric_shifter_all_res, ARM_Shifter_iface, 5, ARM_ARMGeneric_shifter_all_port_op};

HADL_Port_t ARM_ARMGeneric_fetcher_all_port= {"fetcher.all", ARM_ARMGeneric_fetcher_all_res, ARM_Fetcher_iface, 2, ARM_ARMGeneric_fetcher_all_port_op};

HADL_Port_t ARM_ARMGeneric_gpr_rs_port= {"gpr.rs", ARM_ARMGeneric_gpr_rs_res, ARM_Registers_iface, 1, ARM_ARMGeneric_gpr_rs_port_op};

HADL_Port_t ARM_ARMGeneric_cpsr_c_w_port= {"cpsr.c_w", ARM_ARMGeneric_cpsr_c_w_res, ARM_StatusRegister_iface, 1, ARM_ARMGeneric_cpsr_c_w_port_op};

HADL_Port_t ARM_ARMGeneric_cpsr_n_w_port= {"cpsr.n_w", ARM_ARMGeneric_cpsr_n_w_res, ARM_StatusRegister_iface, 1, ARM_ARMGeneric_cpsr_n_w_port_op};

HADL_Port_t ARM_ARMGeneric_cpsr_n_r_port= {"cpsr.n_r", ARM_ARMGeneric_cpsr_n_r_res, ARM_StatusRegister_iface, 1, ARM_ARMGeneric_cpsr_n_r_port_op};

HADL_Port_t ARM_ARMGeneric_alu_all_port= {"alu.all", ARM_ARMGeneric_alu_all_res, ARM_ALU_iface, 22, ARM_ARMGeneric_alu_all_port_op};

HADL_Port_t ARM_ARMGeneric_cpsr_z_w_port= {"cpsr.z_w", ARM_ARMGeneric_cpsr_z_w_res, ARM_StatusRegister_iface, 1, ARM_ARMGeneric_cpsr_z_w_port_op};

unsigned ARM_pFDE_Memory_succ_rep[1]= {ARM_pFDE_Memory_stage};

unsigned ARM_pFDE_Fetch_succ_rep[1]= {ARM_pFDE_Decode_stage};

unsigned ARM_pFDE_Execute_succ_rep[1]= {ARM_pFDE_Memory_stage};

unsigned ARM_pFDE_Decode_succ_rep[1]= {ARM_pFDE_Execute_stage};

HADL_PortUsage_t ARM_pFDE_Memory_ports_rep[3]= {{&ARM_ARM7_memory_all_port, 1} , {&ARM_ARMGeneric_gpr_rn_port, 1} , {&ARM_ARMGeneric_gpr_rd_port, 1}};

HADL_PortUsage_t ARM_pFDE_Fetch_ports_rep[4]= {{&ARM_ARMGeneric_fetcher_all_port, 0} , {&ARM_ARM7_memory_all_port, 0} , {&ARM_ARMGeneric_gpr_pc_r_port, 0} , {&ARM_ARMGeneric_gpr_pc_w_port, 0}};

HADL_PortUsage_t ARM_pFDE_Execute_ports_rep[14]= {{&ARM_ARMGeneric_gpr_rn_port, 0} , {&ARM_ARMGeneric_gpr_rm_port, 0} , {&ARM_ARMGeneric_gpr_rs_port, 0} , {&ARM_ARMGeneric_gpr_rd_port, 0} , {&ARM_ARMGeneric_cpsr_c_r_port, 0} , {&ARM_ARMGeneric_cpsr_c_w_port, 0} , {&ARM_ARMGeneric_cpsr_n_r_port, 0} , {&ARM_ARMGeneric_cpsr_n_w_port, 0} , {&ARM_ARMGeneric_cpsr_v_r_port, 0} , {&ARM_ARMGeneric_cpsr_v_w_port, 0} , {&ARM_ARMGeneric_cpsr_z_r_port, 0} , {&ARM_ARMGeneric_cpsr_z_w_port, 0} , {&ARM_ARMGeneric_shifter_all_port, 0} , {&ARM_ARMGeneric_alu_all_port, 0}};

HADL_PortUsage_t ARM_pFDE_Decode_ports_rep[0]= {};

HADL_Stage_t ARM_pFDE_stages_rep[4]= {{"Fetch", 1, ARM_pFDE_Fetch_succ_rep, 4, ARM_pFDE_Fetch_ports_rep} , {"Decode", 1, ARM_pFDE_Decode_succ_rep, 0, ARM_pFDE_Decode_ports_rep} , {"Execute", 1, ARM_pFDE_Execute_succ_rep, 14, ARM_pFDE_Execute_ports_rep} , {"Memory", 1, ARM_pFDE_Memory_succ_rep, 3, ARM_pFDE_Memory_ports_rep}};

HADL_Pipeline_t ARM_pFDE_rep= {"pFDE", 4, ARM_pFDE_stages_rep};

HADL_PipelineData_t * ARM_pFDE_init() {
   HADL_PipelineData_t * _pipeData=HADL_Scheduler_newPipelineData(&ARM_pFDE_rep, 4, 20);
   HADL_Time_t _dtime=0;
   int _dstage=-1;
   HADL_Time_t * _time=&_dtime;
   HADL_Time_t _startTime=0;
   int * _stage=&_dstage;
   void * _instr=NULL;
   {
      {
         ARM_Fetcher_reset(_pipeData, _time, _startTime, _stage, _instr, 0);
      }
   }
   return _pipeData;
}
#endif
   
