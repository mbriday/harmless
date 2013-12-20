#ifndef ARMRunnerHeader
   
#define ARMRunnerHeader
   


#include "hadl-types.h"

#include "hadl-custom.h"

#include "hadl-scheduler.h"

struct ARM_Instruction_st;

struct ARM_Condition_st;

struct ARM_InstructionKind_st;

struct ARM_DataProcessingInstruction_st;

struct ARM_GprRead_st;

struct ARM_DataProcessingOperation_st;

struct ARM_CalculationOperation_st;

struct ARM_ComparisonOperation_st;

struct ARM_FlexibleOperand2_st;

struct ARM_Immediate_st;

struct ARM_RotatedImmediate_st;

struct ARM_ShiftedRegister_st;

struct ARM_ShiftSpecification_st;

struct ARM_ShiftOperation_st;

struct ARM_ShiftAmount_st;

struct ARM_ShiftOperationKind_st;

struct ARM_LoadStoreInstruction_st;

struct ARM_LoadStoreOffset_st;

struct ARM_LoadStoreAddressCalculation_st;

struct ARM_LoadStoreAddressingMode_st;

struct ARM_LoadStoreTransfer_st;

struct ARM_LoadStoreMultipleInstruction_st;

struct ARM_LoadStoreMultipleTransfer_st;

struct ARM_LoadStoreMultipleWriteBack_st;

struct ARM_BranchInstruction_st;

enum ARM_Paths_en {
   ARM_Root_path,
   ARM_Instruction_Condition_path,
   ARM_Instruction_InstructionKind_path,
   ARM_InstructionKind_DataProcessingInstruction_path,
   ARM_InstructionKind_LoadStoreInstruction_path,
   ARM_InstructionKind_LoadStoreMultipleInstruction_path,
   ARM_InstructionKind_BranchInstruction_path,
   ARM_DataProcessingInstruction_GprRead_path,
   ARM_DataProcessingInstruction_FlexibleOperand2_path,
   ARM_DataProcessingInstruction_DataProcessingOperation_path,
   ARM_DataProcessingOperation_CalculationOperation_path,
   ARM_DataProcessingOperation_ComparisonOperation_path,
   ARM_FlexibleOperand2_Immediate_path,
   ARM_FlexibleOperand2_RotatedImmediate_path,
   ARM_FlexibleOperand2_GprRead_path,
   ARM_FlexibleOperand2_ShiftedRegister_path,
   ARM_ShiftedRegister_GprRead_path,
   ARM_ShiftedRegister_ShiftSpecification_path,
   ARM_ShiftSpecification_ShiftOperation_path,
   ARM_ShiftOperation_ShiftAmount_path,
   ARM_ShiftOperation_ShiftOperationKind_path,
   ARM_ShiftAmount_Immediate_path,
   ARM_ShiftAmount_GprRead_path,
   ARM_LoadStoreInstruction_LoadStoreOffset_path,
   ARM_LoadStoreInstruction_LoadStoreAddressCalculation_path,
   ARM_LoadStoreInstruction_LoadStoreAddressingMode_path,
   ARM_LoadStoreInstruction_LoadStoreTransfer_path,
   ARM_LoadStoreOffset_Immediate_path,
   ARM_LoadStoreOffset_ShiftedRegister_path,
   ARM_LoadStoreOffset_GprRead_path,
   ARM_LoadStoreMultipleInstruction_LoadStoreMultipleTransfer_path,
   ARM_LoadStoreMultipleInstruction_LoadStoreMultipleWriteBack_path
};

enum ARM_Condition_en {
   ARM_Condition_EQ_choice,
   ARM_Condition_NE_choice,
   ARM_Condition_CS_choice,
   ARM_Condition_CC_choice,
   ARM_Condition_MI_choice,
   ARM_Condition_PL_choice,
   ARM_Condition_VS_choice,
   ARM_Condition_VC_choice,
   ARM_Condition_HI_choice,
   ARM_Condition_LS_choice,
   ARM_Condition_GE_choice,
   ARM_Condition_LT_choice,
   ARM_Condition_GT_choice,
   ARM_Condition_LE_choice,
   ARM_Condition_AL_choice,
   ARM_Condition_NV_choice
};

