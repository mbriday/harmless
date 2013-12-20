#ifndef ARMDecoderModule
   
#define ARMDecoderModule
   


#include "stdlib.h"

#include "hadl-fields.h"

#include "hadl-paths.h"

#include "hadl-debug.h"

#include "ARMRunnerHeader.hadl.cpp"

#include "ARMDecoderHeader.hadl.cpp"

int _r1[1 ][ 3]= {{23, 23, 1}};

int _r4[1 ][ 3]= {{11, 7, 1}};

int _r5[1 ][ 3]= {{19, 16, 1}};

int _r7[1 ][ 3]= {{20, 20, 1}};

int _r9[1 ][ 3]= {{25, 25, 1}};

int _r10[1 ][ 3]= {{24, 24, 1}};

int _r15[1 ][ 3]= {{24, 20, 1}};

int _r18[1 ][ 3]= {{19, 16, 1}};

int _r20[1 ][ 3]= {{7, 4, 1}};

int _r22[1 ][ 3]= {{11, 8, 1}};

int _r23[1 ][ 3]= {{3, 0, 1}};

int _r26[1 ][ 3]= {{15, 12, 1}};

int _r27[1 ][ 3]= {{26, 26, 1}};

int _r31[1 ][ 3]= {{24, 21, 1}};

int _r33[1 ][ 3]= {{11, 4, 1}};

int _r37[5 ][ 3]= {{26, 26, 1} , {25, 25, 1} , {22, 22, 1} , {11, 8, 1} , {4, 4, 1}};

int _r38[1 ][ 3]= {{21, 21, 1}};

int _r40[2 ][ 3]= {{11, 8, 1} , {3, 0, 1}};

int _r44[1 ][ 3]= {{31, 28, 1}};

int _r46[3 ][ 3]= {{27, 25, 1} , {7, 7, 1} , {4, 4, 1}};

int _r55[1 ][ 3]= {{15, 0, 1}};

int _r56[1 ][ 3]= {{19, 16, 1}};

int _r57[1 ][ 3]= {{24, 21, 1}};

int _r60[1 ][ 3]= {{15, 12, 1}};

int _r62[1 ][ 3]= {{26, 26, 1}};

int _r64[1 ][ 3]= {{24, 24, 1}};

int _r67[1 ][ 3]= {{22, 22, 1}};

int _r69[1 ][ 3]= {{6, 5, 1}};

int _r73[1 ][ 3]= {{11, 0, 1}};

int _r75[1 ][ 3]= {{23, 23, 1}};

int _r82[2 ][ 3]= {{24, 24, 1} , {21, 21, 1}};

int _r84[1 ][ 3]= {{7, 0, 1}};

int _r85[1 ][ 3]= {{11, 8, 1}};

int _r86[1 ][ 3]= {{23, 0, 1}};

int _r93[5 ][ 3]= {{26, 26, 1} , {22, 22, 1} , {20, 20, 1} , {6, 6, 1} , {5, 5, 1}};

