#ifndef ARMDisassemblerHeader
   
#define ARMDisassemblerHeader
   


#include "hadl-types.h"

#include "hadl-custom.h"

#include "ARMRunnerHeader.hadl.cpp"

void ARM_Instruction_disassemble(struct ARM_Instruction_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_Condition_disassemble(struct ARM_Condition_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_DataProcessingInstruction_disassemble(struct ARM_DataProcessingInstruction_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_GprRead_disassemble(struct ARM_GprRead_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_CalculationOperation_disassemble(struct ARM_CalculationOperation_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_ComparisonOperation_disassemble(struct ARM_ComparisonOperation_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_Immediate_FlexibleOperand2_ShiftAmount_disassemble(struct ARM_Immediate_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_RotatedImmediate_disassemble(struct ARM_RotatedImmediate_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_ShiftedRegister_FlexibleOperand2_disassemble(struct ARM_ShiftedRegister_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_ShiftSpecification_disassemble(struct ARM_ShiftSpecification_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_ShiftOperation_disassemble(struct ARM_ShiftOperation_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_ShiftOperationKind_disassemble(struct ARM_ShiftOperationKind_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_LoadStoreInstruction_disassemble(struct ARM_LoadStoreInstruction_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_LoadStoreAddressCalculation_disassemble(struct ARM_LoadStoreAddressCalculation_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_LoadStoreTransfer_disassemble(struct ARM_LoadStoreTransfer_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_Immediate_LoadStoreOffset_disassemble(struct ARM_Immediate_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_ShiftedRegister_LoadStoreOffset_disassemble(struct ARM_ShiftedRegister_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_LoadStoreAddressingMode_disassemble(struct ARM_LoadStoreAddressingMode_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_LoadStoreMultipleInstruction_disassemble(struct ARM_LoadStoreMultipleInstruction_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_LoadStoreMultipleTransfer_disassemble(struct ARM_LoadStoreMultipleTransfer_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_LoadStoreMultipleWriteBack_disassemble(struct ARM_LoadStoreMultipleWriteBack_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_BranchInstruction_disassemble(struct ARM_BranchInstruction_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_InstructionKind_disassemble(struct ARM_InstructionKind_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_DataProcessingOperation_disassemble(struct ARM_DataProcessingOperation_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_FlexibleOperand2_disassemble(struct ARM_FlexibleOperand2_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_ShiftAmount_disassemble(struct ARM_ShiftAmount_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_LoadStoreOffset_disassemble(struct ARM_LoadStoreOffset_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_Immediate_disassemble(struct ARM_Immediate_st * _this, char * _buffer, int _count, char * _args[]);

void ARM_ShiftedRegister_disassemble(struct ARM_ShiftedRegister_st * _this, char * _buffer, int _count, char * _args[]);
#endif
   