enum ARM_InstructionKind_en {
   ARM_InstructionKind_DataProcessingInstruction_choice,
   ARM_InstructionKind_LoadStoreInstruction_choice,
   ARM_InstructionKind_LoadStoreMultipleInstruction_choice,
   ARM_InstructionKind_BranchInstruction_choice
};

enum ARM_DataProcessingOperation_en {
   ARM_DataProcessingOperation_CalculationOperation_choice,
   ARM_DataProcessingOperation_ComparisonOperation_choice
};

enum ARM_CalculationOperation_en {
   ARM_CalculationOperation_AND_choice,
   ARM_CalculationOperation_ANDS_choice,
   ARM_CalculationOperation_EOR_choice,
   ARM_CalculationOperation_EORS_choice,
   ARM_CalculationOperation_SUB_choice,
   ARM_CalculationOperation_SUBS_choice,
   ARM_CalculationOperation_RSB_choice,
   ARM_CalculationOperation_RSBS_choice,
   ARM_CalculationOperation_ADD_choice,
   ARM_CalculationOperation_ADDS_choice,
   ARM_CalculationOperation_ADC_choice,
   ARM_CalculationOperation_ADCS_choice,
   ARM_CalculationOperation_SBC_choice,
   ARM_CalculationOperation_SBCS_choice,
   ARM_CalculationOperation_RSC_choice,
   ARM_CalculationOperation_RSCS_choice,
   ARM_CalculationOperation_ORR_choice,
   ARM_CalculationOperation_ORRS_choice,
   ARM_CalculationOperation_MOV_choice,
   ARM_CalculationOperation_MOVS_choice,
   ARM_CalculationOperation_BIC_choice,
   ARM_CalculationOperation_BICS_choice,
   ARM_CalculationOperation_MVN_choice,
   ARM_CalculationOperation_MVNS_choice
};

enum ARM_ComparisonOperation_en {
   ARM_ComparisonOperation_TST_choice,
   ARM_ComparisonOperation_TEQ_choice,
   ARM_ComparisonOperation_CMP_choice,
   ARM_ComparisonOperation_CMN_choice
};

enum ARM_FlexibleOperand2_en {
   ARM_FlexibleOperand2_Immediate_choice,
   ARM_FlexibleOperand2_RotatedImmediate_choice,
   ARM_FlexibleOperand2_GprRead_choice,
   ARM_FlexibleOperand2_ShiftedRegister_choice
};

enum ARM_ShiftSpecification_en {
   ARM_ShiftSpecification_RRX_choice,
   ARM_ShiftSpecification_ShiftOperation_choice
};

enum ARM_ShiftAmount_en {
   ARM_ShiftAmount_Immediate_choice,
   ARM_ShiftAmount_GprRead_choice
};

enum ARM_ShiftOperationKind_en {
   ARM_ShiftOperationKind_LSL_choice,
   ARM_ShiftOperationKind_LSR_choice,
   ARM_ShiftOperationKind_ASR_choice,
   ARM_ShiftOperationKind_ROR_choice
};

enum ARM_LoadStoreOffset_en {
   ARM_LoadStoreOffset_Immediate_choice,
   ARM_LoadStoreOffset_ShiftedRegister_choice,
   ARM_LoadStoreOffset_GprRead_choice
};

enum ARM_LoadStoreAddressCalculation_en {
   ARM_LoadStoreAddressCalculation_UP_choice,
   ARM_LoadStoreAddressCalculation_DOWN_choice
};

enum ARM_LoadStoreAddressingMode_en {
   ARM_LoadStoreAddressingMode_PREINDEXED_choice,
   ARM_LoadStoreAddressingMode_AUTOINDEXED_choice,
   ARM_LoadStoreAddressingMode_POSTINDEXED_choice
};