struct ARM_Condition_st * ARM_Condition_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r44, 1, 0, 0, 1, 0);
   struct ARM_Condition_st * result=(struct ARM_Condition_st * )(malloc(sizeof(struct ARM_Condition_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: Condition");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&15)==0) {
      result->_choice=ARM_Condition_EQ_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #EQ");
   }
   else
   if((_field&15)==1) {
      result->_choice=ARM_Condition_NE_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #NE");
   }
   else
   if((_field&15)==2) {
      result->_choice=ARM_Condition_CS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #CS");
   }
   else
   if((_field&15)==3) {
      result->_choice=ARM_Condition_CC_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #CC");
   }
   else
   if((_field&15)==4) {
      result->_choice=ARM_Condition_MI_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #MI");
   }
   else
   if((_field&15)==5) {
      result->_choice=ARM_Condition_PL_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #PL");
   }
   else
   if((_field&15)==6) {
      result->_choice=ARM_Condition_VS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #VS");
   }
   else
   if((_field&15)==7) {
      result->_choice=ARM_Condition_VC_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #VC");
   }
   else
   if((_field&15)==8) {
      result->_choice=ARM_Condition_HI_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #HI");
   }
   else
   if((_field&15)==9) {
      result->_choice=ARM_Condition_LS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LS");
   }
   else
   if((_field&15)==10) {
      result->_choice=ARM_Condition_GE_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #GE");
   }
   else
   if((_field&15)==11) {
      result->_choice=ARM_Condition_LT_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LT");
   }
   else
   if((_field&15)==12) {
      result->_choice=ARM_Condition_GT_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #GT");
   }
   else
   if((_field&15)==13) {
      result->_choice=ARM_Condition_LE_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LE");
   }
   else
   if((_field&15)==14) {
      result->_choice=ARM_Condition_AL_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #AL");
   }
   else
   if((_field&15)==15) {
      result->_choice=ARM_Condition_NV_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #NV");
   }
   
   return result;
}

struct ARM_InstructionKind_st * ARM_InstructionKind_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r46, 3, 0, 0, 1, 0);
   struct ARM_InstructionKind_st * result=(struct ARM_InstructionKind_st * )(malloc(sizeof(struct ARM_InstructionKind_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: InstructionKind");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&31)==3) {
      result->_choice=ARM_InstructionKind_LoadStoreInstruction_choice;
      result->_target=ARM_LoadStoreInstruction_decode(_instr, result, ARM_InstructionKind_LoadStoreInstruction_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior LoadStoreInstruction");
   }
   else
   if((_field&24)==8) {
      result->_choice=ARM_InstructionKind_LoadStoreInstruction_choice;
      result->_target=ARM_LoadStoreInstruction_decode(_instr, result, ARM_InstructionKind_LoadStoreInstruction_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior LoadStoreInstruction");
   }
   else
   if((_field&24)==0) {
      result->_choice=ARM_InstructionKind_DataProcessingInstruction_choice;
      result->_target=ARM_DataProcessingInstruction_decode(_instr, result, ARM_InstructionKind_DataProcessingInstruction_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior DataProcessingInstruction");
   }
   else
   if((_field&28)==16) {
      result->_choice=ARM_InstructionKind_LoadStoreMultipleInstruction_choice;
      result->_target=ARM_LoadStoreMultipleInstruction_decode(_instr, result, ARM_InstructionKind_LoadStoreMultipleInstruction_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior LoadStoreMultipleInstruction");
   }
   else
   if((_field&28)==20) {
      result->_choice=ARM_InstructionKind_BranchInstruction_choice;
      result->_target=ARM_BranchInstruction_decode(_instr, result, ARM_InstructionKind_BranchInstruction_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior BranchInstruction");
   }
   
   return result;
}

struct ARM_FlexibleOperand2_st * ARM_FlexibleOperand2_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r9, 1, 0, 0, 1, 0);
   struct ARM_FlexibleOperand2_st * result=(struct ARM_FlexibleOperand2_st * )(malloc(sizeof(struct ARM_FlexibleOperand2_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: FlexibleOperand2");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&1)==1) {
      result->_choice=ARM_FlexibleOperand2_RotatedImmediate_choice;
      result->_target=ARM_RotatedImmediate_decode(_instr, result, ARM_FlexibleOperand2_RotatedImmediate_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior RotatedImmediate");
   }
   else
   if((_field&1)==0) {
      result->_choice=ARM_FlexibleOperand2_ShiftedRegister_choice;
      result->_target=ARM_ShiftedRegister_decode(_instr, result, ARM_FlexibleOperand2_ShiftedRegister_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior ShiftedRegister");
   }
   
   return result;
}

struct ARM_DataProcessingOperation_st * ARM_DataProcessingOperation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r31, 1, 0, 0, 1, 0);
   struct ARM_DataProcessingOperation_st * result=(struct ARM_DataProcessingOperation_st * )(malloc(sizeof(struct ARM_DataProcessingOperation_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: DataProcessingOperation");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&8)==0) {
      result->_choice=ARM_DataProcessingOperation_CalculationOperation_choice;
      result->_target=ARM_CalculationOperation_decode(_instr, result, ARM_DataProcessingOperation_CalculationOperation_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior CalculationOperation");
   }
   else
   if((_field&12)==12) {
      result->_choice=ARM_DataProcessingOperation_CalculationOperation_choice;
      result->_target=ARM_CalculationOperation_decode(_instr, result, ARM_DataProcessingOperation_CalculationOperation_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior CalculationOperation");
   }
   else
   if((_field&12)==8) {
      result->_choice=ARM_DataProcessingOperation_ComparisonOperation_choice;
      result->_target=ARM_ComparisonOperation_decode(_instr, result, ARM_DataProcessingOperation_ComparisonOperation_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior ComparisonOperation");
   }
   
   return result;
}

struct ARM_CalculationOperation_st * ARM_CalculationOperation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r15, 1, 0, 0, 1, 0);
   struct ARM_CalculationOperation_st * result=(struct ARM_CalculationOperation_st * )(malloc(sizeof(struct ARM_CalculationOperation_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: CalculationOperation");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->rd=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r60, 1, 0, 0, 1, 0);
   }
   
   if((_field&31)==0) {
      result->_choice=ARM_CalculationOperation_AND_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #AND");
   }
   else
   if((_field&31)==1) {
      result->_choice=ARM_CalculationOperation_ANDS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ANDS");
   }
   else
   if((_field&31)==2) {
      result->_choice=ARM_CalculationOperation_EOR_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #EOR");
   }
   else
   if((_field&31)==3) {
      result->_choice=ARM_CalculationOperation_EORS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #EORS");
   }
   else
   if((_field&31)==4) {
      result->_choice=ARM_CalculationOperation_SUB_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #SUB");
   }
   else
   if((_field&31)==5) {
      result->_choice=ARM_CalculationOperation_SUBS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #SUBS");
   }
   else
   if((_field&31)==6) {
      result->_choice=ARM_CalculationOperation_RSB_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #RSB");
   }
   else
   if((_field&31)==7) {
      result->_choice=ARM_CalculationOperation_RSBS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #RSBS");
   }
   else
   if((_field&31)==8) {
      result->_choice=ARM_CalculationOperation_ADD_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ADD");
   }
   else
   if((_field&31)==9) {
      result->_choice=ARM_CalculationOperation_ADDS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ADDS");
   }
   else
   if((_field&31)==10) {
      result->_choice=ARM_CalculationOperation_ADC_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ADC");
   }
   else
   if((_field&31)==11) {
      result->_choice=ARM_CalculationOperation_ADCS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ADCS");
   }
   else
   if((_field&31)==12) {
      result->_choice=ARM_CalculationOperation_SBC_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #SBC");
   }
   else
   if((_field&31)==13) {
      result->_choice=ARM_CalculationOperation_SBCS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #SBCS");
   }
   else
   if((_field&31)==14) {
      result->_choice=ARM_CalculationOperation_RSC_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #RSC");
   }
   else
   if((_field&31)==15) {
      result->_choice=ARM_CalculationOperation_RSCS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #RSCS");
   }
   else
   if((_field&31)==24) {
      result->_choice=ARM_CalculationOperation_ORR_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ORR");
   }
   else
   if((_field&31)==25) {
      result->_choice=ARM_CalculationOperation_ORRS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ORRS");
   }
   else
   if((_field&31)==26) {
      result->_choice=ARM_CalculationOperation_MOV_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #MOV");
   }
   else
   if((_field&31)==27) {
      result->_choice=ARM_CalculationOperation_MOVS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #MOVS");
   }
   else
   if((_field&31)==28) {
      result->_choice=ARM_CalculationOperation_BIC_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #BIC");
   }
   else
   if((_field&31)==29) {
      result->_choice=ARM_CalculationOperation_BICS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #BICS");
   }
   else
   if((_field&31)==30) {
      result->_choice=ARM_CalculationOperation_MVN_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #MVN");
   }
   else
   if((_field&31)==31) {
      result->_choice=ARM_CalculationOperation_MVNS_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #MVNS");
   }
   
   return result;
}

struct ARM_ComparisonOperation_st * ARM_ComparisonOperation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r57, 1, 0, 0, 1, 0);
   struct ARM_ComparisonOperation_st * result=(struct ARM_ComparisonOperation_st * )(malloc(sizeof(struct ARM_ComparisonOperation_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: ComparisonOperation");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&15)==8) {
      result->_choice=ARM_ComparisonOperation_TST_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #TST");
   }
   else
   if((_field&15)==9) {
      result->_choice=ARM_ComparisonOperation_TEQ_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #TEQ");
   }
   else
   if((_field&15)==10) {
      result->_choice=ARM_ComparisonOperation_CMP_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #CMP");
   }
   else
   if((_field&15)==11) {
      result->_choice=ARM_ComparisonOperation_CMN_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #CMN");
   }
   
   return result;
}

struct ARM_GprRead_st * ARM_GprRead_DataProcessingInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_GprRead_st * result=(struct ARM_GprRead_st * )(malloc(sizeof(struct ARM_GprRead_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: GprRead");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->reg=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r5, 1, 0, 0, 1, 0);
   }
   return result;
}

struct ARM_GprRead_st * ARM_GprRead_ShiftedRegister_LoadStoreOffset_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_GprRead_st * result=(struct ARM_GprRead_st * )(malloc(sizeof(struct ARM_GprRead_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: GprRead");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->reg=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r23, 1, 0, 0, 1, 0);
   }
   return result;
}

struct ARM_GprRead_st * ARM_GprRead_ShiftAmount_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_GprRead_st * result=(struct ARM_GprRead_st * )(malloc(sizeof(struct ARM_GprRead_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: GprRead");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->reg=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r85, 1, 0, 0, 1, 0);
   }
   return result;
}

struct ARM_RotatedImmediate_st * ARM_RotatedImmediate_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_RotatedImmediate_st * result=(struct ARM_RotatedImmediate_st * )(malloc(sizeof(struct ARM_RotatedImmediate_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: RotatedImmediate");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->rot=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r22, 1, 2, 0, 0, 0);
   }
   {
      result->val=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r84, 1, 0, 0, 1, 0);
   }
   return result;
}

struct ARM_ShiftSpecification_st * ARM_ShiftSpecification_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r33, 1, 0, 0, 1, 0);
   struct ARM_ShiftSpecification_st * result=(struct ARM_ShiftSpecification_st * )(malloc(sizeof(struct ARM_ShiftSpecification_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: ShiftSpecification");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&255)==6) {
      result->_choice=ARM_ShiftSpecification_RRX_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #RRX");
   }
   else
   if((_field&0)==0) {
      result->_choice=ARM_ShiftSpecification_ShiftOperation_choice;
      result->_target=ARM_ShiftOperation_decode(_instr, result, ARM_ShiftSpecification_ShiftOperation_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior ShiftOperation");
   }
   
   return result;
}

struct ARM_ShiftAmount_st * ARM_ShiftAmount_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r20, 1, 0, 0, 1, 0);
   struct ARM_ShiftAmount_st * result=(struct ARM_ShiftAmount_st * )(malloc(sizeof(struct ARM_ShiftAmount_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: ShiftAmount");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&1)==0) {
      result->_choice=ARM_ShiftAmount_Immediate_choice;
      result->_target=ARM_Immediate_decode(_instr, result, ARM_ShiftAmount_Immediate_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior Immediate");
   }
   else
   if((_field&9)==1) {
      result->_choice=ARM_ShiftAmount_GprRead_choice;
      result->_target=ARM_GprRead_decode(_instr, result, ARM_ShiftAmount_GprRead_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior GprRead");
   }
   
   return result;
}

struct ARM_ShiftOperationKind_st * ARM_ShiftOperationKind_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r69, 1, 0, 0, 1, 0);
   struct ARM_ShiftOperationKind_st * result=(struct ARM_ShiftOperationKind_st * )(malloc(sizeof(struct ARM_ShiftOperationKind_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: ShiftOperationKind");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&3)==0) {
      result->_choice=ARM_ShiftOperationKind_LSL_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LSL");
   }
   else
   if((_field&3)==1) {
      result->_choice=ARM_ShiftOperationKind_LSR_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LSR");
   }
   else
   if((_field&3)==2) {
      result->_choice=ARM_ShiftOperationKind_ASR_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ASR");
   }
   else
   if((_field&3)==3) {
      result->_choice=ARM_ShiftOperationKind_ROR_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #ROR");
   }
   
   return result;
}

struct ARM_Immediate_st * ARM_Immediate_ShiftAmount_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_Immediate_st * result=(struct ARM_Immediate_st * )(malloc(sizeof(struct ARM_Immediate_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: Immediate");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->val=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r4, 1, 0, 0, 1, 0);
   }
   return result;
}

struct ARM_LoadStoreInstruction_st * ARM_LoadStoreInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_LoadStoreInstruction_st * result=(struct ARM_LoadStoreInstruction_st * )(malloc(sizeof(struct ARM_LoadStoreInstruction_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: LoadStoreInstruction");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->rn=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r18, 1, 0, 0, 1, 0);
   }
   {
      result->rd=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r26, 1, 0, 0, 1, 0);
   }
   result->chunk_ARM_LoadStoreOffset_st=ARM_LoadStoreOffset_decode(_instr, result, ARM_LoadStoreInstruction_LoadStoreOffset_path);
   result->chunk_ARM_LoadStoreAddressCalculation_st=ARM_LoadStoreAddressCalculation_decode(_instr, result, ARM_LoadStoreInstruction_LoadStoreAddressCalculation_path);
   result->chunk_ARM_LoadStoreAddressingMode_st=ARM_LoadStoreAddressingMode_decode(_instr, result, ARM_LoadStoreInstruction_LoadStoreAddressingMode_path);
   result->chunk_ARM_LoadStoreTransfer_st=ARM_LoadStoreTransfer_decode(_instr, result, ARM_LoadStoreInstruction_LoadStoreTransfer_path);
   return result;
}

struct ARM_LoadStoreOffset_st * ARM_LoadStoreOffset_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r37, 5, 0, 0, 1, 0);
   struct ARM_LoadStoreOffset_st * result=(struct ARM_LoadStoreOffset_st * )(malloc(sizeof(struct ARM_LoadStoreOffset_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: LoadStoreOffset");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&192)==128) {
      result->_choice=ARM_LoadStoreOffset_Immediate_choice;
      result->_target=ARM_Immediate_decode(_instr, result, ARM_LoadStoreOffset_Immediate_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior Immediate");
   }
   else
   if((_field&193)==192) {
      result->_choice=ARM_LoadStoreOffset_ShiftedRegister_choice;
      result->_target=ARM_ShiftedRegister_decode(_instr, result, ARM_LoadStoreOffset_ShiftedRegister_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior ShiftedRegister");
   }
   else
   if((_field&190)==0) {
      result->_choice=ARM_LoadStoreOffset_GprRead_choice;
      result->_target=ARM_GprRead_decode(_instr, result, ARM_LoadStoreOffset_GprRead_path);
      HADL_Debug_printMessage("(FMT) ... Matching behavior GprRead");
   }
   
   return result;
}

struct ARM_LoadStoreAddressCalculation_st * ARM_LoadStoreAddressCalculation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r75, 1, 0, 0, 1, 0);
   struct ARM_LoadStoreAddressCalculation_st * result=(struct ARM_LoadStoreAddressCalculation_st * )(malloc(sizeof(struct ARM_LoadStoreAddressCalculation_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: LoadStoreAddressCalculation");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&1)==1) {
      result->_choice=ARM_LoadStoreAddressCalculation_UP_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #UP");
   }
   else
   if((_field&1)==0) {
      result->_choice=ARM_LoadStoreAddressCalculation_DOWN_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #DOWN");
   }
   
   return result;
}

struct ARM_Immediate_st * ARM_Immediate_LoadStoreOffset_1_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_Immediate_st * result=(struct ARM_Immediate_st * )(malloc(sizeof(struct ARM_Immediate_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: Immediate");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->val=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r73, 1, 0, 1, 0, 1);
   }
   return result;
}

struct ARM_Immediate_st * ARM_Immediate_LoadStoreOffset_2_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_Immediate_st * result=(struct ARM_Immediate_st * )(malloc(sizeof(struct ARM_Immediate_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: Immediate");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->val=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r40, 2, 0, 1, 0, 1);
   }
   return result;
}

struct ARM_LoadStoreAddressingMode_st * ARM_LoadStoreAddressingMode_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r82, 2, 0, 0, 1, 0);
   struct ARM_LoadStoreAddressingMode_st * result=(struct ARM_LoadStoreAddressingMode_st * )(malloc(sizeof(struct ARM_LoadStoreAddressingMode_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: LoadStoreAddressingMode");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&2)==0) {
      result->_choice=ARM_LoadStoreAddressingMode_POSTINDEXED_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #POSTINDEXED");
   }
   else
   if((_field&3)==2) {
      result->_choice=ARM_LoadStoreAddressingMode_PREINDEXED_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #PREINDEXED");
   }
   else
   if((_field&3)==3) {
      result->_choice=ARM_LoadStoreAddressingMode_AUTOINDEXED_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #AUTOINDEXED");
   }
   
   return result;
}

struct ARM_LoadStoreTransfer_st * ARM_LoadStoreTransfer_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r93, 5, 0, 0, 1, 0);
   struct ARM_LoadStoreTransfer_st * result=(struct ARM_LoadStoreTransfer_st * )(malloc(sizeof(struct ARM_LoadStoreTransfer_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: LoadStoreTransfer");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&28)==16) {
      result->_choice=ARM_LoadStoreTransfer_STR_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #STR");
   }
   else
   if((_field&28)==20) {
      result->_choice=ARM_LoadStoreTransfer_LDR_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LDR");
   }
   else
   if((_field&28)==24) {
      result->_choice=ARM_LoadStoreTransfer_STRB_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #STRB");
   }
   else
   if((_field&28)==28) {
      result->_choice=ARM_LoadStoreTransfer_LDRB_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LDRB");
   }
   else
   if((_field&23)==6) {
      result->_choice=ARM_LoadStoreTransfer_LDRSB_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LDRSB");
   }
   else
   if((_field&23)==1) {
      result->_choice=ARM_LoadStoreTransfer_STRH_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #STRH");
   }
   else
   if((_field&23)==5) {
      result->_choice=ARM_LoadStoreTransfer_LDRH_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LDRH");
   }
   else
   if((_field&23)==7) {
      result->_choice=ARM_LoadStoreTransfer_LDRSH_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LDRSH");
   }
   
   return result;
}

struct ARM_LoadStoreMultipleInstruction_st * ARM_LoadStoreMultipleInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_LoadStoreMultipleInstruction_st * result=(struct ARM_LoadStoreMultipleInstruction_st * )(malloc(sizeof(struct ARM_LoadStoreMultipleInstruction_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: LoadStoreMultipleInstruction");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->sr=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r67, 1, 0, 0, 1, 0);
   }
   {
      result->rn=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r56, 1, 0, 0, 1, 0);
   }
   {
      result->rl=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r55, 1, 0, 0, 1, 0);
   }
   result->chunk_ARM_LoadStoreMultipleTransfer_st=ARM_LoadStoreMultipleTransfer_decode(_instr, result, ARM_LoadStoreMultipleInstruction_LoadStoreMultipleTransfer_path);
   result->chunk_ARM_LoadStoreMultipleWriteBack_st=ARM_LoadStoreMultipleWriteBack_decode(_instr, result, ARM_LoadStoreMultipleInstruction_LoadStoreMultipleWriteBack_path);
   return result;
}

struct ARM_LoadStoreMultipleTransfer_st * ARM_LoadStoreMultipleTransfer_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r7, 1, 0, 0, 1, 0);
   struct ARM_LoadStoreMultipleTransfer_st * result=(struct ARM_LoadStoreMultipleTransfer_st * )(malloc(sizeof(struct ARM_LoadStoreMultipleTransfer_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: LoadStoreMultipleTransfer");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->inc=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r10, 1, 0, 0, 1, 0);
   }
   {
      result->bfore=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r1, 1, 0, 0, 1, 0);
   }
   
   if((_field&1)==1) {
      result->_choice=ARM_LoadStoreMultipleTransfer_LOAD_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #LOAD");
   }
   else
   if((_field&1)==0) {
      result->_choice=ARM_LoadStoreMultipleTransfer_STORE_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #STORE");
   }
   
   return result;
}

struct ARM_LoadStoreMultipleWriteBack_st * ARM_LoadStoreMultipleWriteBack_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r38, 1, 0, 0, 1, 0);
   struct ARM_LoadStoreMultipleWriteBack_st * result=(struct ARM_LoadStoreMultipleWriteBack_st * )(malloc(sizeof(struct ARM_LoadStoreMultipleWriteBack_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: LoadStoreMultipleWriteBack");
   }
   result->_parent=_parent;
   result->_path=_path;
   
   if((_field&1)==1) {
      result->_choice=ARM_LoadStoreMultipleWriteBack_WRITE_BACK_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #WRITE_BACK");
   }
   else
   if((_field&1)==0) {
      result->_choice=ARM_LoadStoreMultipleWriteBack_NO_WRITE_BACK_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #NO_WRITE_BACK");
   }
   
   return result;
}

struct ARM_BranchInstruction_st * ARM_BranchInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   HADL_Int32 _field=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r64, 1, 0, 0, 1, 0);
   struct ARM_BranchInstruction_st * result=(struct ARM_BranchInstruction_st * )(malloc(sizeof(struct ARM_BranchInstruction_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: BranchInstruction");
   }
   result->_parent=_parent;
   result->_path=_path;
   {
      result->offset=HADL_Field_getValue<HADL_Int32,HADL_Int32>(_instr, _r86, 1, 2, 0, 0, 1);
   }
   
   if((_field&1)==0) {
      result->_choice=ARM_BranchInstruction_B_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #B");
   }
   else
   if((_field&1)==1) {
      result->_choice=ARM_BranchInstruction_BL_choice;
      HADL_Debug_printMessage("(FMT) ... Matching #BL");
   }
   
   return result;
}

struct ARM_Instruction_st * ARM_Instruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_Instruction_st * result=(struct ARM_Instruction_st * )(malloc(sizeof(struct ARM_Instruction_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: Instruction");
   }
   result->_parent=_parent;
   result->_path=_path;
   result->chunk_ARM_Condition_st=ARM_Condition_decode(_instr, result, ARM_Instruction_Condition_path);
   result->chunk_ARM_InstructionKind_st=ARM_InstructionKind_decode(_instr, result, ARM_Instruction_InstructionKind_path);
   return result;
}

struct ARM_DataProcessingInstruction_st * ARM_DataProcessingInstruction_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_DataProcessingInstruction_st * result=(struct ARM_DataProcessingInstruction_st * )(malloc(sizeof(struct ARM_DataProcessingInstruction_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: DataProcessingInstruction");
   }
   result->_parent=_parent;
   result->_path=_path;
   result->chunk_ARM_GprRead_st=ARM_GprRead_decode(_instr, result, ARM_DataProcessingInstruction_GprRead_path);
   result->chunk_ARM_FlexibleOperand2_st=ARM_FlexibleOperand2_decode(_instr, result, ARM_DataProcessingInstruction_FlexibleOperand2_path);
   result->chunk_ARM_DataProcessingOperation_st=ARM_DataProcessingOperation_decode(_instr, result, ARM_DataProcessingInstruction_DataProcessingOperation_path);
   return result;
}

struct ARM_GprRead_st * ARM_GprRead_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_GprRead_st * result;
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: GprRead");
   }
   
   if(HADL_checkPath<HADL_Int32>(_instr, NULL, 0, 0, 0, _parent, _path, 1, ARM_DataProcessingInstruction_GprRead_path))result=ARM_GprRead_DataProcessingInstruction_decode(_instr, _parent, _path);
   else
   if(HADL_checkPath<HADL_Int32>(_instr, NULL, 0, 0, 0, _parent, _path, 1, ARM_ShiftedRegister_GprRead_path))result=ARM_GprRead_ShiftedRegister_LoadStoreOffset_decode(_instr, _parent, _path);
   else
   if(HADL_checkPath<HADL_Int32>(_instr, NULL, 0, 0, 0, _parent, _path, 1, ARM_LoadStoreOffset_GprRead_path))result=ARM_GprRead_ShiftedRegister_LoadStoreOffset_decode(_instr, _parent, _path);
   else
   if(HADL_checkPath<HADL_Int32>(_instr, NULL, 0, 0, 0, _parent, _path, 1, ARM_ShiftAmount_GprRead_path))result=ARM_GprRead_ShiftAmount_decode(_instr, _parent, _path);
   
   return result;
}

struct ARM_Immediate_st * ARM_Immediate_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_Immediate_st * result;
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: Immediate");
   }
   
   if(HADL_checkPath<HADL_Int32>(_instr, NULL, 0, 0, 0, _parent, _path, 1, ARM_ShiftAmount_Immediate_path))result=ARM_Immediate_ShiftAmount_decode(_instr, _parent, _path);
   else
   if(HADL_checkPath<HADL_Int32>(_instr, _r62, 1, 1, 1, _parent, _path, 1, ARM_LoadStoreOffset_Immediate_path))result=ARM_Immediate_LoadStoreOffset_1_decode(_instr, _parent, _path);
   else
   if(HADL_checkPath<HADL_Int32>(_instr, _r27, 1, 1, 0, _parent, _path, 1, ARM_LoadStoreOffset_Immediate_path))result=ARM_Immediate_LoadStoreOffset_2_decode(_instr, _parent, _path);
   
   return result;
}

struct ARM_ShiftedRegister_st * ARM_ShiftedRegister_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_ShiftedRegister_st * result=(struct ARM_ShiftedRegister_st * )(malloc(sizeof(struct ARM_ShiftedRegister_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: ShiftedRegister");
   }
   result->_parent=_parent;
   result->_path=_path;
   result->chunk_ARM_GprRead_st=ARM_GprRead_decode(_instr, result, ARM_ShiftedRegister_GprRead_path);
   result->chunk_ARM_ShiftSpecification_st=ARM_ShiftSpecification_decode(_instr, result, ARM_ShiftedRegister_ShiftSpecification_path);
   return result;
}

struct ARM_ShiftOperation_st * ARM_ShiftOperation_decode(HADL_Int32 _instr, void * _parent, enum ARM_Paths_en _path) {
   struct ARM_ShiftOperation_st * result=(struct ARM_ShiftOperation_st * )(malloc(sizeof(struct ARM_ShiftOperation_st)));
   {
      HADL_Debug_printMessage("(FMT) Decoding behavior: ShiftOperation");
   }
   result->_parent=_parent;
   result->_path=_path;
   result->chunk_ARM_ShiftAmount_st=ARM_ShiftAmount_decode(_instr, result, ARM_ShiftOperation_ShiftAmount_path);
   result->chunk_ARM_ShiftOperationKind_st=ARM_ShiftOperationKind_decode(_instr, result, ARM_ShiftOperation_ShiftOperationKind_path);
   return result;
}
#endif
   
