#ifndef ARMDecoderHeader
   
#define ARMDecoderHeader
   


#include "hadl-types.h"

#include "hadl-custom.h"

struct ARM_Condition_st * ARM_Condition_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_InstructionKind_st * ARM_InstructionKind_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_FlexibleOperand2_st * ARM_FlexibleOperand2_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_DataProcessingOperation_st * ARM_DataProcessingOperation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_CalculationOperation_st * ARM_CalculationOperation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_ComparisonOperation_st * ARM_ComparisonOperation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_GprRead_st * ARM_GprRead_DataProcessingInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_GprRead_st * ARM_GprRead_ShiftedRegister_LoadStoreOffset_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_GprRead_st * ARM_GprRead_ShiftAmount_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_RotatedImmediate_st * ARM_RotatedImmediate_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_ShiftSpecification_st * ARM_ShiftSpecification_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_ShiftAmount_st * ARM_ShiftAmount_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_ShiftOperationKind_st * ARM_ShiftOperationKind_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_Immediate_st * ARM_Immediate_ShiftAmount_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_LoadStoreInstruction_st * ARM_LoadStoreInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_LoadStoreOffset_st * ARM_LoadStoreOffset_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_LoadStoreAddressCalculation_st * ARM_LoadStoreAddressCalculation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_Immediate_st * ARM_Immediate_LoadStoreOffset_1_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_Immediate_st * ARM_Immediate_LoadStoreOffset_2_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_LoadStoreAddressingMode_st * ARM_LoadStoreAddressingMode_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_LoadStoreTransfer_st * ARM_LoadStoreTransfer_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_LoadStoreMultipleInstruction_st * ARM_LoadStoreMultipleInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_LoadStoreMultipleTransfer_st * ARM_LoadStoreMultipleTransfer_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_LoadStoreMultipleWriteBack_st * ARM_LoadStoreMultipleWriteBack_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_BranchInstruction_st * ARM_BranchInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_Instruction_st * ARM_Instruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_DataProcessingInstruction_st * ARM_DataProcessingInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_GprRead_st * ARM_GprRead_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_Immediate_st * ARM_Immediate_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_ShiftedRegister_st * ARM_ShiftedRegister_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);

struct ARM_ShiftOperation_st * ARM_ShiftOperation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path);
#endif
   