enum ARM_LoadStoreTransfer_en {
   ARM_LoadStoreTransfer_LDR_choice,
   ARM_LoadStoreTransfer_LDRH_choice,
   ARM_LoadStoreTransfer_LDRSH_choice,
   ARM_LoadStoreTransfer_LDRB_choice,
   ARM_LoadStoreTransfer_LDRSB_choice,
   ARM_LoadStoreTransfer_STR_choice,
   ARM_LoadStoreTransfer_STRH_choice,
   ARM_LoadStoreTransfer_STRB_choice
};

enum ARM_LoadStoreMultipleTransfer_en {
   ARM_LoadStoreMultipleTransfer_LOAD_choice,
   ARM_LoadStoreMultipleTransfer_STORE_choice
};

enum ARM_LoadStoreMultipleWriteBack_en {
   ARM_LoadStoreMultipleWriteBack_WRITE_BACK_choice,
   ARM_LoadStoreMultipleWriteBack_NO_WRITE_BACK_choice
};

enum ARM_BranchInstruction_en {
   ARM_BranchInstruction_B_choice,
   ARM_BranchInstruction_BL_choice
};

enum ARM_Ports_en {
   ARM_ARMGeneric_gpr_pc_r_res,
   ARM_ARM9_memory_dcache_res,
   ARM_ARM9_memory_icache_res,
   ARM_ARMGeneric_cpsr_v_w_res,
   ARM_ARMGeneric_gpr_rd_res,
   ARM_ARMGeneric_cpsr_c_r_res,
   ARM_ARMGeneric_gpr_pc_w_res,
   ARM_ARMGeneric_cpsr_v_r_res,
   ARM_ARMGeneric_gpr_rn_res,
   ARM_ARMGeneric_cpsr_z_r_res,
   ARM_ARM7_memory_all_res,
   ARM_ARMGeneric_gpr_rm_res,
   ARM_ARMGeneric_shifter_all_res,
   ARM_ARMGeneric_fetcher_all_res,
   ARM_ARMGeneric_gpr_rs_res,
   ARM_ARMGeneric_cpsr_c_w_res,
   ARM_ARMGeneric_cpsr_n_w_res,
   ARM_ARMGeneric_cpsr_n_r_res,
   ARM_ARMGeneric_alu_all_res,
   ARM_ARMGeneric_cpsr_z_w_res
};

enum ARM_Components_en {
   ARM_StatusRegister_iface,
   ARM_Registers_iface,
   ARM_Memory_iface,
   ARM_ALU_iface,
   ARM_Shifter_iface,
   ARM_Fetcher_iface
};

enum ARM_Pipelines_en {
   ARM_pFDE_pipe
};

enum ARM_StatusRegister_en {
   ARM_StatusRegister_getNFlag_op,
   ARM_StatusRegister_setNFlag_op,
   ARM_StatusRegister_getZFlag_op,
   ARM_StatusRegister_setZFlag_op,
   ARM_StatusRegister_getCFlag_op,
   ARM_StatusRegister_setCFlag_op,
   ARM_StatusRegister_getVFlag_op,
   ARM_StatusRegister_setVFlag_op
};

enum ARM_Registers_en {
   ARM_Registers_getValue_op,
   ARM_Registers_getPC_op,
   ARM_Registers_setValue_op
};

enum ARM_Memory_en {
   ARM_Memory_getByte_op,
   ARM_Memory_getHalfWord_op,
   ARM_Memory_getWord_op,
   ARM_Memory_setByte_op,
   ARM_Memory_setHalfWord_op,
   ARM_Memory_setWord_op
};

enum ARM_ALU_en {
   ARM_ALU_updateCpsrWithResult_op,
   ARM_ALU_clearCpsrCV_op,
   ARM_ALU_movOp_op,
   ARM_ALU_movOpUpdateCpsr_op,
   ARM_ALU_notOp_op,
   ARM_ALU_notOpUpdateCpsr_op,
   ARM_ALU_andOp_op,
   ARM_ALU_andOpUpdateCpsr_op,
   ARM_ALU_orOp_op,
   ARM_ALU_orOpUpdateCpsr_op,
   ARM_ALU_eorOp_op,
   ARM_ALU_eorOpUpdateCpsr_op,
   ARM_ALU_bicOp_op,
   ARM_ALU_bicOpUpdateCpsr_op,
   ARM_ALU_subOp_op,
   ARM_ALU_subOpUpdateCpsr_op,
   ARM_ALU_subOpWithCarry_op,
   ARM_ALU_subOpWithCarryUpdateCpsr_op,
   ARM_ALU_addOp_op,
   ARM_ALU_addOpWithCarry_op,
   ARM_ALU_addOpUpdateCpsr_op,
   ARM_ALU_addOpWithCarryUpdateCpsr_op
};

enum ARM_Shifter_en {
   ARM_Shifter_lslOp_op,
   ARM_Shifter_lsrOp_op,
   ARM_Shifter_asrOp_op,
   ARM_Shifter_rorOp_op,
   ARM_Shifter_rrxOp_op
};

enum ARM_Fetcher_en {
   ARM_Fetcher_reset_op,
   ARM_Fetcher_next_op
};

enum ARM_pFDE_en {
   ARM_pFDE_Fetch_stage,
   ARM_pFDE_Decode_stage,
   ARM_pFDE_Execute_stage,
   ARM_pFDE_Memory_stage
};

HADL_Int32 ARM_StatusRegister_getNFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline);

void ARM_StatusRegister_setNFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 flag);

HADL_Int32 ARM_StatusRegister_getZFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline);

void ARM_StatusRegister_setZFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 flag);

HADL_Int32 ARM_StatusRegister_getCFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline);

void ARM_StatusRegister_setCFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 flag);

HADL_Int32 ARM_StatusRegister_getVFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline);

void ARM_StatusRegister_setVFlag(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 flag);

HADL_Int32 ARM_Registers_getValue(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 index);

HADL_Int32 ARM_Registers_getPC(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline);

void ARM_Registers_setValue(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int8 index, HADL_Int32 value);

HADL_Int32 ARM_Memory_getByte(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int8 ext);

HADL_Int32 ARM_Memory_getHalfWord(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int8 ext);

HADL_Int32 ARM_Memory_getWord(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address);

void ARM_Memory_setByte(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int8 value);

void ARM_Memory_setHalfWord(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int16 value);

void ARM_Memory_setWord(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 address, HADL_Int32 value);

void ARM_ALU_updateCpsrWithResult(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 r);

void ARM_ALU_clearCpsrCV(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline);

HADL_Int32 ARM_ALU_movOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a);

HADL_Int32 ARM_ALU_movOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a);

HADL_Int32 ARM_ALU_notOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a);

HADL_Int32 ARM_ALU_notOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a);

HADL_Int32 ARM_ALU_andOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_andOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_orOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_orOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_eorOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_eorOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_bicOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_bicOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_subOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_subOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_subOpWithCarry(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_subOpWithCarryUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_addOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_addOpWithCarry(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_addOpUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_ALU_addOpWithCarryUpdateCpsr(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_Shifter_lslOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_Shifter_lsrOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_Shifter_asrOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_Shifter_rorOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a, HADL_Int32 b);

HADL_Int32 ARM_Shifter_rrxOp(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline, HADL_Int32 a);

void ARM_Fetcher_reset(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline);

HADL_Int32 ARM_Fetcher_next(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, int _inline);

void ARM_pFDE_step(HADL_PipelineData_t * _pipeData, HADL_Time_t _dtime);

void ARM_Instruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_Instruction_st * _this);

void ARM_Condition_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_Condition_st * _this, HADL_Int8 * result);

void ARM_InstructionKind_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_InstructionKind_st * _this);

void ARM_DataProcessingInstruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_DataProcessingInstruction_st * _this);

void ARM_GprRead_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_GprRead_st * _this, HADL_Int32 * result);

void ARM_DataProcessingOperation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_DataProcessingOperation_st * _this, HADL_Int32 a, HADL_Int32 b);

void ARM_CalculationOperation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_CalculationOperation_st * _this, HADL_Int32 a, HADL_Int32 b);

void ARM_ComparisonOperation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ComparisonOperation_st * _this, HADL_Int32 a, HADL_Int32 b);

void ARM_FlexibleOperand2_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_FlexibleOperand2_st * _this, HADL_Int32 * result);

void ARM_Immediate_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_Immediate_st * _this, HADL_Int32 * result);

void ARM_RotatedImmediate_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_RotatedImmediate_st * _this, HADL_Int32 * result);

void ARM_ShiftedRegister_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftedRegister_st * _this, HADL_Int32 * result);

void ARM_ShiftSpecification_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftSpecification_st * _this, HADL_Int32 value, HADL_Int32 * result);

void ARM_ShiftOperation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftOperation_st * _this, HADL_Int32 value, HADL_Int32 * result);

void ARM_ShiftAmount_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftAmount_st * _this, HADL_Int32 * result);

void ARM_ShiftOperationKind_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_ShiftOperationKind_st * _this, HADL_Int32 value, HADL_Int32 amount, HADL_Int32 * result);

void ARM_LoadStoreInstruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreInstruction_st * _this);

void ARM_LoadStoreOffset_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreOffset_st * _this, HADL_Int32 * result);

void ARM_LoadStoreAddressCalculation_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreAddressCalculation_st * _this, HADL_Int8 rn, HADL_Int32 offset, HADL_Int32 * base, HADL_Int32 * result);

void ARM_LoadStoreAddressingMode_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreAddressingMode_st * _this, HADL_Int8 rn, HADL_Int32 base, HADL_Int32 address, HADL_Int32 * result);

void ARM_LoadStoreTransfer_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreTransfer_st * _this, HADL_Int32 addr, HADL_Int8 rd);

void ARM_LoadStoreMultipleInstruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreMultipleInstruction_st * _this);

void ARM_LoadStoreMultipleTransfer_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreMultipleTransfer_st * _this, HADL_Int8 rn, HADL_Int16 regList, HADL_Int8 sr, HADL_Int32 * finalAddress);

void ARM_LoadStoreMultipleWriteBack_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_LoadStoreMultipleWriteBack_st * _this, HADL_Int8 rn, HADL_Int32 addr);

void ARM_BranchInstruction_run(HADL_PipelineData_t * _pipeData, HADL_Time_t * _time, HADL_Time_t _startTime, int * _stage, void * _instr, struct ARM_BranchInstruction_st * _this);

void ARM_create();

HADL_PipelineData_t * ARM_pFDE_init();

struct ARM_Instruction_st {
   enum ARM_Paths_en _path;
   void * _parent;
   struct ARM_Condition_st * chunk_ARM_Condition_st;
   struct ARM_InstructionKind_st * chunk_ARM_InstructionKind_st;
};

struct ARM_Condition_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_Condition_en _choice;
   void * _target;
};

struct ARM_InstructionKind_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_InstructionKind_en _choice;
   void * _target;
};

struct ARM_DataProcessingInstruction_st {
   enum ARM_Paths_en _path;
   void * _parent;
   struct ARM_GprRead_st * chunk_ARM_GprRead_st;
   struct ARM_FlexibleOperand2_st * chunk_ARM_FlexibleOperand2_st;
   struct ARM_DataProcessingOperation_st * chunk_ARM_DataProcessingOperation_st;
};

struct ARM_GprRead_st {
   enum ARM_Paths_en _path;
   void * _parent;
   HADL_Int32 reg;
};

struct ARM_DataProcessingOperation_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_DataProcessingOperation_en _choice;
   void * _target;
};

struct ARM_CalculationOperation_st {
   enum ARM_Paths_en _path;
   void * _parent;
   HADL_Int32 rd;
   enum ARM_CalculationOperation_en _choice;
   void * _target;
};

struct ARM_ComparisonOperation_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_ComparisonOperation_en _choice;
   void * _target;
};

struct ARM_FlexibleOperand2_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_FlexibleOperand2_en _choice;
   void * _target;
};

struct ARM_Immediate_st {
   enum ARM_Paths_en _path;
   void * _parent;
   HADL_Int32 val;
};

struct ARM_RotatedImmediate_st {
   enum ARM_Paths_en _path;
   void * _parent;
   HADL_Int32 rot;
   HADL_Int32 val;
};

struct ARM_ShiftedRegister_st {
   enum ARM_Paths_en _path;
   void * _parent;
   struct ARM_GprRead_st * chunk_ARM_GprRead_st;
   struct ARM_ShiftSpecification_st * chunk_ARM_ShiftSpecification_st;
};

struct ARM_ShiftSpecification_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_ShiftSpecification_en _choice;
   void * _target;
};

struct ARM_ShiftOperation_st {
   enum ARM_Paths_en _path;
   void * _parent;
   struct ARM_ShiftAmount_st * chunk_ARM_ShiftAmount_st;
   struct ARM_ShiftOperationKind_st * chunk_ARM_ShiftOperationKind_st;
};

struct ARM_ShiftAmount_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_ShiftAmount_en _choice;
   void * _target;
};

struct ARM_ShiftOperationKind_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_ShiftOperationKind_en _choice;
   void * _target;
};

struct ARM_LoadStoreInstruction_st {
   enum ARM_Paths_en _path;
   void * _parent;
   HADL_Int32 rn;
   HADL_Int32 rd;
   struct ARM_LoadStoreOffset_st * chunk_ARM_LoadStoreOffset_st;
   struct ARM_LoadStoreAddressCalculation_st * chunk_ARM_LoadStoreAddressCalculation_st;
   struct ARM_LoadStoreAddressingMode_st * chunk_ARM_LoadStoreAddressingMode_st;
   struct ARM_LoadStoreTransfer_st * chunk_ARM_LoadStoreTransfer_st;
};

struct ARM_LoadStoreOffset_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_LoadStoreOffset_en _choice;
   void * _target;
};

struct ARM_LoadStoreAddressCalculation_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_LoadStoreAddressCalculation_en _choice;
   void * _target;
};

struct ARM_LoadStoreAddressingMode_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_LoadStoreAddressingMode_en _choice;
   void * _target;
};

struct ARM_LoadStoreTransfer_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_LoadStoreTransfer_en _choice;
   void * _target;
};

struct ARM_LoadStoreMultipleInstruction_st {
   enum ARM_Paths_en _path;
   void * _parent;
   HADL_Int32 sr;
   HADL_Int32 rn;
   HADL_Int32 rl;
   struct ARM_LoadStoreMultipleTransfer_st * chunk_ARM_LoadStoreMultipleTransfer_st;
   struct ARM_LoadStoreMultipleWriteBack_st * chunk_ARM_LoadStoreMultipleWriteBack_st;
};

struct ARM_LoadStoreMultipleTransfer_st {
   enum ARM_Paths_en _path;
   void * _parent;
   HADL_Int32 inc;
   HADL_Int32 bfore;
   enum ARM_LoadStoreMultipleTransfer_en _choice;
   void * _target;
};

struct ARM_LoadStoreMultipleWriteBack_st {
   enum ARM_Paths_en _path;
   void * _parent;
   enum ARM_LoadStoreMultipleWriteBack_en _choice;
   void * _target;
};

struct ARM_BranchInstruction_st {
   enum ARM_Paths_en _path;
   void * _parent;
   HADL_Int32 offset;
   enum ARM_BranchInstruction_en _choice;
   void * _target;
};
#endif
   
