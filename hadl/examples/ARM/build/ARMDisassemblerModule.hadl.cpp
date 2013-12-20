#ifndef ARMDisassemblerModule
   
#define ARMDisassemblerModule
   


#include "stdlib.h"

#include "string.h"

#include "hadl-fields.h"

#include "hadl-paths.h"

#include "hadl-string.h"

#include "hadl-debug.h"

#include "ARMDisassemblerHeader.hadl.cpp"

void ARM_Instruction_disassemble(struct ARM_Instruction_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: Instruction");
   }
   {
      char _buf6[HADL_BUFFER_SIZE];
      {
         char _buf101[HADL_BUFFER_SIZE];
         char * _tmpArgs[]= {_buf101};
         {
            char * _tmpArgs[]= {};
            ARM_Condition_disassemble((struct ARM_Condition_st * )(_this->chunk_ARM_Condition_st), _buf101, 0, _tmpArgs);
         }
         ARM_InstructionKind_disassemble((struct ARM_InstructionKind_st * )(_this->chunk_ARM_InstructionKind_st), _buf6, 1, _tmpArgs);
      }
      strcpy(_buffer, _buf6);
   }
}

void ARM_Condition_disassemble(struct ARM_Condition_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: Condition");
   }
   * _buffer=0;
   switch(_this->_choice) {
      case ARM_Condition_EQ_choice:
         {
            char * _buf70="EQ";
            strcat(_buffer, _buf70);
         }
         break;
      
      case ARM_Condition_NE_choice:
         {
            char * _buf66="NE";
            strcat(_buffer, _buf66);
         }
         break;
      
      case ARM_Condition_CS_choice:
         {
            char * _buf38="CS";
            strcat(_buffer, _buf38);
         }
         break;
      
      case ARM_Condition_CC_choice:
         {
            char * _buf31="CC";
            strcat(_buffer, _buf31);
         }
         break;
      
      case ARM_Condition_MI_choice:
         {
            char * _buf74="MI";
            strcat(_buffer, _buf74);
         }
         break;
      
      case ARM_Condition_PL_choice:
         {
            char * _buf42="PL";
            strcat(_buffer, _buf42);
         }
         break;
      
      case ARM_Condition_VS_choice:
         {
            char * _buf46="VS";
            strcat(_buffer, _buf46);
         }
         break;
      
      case ARM_Condition_VC_choice:
         {
            char * _buf54="VC";
            strcat(_buffer, _buf54);
         }
         break;
      
      case ARM_Condition_HI_choice:
         {
            char * _buf93="HI";
            strcat(_buffer, _buf93);
         }
         break;
      
      case ARM_Condition_LS_choice:
         {
            char * _buf45="LS";
            strcat(_buffer, _buf45);
         }
         break;
      
      case ARM_Condition_GE_choice:
         {
            char * _buf59="GE";
            strcat(_buffer, _buf59);
         }
         break;
      
      case ARM_Condition_LT_choice:
         {
            char * _buf81="LT";
            strcat(_buffer, _buf81);
         }
         break;
      
      case ARM_Condition_GT_choice:
         {
            char * _buf34="GT";
            strcat(_buffer, _buf34);
         }
         break;
      
      case ARM_Condition_LE_choice:
         {
            char * _buf41="LE";
            strcat(_buffer, _buf41);
         }
         break;
      
      case ARM_Condition_AL_choice:
         {
            char * _buf78="";
            strcat(_buffer, _buf78);
         }
         break;
      
      case ARM_Condition_NV_choice:
         {
            char * _buf55="NV";
            strcat(_buffer, _buf55);
         }
         break;
      
   }
}

void ARM_DataProcessingInstruction_disassemble(struct ARM_DataProcessingInstruction_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: DataProcessingInstruction");
   }
   {
      char _buf9[HADL_BUFFER_SIZE];
      {
         char _buf103[HADL_BUFFER_SIZE];
         char * _buf314=",";
         char _buf105[HADL_BUFFER_SIZE];
         {
            char * _buf102=_args[0];
            char _buf96[HADL_BUFFER_SIZE];
            char * _tmpArgs[]= {_buf102, _buf96};
            {
               char * _tmpArgs[]= {};
               ARM_GprRead_disassemble((struct ARM_GprRead_st * )(_this->chunk_ARM_GprRead_st), _buf96, 0, _tmpArgs);
            }
            ARM_DataProcessingOperation_disassemble((struct ARM_DataProcessingOperation_st * )(_this->chunk_ARM_DataProcessingOperation_st), _buf103, 2, _tmpArgs);
         }
         {
            char * _tmpArgs[]= {};
            ARM_FlexibleOperand2_disassemble((struct ARM_FlexibleOperand2_st * )(_this->chunk_ARM_FlexibleOperand2_st), _buf105, 0, _tmpArgs);
         }
         * _buf9=0;
         strcat(_buf9, _buf103);
         strcat(_buf9, _buf314);
         strcat(_buf9, _buf105);
      }
      strcpy(_buffer, _buf9);
   }
}

void ARM_GprRead_disassemble(struct ARM_GprRead_st * _this, char * _buffer, int _count, char * _args[]) {
   char reg_buffer[HADL_BUFFER_SIZE];
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: GprRead");
   }
   {
      char _buf16[HADL_BUFFER_SIZE];
      {
         char * _buf145="R";
         char _buf125[HADL_BUFFER_SIZE];
         HADL_String_convert<HADL_Int32>(_buf125, _this->reg, 10, "", "");
         * _buf16=0;
         strcat(_buf16, _buf145);
         strcat(_buf16, _buf125);
      }
      strcpy(reg_buffer, _buf16);
   }
   {
      char * _buf3=reg_buffer;
      strcpy(_buffer, _buf3);
   }
}

void ARM_CalculationOperation_disassemble(struct ARM_CalculationOperation_st * _this, char * _buffer, int _count, char * _args[]) {
   char rd_buffer[HADL_BUFFER_SIZE];
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: CalculationOperation");
   }
   * _buffer=0;
   {
      char _buf18[HADL_BUFFER_SIZE];
      {
         char * _buf288="R";
         char _buf123[HADL_BUFFER_SIZE];
         HADL_String_convert<HADL_Int32>(_buf123, _this->rd, 10, "", "");
         * _buf18=0;
         strcat(_buf18, _buf288);
         strcat(_buf18, _buf123);
      }
      strcpy(rd_buffer, _buf18);
   }
   switch(_this->_choice) {
      case ARM_CalculationOperation_AND_choice:
         {
            char _buf36[HADL_BUFFER_SIZE];
            {
               char * _buf334="AND";
               char * _buf335=_args[0];
               char * _buf336=" ";
               char * _buf337=rd_buffer;
               char * _buf338=", ";
               char * _buf339=_args[1];
               * _buf36=0;
               strcat(_buf36, _buf334);
               strcat(_buf36, _buf335);
               strcat(_buf36, _buf336);
               strcat(_buf36, _buf337);
               strcat(_buf36, _buf338);
               strcat(_buf36, _buf339);
            }
            strcat(_buffer, _buf36);
         }
         break;
      
      case ARM_CalculationOperation_ANDS_choice:
         {
            char _buf91[HADL_BUFFER_SIZE];
            {
               char * _buf221="AND";
               char * _buf222=_args[0];
               char * _buf223="S";
               char * _buf224=" ";
               char * _buf225=rd_buffer;
               char * _buf226=", ";
               char * _buf227=_args[1];
               * _buf91=0;
               strcat(_buf91, _buf221);
               strcat(_buf91, _buf222);
               strcat(_buf91, _buf223);
               strcat(_buf91, _buf224);
               strcat(_buf91, _buf225);
               strcat(_buf91, _buf226);
               strcat(_buf91, _buf227);
            }
            strcat(_buffer, _buf91);
         }
         break;
      
      case ARM_CalculationOperation_EOR_choice:
         {
            char _buf44[HADL_BUFFER_SIZE];
            {
               char * _buf172="EOR";
               char * _buf173=_args[0];
               char * _buf174=" ";
               char * _buf175=rd_buffer;
               char * _buf176=", ";
               char * _buf177=_args[1];
               * _buf44=0;
               strcat(_buf44, _buf172);
               strcat(_buf44, _buf173);
               strcat(_buf44, _buf174);
               strcat(_buf44, _buf175);
               strcat(_buf44, _buf176);
               strcat(_buf44, _buf177);
            }
            strcat(_buffer, _buf44);
         }
         break;
      
      case ARM_CalculationOperation_EORS_choice:
         {
            char _buf32[HADL_BUFFER_SIZE];
            {
               char * _buf190="EOR";
               char * _buf191=_args[0];
               char * _buf192="S";
               char * _buf193=" ";
               char * _buf194=rd_buffer;
               char * _buf195=", ";
               char * _buf196=_args[1];
               * _buf32=0;
               strcat(_buf32, _buf190);
               strcat(_buf32, _buf191);
               strcat(_buf32, _buf192);
               strcat(_buf32, _buf193);
               strcat(_buf32, _buf194);
               strcat(_buf32, _buf195);
               strcat(_buf32, _buf196);
            }
            strcat(_buffer, _buf32);
         }
         break;
      
      case ARM_CalculationOperation_SUB_choice:
         {
            char _buf69[HADL_BUFFER_SIZE];
            {
               char * _buf153="SUB";
               char * _buf154=_args[0];
               char * _buf155=" ";
               char * _buf156=rd_buffer;
               char * _buf157=", ";
               char * _buf158=_args[1];
               * _buf69=0;
               strcat(_buf69, _buf153);
               strcat(_buf69, _buf154);
               strcat(_buf69, _buf155);
               strcat(_buf69, _buf156);
               strcat(_buf69, _buf157);
               strcat(_buf69, _buf158);
            }
            strcat(_buffer, _buf69);
         }
         break;
      
      case ARM_CalculationOperation_SUBS_choice:
         {
            char _buf87[HADL_BUFFER_SIZE];
            {
               char * _buf228="SUB";
               char * _buf229=_args[0];
               char * _buf230="S";
               char * _buf231=" ";
               char * _buf232=rd_buffer;
               char * _buf233=", ";
               char * _buf234=_args[1];
               * _buf87=0;
               strcat(_buf87, _buf228);
               strcat(_buf87, _buf229);
               strcat(_buf87, _buf230);
               strcat(_buf87, _buf231);
               strcat(_buf87, _buf232);
               strcat(_buf87, _buf233);
               strcat(_buf87, _buf234);
            }
            strcat(_buffer, _buf87);
         }
         break;
      
      case ARM_CalculationOperation_RSB_choice:
         {
            char _buf33[HADL_BUFFER_SIZE];
            {
               char * _buf204="RSB";
               char * _buf205=_args[0];
               char * _buf206=" ";
               char * _buf207=rd_buffer;
               char * _buf208=", ";
               char * _buf209=_args[1];
               * _buf33=0;
               strcat(_buf33, _buf204);
               strcat(_buf33, _buf205);
               strcat(_buf33, _buf206);
               strcat(_buf33, _buf207);
               strcat(_buf33, _buf208);
               strcat(_buf33, _buf209);
            }
            strcat(_buffer, _buf33);
         }
         break;
      
      case ARM_CalculationOperation_RSBS_choice:
         {
            char _buf61[HADL_BUFFER_SIZE];
            {
               char * _buf268="RSB";
               char * _buf269=_args[0];
               char * _buf270="S";
               char * _buf271=" ";
               char * _buf272=rd_buffer;
               char * _buf273=", ";
               char * _buf274=_args[1];
               * _buf61=0;
               strcat(_buf61, _buf268);
               strcat(_buf61, _buf269);
               strcat(_buf61, _buf270);
               strcat(_buf61, _buf271);
               strcat(_buf61, _buf272);
               strcat(_buf61, _buf273);
               strcat(_buf61, _buf274);
            }
            strcat(_buffer, _buf61);
         }
         break;
      
      case ARM_CalculationOperation_ADD_choice:
         {
            char _buf63[HADL_BUFFER_SIZE];
            {
               char * _buf252="ADD";
               char * _buf253=_args[0];
               char * _buf254=" ";
               char * _buf255=rd_buffer;
               char * _buf256=", ";
               char * _buf257=_args[1];
               * _buf63=0;
               strcat(_buf63, _buf252);
               strcat(_buf63, _buf253);
               strcat(_buf63, _buf254);
               strcat(_buf63, _buf255);
               strcat(_buf63, _buf256);
               strcat(_buf63, _buf257);
            }
            strcat(_buffer, _buf63);
         }
         break;
      
      case ARM_CalculationOperation_ADDS_choice:
         {
            char _buf58[HADL_BUFFER_SIZE];
            {
               char * _buf197="ADD";
               char * _buf198=_args[0];
               char * _buf199="S";
               char * _buf200=" ";
               char * _buf201=rd_buffer;
               char * _buf202=", ";
               char * _buf203=_args[1];
               * _buf58=0;
               strcat(_buf58, _buf197);
               strcat(_buf58, _buf198);
               strcat(_buf58, _buf199);
               strcat(_buf58, _buf200);
               strcat(_buf58, _buf201);
               strcat(_buf58, _buf202);
               strcat(_buf58, _buf203);
            }
            strcat(_buffer, _buf58);
         }
         break;
      
      case ARM_CalculationOperation_ADC_choice:
         {
            char _buf37[HADL_BUFFER_SIZE];
            {
               char * _buf166="ADC";
               char * _buf167=_args[0];
               char * _buf168=" ";
               char * _buf169=rd_buffer;
               char * _buf170=", ";
               char * _buf171=_args[1];
               * _buf37=0;
               strcat(_buf37, _buf166);
               strcat(_buf37, _buf167);
               strcat(_buf37, _buf168);
               strcat(_buf37, _buf169);
               strcat(_buf37, _buf170);
               strcat(_buf37, _buf171);
            }
            strcat(_buffer, _buf37);
         }
         break;
      
      case ARM_CalculationOperation_ADCS_choice:
         {
            char _buf75[HADL_BUFFER_SIZE];
            {
               char * _buf343="ADC";
               char * _buf344=_args[0];
               char * _buf345="S";
               char * _buf346=" ";
               char * _buf347=rd_buffer;
               char * _buf348=", ";
               char * _buf349=_args[1];
               * _buf75=0;
               strcat(_buf75, _buf343);
               strcat(_buf75, _buf344);
               strcat(_buf75, _buf345);
               strcat(_buf75, _buf346);
               strcat(_buf75, _buf347);
               strcat(_buf75, _buf348);
               strcat(_buf75, _buf349);
            }
            strcat(_buffer, _buf75);
         }
         break;
      
      case ARM_CalculationOperation_SBC_choice:
         {
            char _buf26[HADL_BUFFER_SIZE];
            {
               char * _buf215="SBC";
               char * _buf216=_args[0];
               char * _buf217=" ";
               char * _buf218=rd_buffer;
               char * _buf219=", ";
               char * _buf220=_args[1];
               * _buf26=0;
               strcat(_buf26, _buf215);
               strcat(_buf26, _buf216);
               strcat(_buf26, _buf217);
               strcat(_buf26, _buf218);
               strcat(_buf26, _buf219);
               strcat(_buf26, _buf220);
            }
            strcat(_buffer, _buf26);
         }
         break;
      
      case ARM_CalculationOperation_SBCS_choice:
         {
            char _buf62[HADL_BUFFER_SIZE];
            {
               char * _buf275="SBC";
               char * _buf276=_args[0];
               char * _buf277="S";
               char * _buf278=" ";
               char * _buf279=rd_buffer;
               char * _buf280=", ";
               char * _buf281=_args[1];
               * _buf62=0;
               strcat(_buf62, _buf275);
               strcat(_buf62, _buf276);
               strcat(_buf62, _buf277);
               strcat(_buf62, _buf278);
               strcat(_buf62, _buf279);
               strcat(_buf62, _buf280);
               strcat(_buf62, _buf281);
            }
            strcat(_buffer, _buf62);
         }
         break;
      
      case ARM_CalculationOperation_RSC_choice:
         {
            char _buf71[HADL_BUFFER_SIZE];
            {
               char * _buf328="RSC";
               char * _buf329=_args[0];
               char * _buf330=" ";
               char * _buf331=rd_buffer;
               char * _buf332=", ";
               char * _buf333=_args[1];
               * _buf71=0;
               strcat(_buf71, _buf328);
               strcat(_buf71, _buf329);
               strcat(_buf71, _buf330);
               strcat(_buf71, _buf331);
               strcat(_buf71, _buf332);
               strcat(_buf71, _buf333);
            }
            strcat(_buffer, _buf71);
         }
         break;
      
      case ARM_CalculationOperation_RSCS_choice:
         {
            char _buf35[HADL_BUFFER_SIZE];
            {
               char * _buf289="RSC";
               char * _buf290=_args[0];
               char * _buf291="S";
               char * _buf292=" ";
               char * _buf293=rd_buffer;
               char * _buf294=", ";
               char * _buf295=_args[1];
               * _buf35=0;
               strcat(_buf35, _buf289);
               strcat(_buf35, _buf290);
               strcat(_buf35, _buf291);
               strcat(_buf35, _buf292);
               strcat(_buf35, _buf293);
               strcat(_buf35, _buf294);
               strcat(_buf35, _buf295);
            }
            strcat(_buffer, _buf35);
         }
         break;
      
      case ARM_CalculationOperation_ORR_choice:
         {
            char _buf53[HADL_BUFFER_SIZE];
            {
               char * _buf258="ORR";
               char * _buf259=_args[0];
               char * _buf260=" ";
               char * _buf261=rd_buffer;
               char * _buf262=", ";
               char * _buf263=_args[1];
               * _buf53=0;
               strcat(_buf53, _buf258);
               strcat(_buf53, _buf259);
               strcat(_buf53, _buf260);
               strcat(_buf53, _buf261);
               strcat(_buf53, _buf262);
               strcat(_buf53, _buf263);
            }
            strcat(_buffer, _buf53);
         }
         break;
      
      case ARM_CalculationOperation_ORRS_choice:
         {
            char _buf88[HADL_BUFFER_SIZE];
            {
               char * _buf235="ORR";
               char * _buf236=_args[0];
               char * _buf237="S";
               char * _buf238=" ";
               char * _buf239=rd_buffer;
               char * _buf240=", ";
               char * _buf241=_args[1];
               * _buf88=0;
               strcat(_buf88, _buf235);
               strcat(_buf88, _buf236);
               strcat(_buf88, _buf237);
               strcat(_buf88, _buf238);
               strcat(_buf88, _buf239);
               strcat(_buf88, _buf240);
               strcat(_buf88, _buf241);
            }
            strcat(_buffer, _buf88);
         }
         break;
      
      case ARM_CalculationOperation_BIC_choice:
         {
            char _buf40[HADL_BUFFER_SIZE];
            {
               char * _buf246="BIC";
               char * _buf247=_args[0];
               char * _buf248=" ";
               char * _buf249=rd_buffer;
               char * _buf250=", ";
               char * _buf251=_args[1];
               * _buf40=0;
               strcat(_buf40, _buf246);
               strcat(_buf40, _buf247);
               strcat(_buf40, _buf248);
               strcat(_buf40, _buf249);
               strcat(_buf40, _buf250);
               strcat(_buf40, _buf251);
            }
            strcat(_buffer, _buf40);
         }
         break;
      
      case ARM_CalculationOperation_BICS_choice:
         {
            char _buf48[HADL_BUFFER_SIZE];
            {
               char * _buf178="BIC";
               char * _buf179=_args[0];
               char * _buf180="S";
               char * _buf181=" ";
               char * _buf182=rd_buffer;
               char * _buf183=", ";
               char * _buf184=_args[1];
               * _buf48=0;
               strcat(_buf48, _buf178);
               strcat(_buf48, _buf179);
               strcat(_buf48, _buf180);
               strcat(_buf48, _buf181);
               strcat(_buf48, _buf182);
               strcat(_buf48, _buf183);
               strcat(_buf48, _buf184);
            }
            strcat(_buffer, _buf48);
         }
         break;
      
      case ARM_CalculationOperation_MOV_choice:
         {
            char _buf83[HADL_BUFFER_SIZE];
            {
               char * _buf242="MOV";
               char * _buf243=_args[0];
               char * _buf244=" ";
               char * _buf245=rd_buffer;
               * _buf83=0;
               strcat(_buf83, _buf242);
               strcat(_buf83, _buf243);
               strcat(_buf83, _buf244);
               strcat(_buf83, _buf245);
            }
            strcat(_buffer, _buf83);
         }
         break;
      
      case ARM_CalculationOperation_MOVS_choice:
         {
            char _buf82[HADL_BUFFER_SIZE];
            {
               char * _buf160="MOV";
               char * _buf161=_args[0];
               char * _buf162="S";
               char * _buf163=" ";
               char * _buf164=rd_buffer;
               * _buf82=0;
               strcat(_buf82, _buf160);
               strcat(_buf82, _buf161);
               strcat(_buf82, _buf162);
               strcat(_buf82, _buf163);
               strcat(_buf82, _buf164);
            }
            strcat(_buffer, _buf82);
         }
         break;
      
      case ARM_CalculationOperation_MVN_choice:
         {
            char _buf84[HADL_BUFFER_SIZE];
            {
               char * _buf264="MVN";
               char * _buf265=_args[0];
               char * _buf266=" ";
               char * _buf267=rd_buffer;
               * _buf84=0;
               strcat(_buf84, _buf264);
               strcat(_buf84, _buf265);
               strcat(_buf84, _buf266);
               strcat(_buf84, _buf267);
            }
            strcat(_buffer, _buf84);
         }
         break;
      
      case ARM_CalculationOperation_MVNS_choice:
         {
            char _buf68[HADL_BUFFER_SIZE];
            {
               char * _buf140="MVN";
               char * _buf141=_args[0];
               char * _buf142="S";
               char * _buf143=" ";
               char * _buf144=rd_buffer;
               * _buf68=0;
               strcat(_buf68, _buf140);
               strcat(_buf68, _buf141);
               strcat(_buf68, _buf142);
               strcat(_buf68, _buf143);
               strcat(_buf68, _buf144);
            }
            strcat(_buffer, _buf68);
         }
         break;
      
   }
}

void ARM_ComparisonOperation_disassemble(struct ARM_ComparisonOperation_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: ComparisonOperation");
   }
   * _buffer=0;
   switch(_this->_choice) {
      case ARM_ComparisonOperation_TST_choice:
         {
            char * _buf77="TST";
            strcat(_buffer, _buf77);
         }
         break;
      
      case ARM_ComparisonOperation_TEQ_choice:
         {
            char * _buf73="TEQ";
            strcat(_buffer, _buf73);
         }
         break;
      
      case ARM_ComparisonOperation_CMP_choice:
         {
            char * _buf52="CMP";
            strcat(_buffer, _buf52);
         }
         break;
      
      case ARM_ComparisonOperation_CMN_choice:
         {
            char * _buf65="CMN";
            strcat(_buffer, _buf65);
         }
         break;
      
   }
   {
      char _buf24[HADL_BUFFER_SIZE];
      {
         char * _buf351=_args[0];
         char * _buf352=" ";
         char * _buf353=_args[1];
         * _buf24=0;
         strcat(_buf24, _buf351);
         strcat(_buf24, _buf352);
         strcat(_buf24, _buf353);
      }
      strcat(_buffer, _buf24);
   }
}

void ARM_Immediate_FlexibleOperand2_ShiftAmount_disassemble(struct ARM_Immediate_st * _this, char * _buffer, int _count, char * _args[]) {
   char val_buffer[HADL_BUFFER_SIZE];
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: Immediate");
   }
   {
      char _buf13[HADL_BUFFER_SIZE];
      {
         char * _buf159="#";
         char _buf122[HADL_BUFFER_SIZE];
         HADL_String_convert<HADL_Int32>(_buf122, _this->val, 16, "0x", "");
         * _buf13=0;
         strcat(_buf13, _buf159);
         strcat(_buf13, _buf122);
      }
      strcpy(val_buffer, _buf13);
   }
   {
      char * _buf2=val_buffer;
      strcpy(_buffer, _buf2);
   }
}

void ARM_RotatedImmediate_disassemble(struct ARM_RotatedImmediate_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: RotatedImmediate");
   }
   {
      char _buf10[HADL_BUFFER_SIZE];
      {
         char * _buf149="#";
         char _buf120[HADL_BUFFER_SIZE];
         {
            int _r96[1 ][ 3]= {{31, _this->rot, 1}};
            HADL_String_convert<HADL_Int32>(_buf120, HADL_Field_getValue<HADL_Int32,HADL_Int32>(_this->val, _r96, 1, 0, 0, 1, 0)|_this->val<<32-_this->rot, 16, "0x", "");
         }
         * _buf10=0;
         strcat(_buf10, _buf149);
         strcat(_buf10, _buf120);
      }
      strcpy(_buffer, _buf10);
   }
}

void ARM_ShiftedRegister_FlexibleOperand2_disassemble(struct ARM_ShiftedRegister_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: ShiftedRegister");
   }
   {
      char _buf5[HADL_BUFFER_SIZE];
      {
         char _buf111[HADL_BUFFER_SIZE];
         char * _buf165=" ";
         char _buf109[HADL_BUFFER_SIZE];
         {
            char * _tmpArgs[]= {};
            ARM_GprRead_disassemble((struct ARM_GprRead_st * )(_this->chunk_ARM_GprRead_st), _buf111, 0, _tmpArgs);
         }
         {
            char * _tmpArgs[]= {};
            ARM_ShiftSpecification_disassemble((struct ARM_ShiftSpecification_st * )(_this->chunk_ARM_ShiftSpecification_st), _buf109, 0, _tmpArgs);
         }
         * _buf5=0;
         strcat(_buf5, _buf111);
         strcat(_buf5, _buf165);
         strcat(_buf5, _buf109);
      }
      strcpy(_buffer, _buf5);
   }
}

void ARM_ShiftSpecification_disassemble(struct ARM_ShiftSpecification_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: ShiftSpecification");
   }
   * _buffer=0;
   switch(_this->_choice) {
      case ARM_ShiftSpecification_RRX_choice:
         {
            char * _buf29="RRX";
            strcat(_buffer, _buf29);
         }
         break;
      
   }
}

void ARM_ShiftOperation_disassemble(struct ARM_ShiftOperation_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: ShiftOperation");
   }
   {
      char _buf4[HADL_BUFFER_SIZE];
      {
         char _buf104[HADL_BUFFER_SIZE];
         char * _buf296=" ";
         char _buf110[HADL_BUFFER_SIZE];
         {
            char * _tmpArgs[]= {};
            ARM_ShiftOperationKind_disassemble((struct ARM_ShiftOperationKind_st * )(_this->chunk_ARM_ShiftOperationKind_st), _buf104, 0, _tmpArgs);
         }
         {
            char * _tmpArgs[]= {};
            ARM_ShiftAmount_disassemble((struct ARM_ShiftAmount_st * )(_this->chunk_ARM_ShiftAmount_st), _buf110, 0, _tmpArgs);
         }
         * _buf4=0;
         strcat(_buf4, _buf104);
         strcat(_buf4, _buf296);
         strcat(_buf4, _buf110);
      }
      strcpy(_buffer, _buf4);
   }
}

void ARM_ShiftOperationKind_disassemble(struct ARM_ShiftOperationKind_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: ShiftOperationKind");
   }
   * _buffer=0;
   switch(_this->_choice) {
      case ARM_ShiftOperationKind_LSL_choice:
         {
            char * _buf79="LSL";
            strcat(_buffer, _buf79);
         }
         break;
      
      case ARM_ShiftOperationKind_LSR_choice:
         {
            char * _buf28="LSR";
            strcat(_buffer, _buf28);
         }
         break;
      
      case ARM_ShiftOperationKind_ASR_choice:
         {
            char * _buf64="ASR";
            strcat(_buffer, _buf64);
         }
         break;
      
      case ARM_ShiftOperationKind_ROR_choice:
         {
            char * _buf49="ROR";
            strcat(_buffer, _buf49);
         }
         break;
      
   }
}

void ARM_LoadStoreInstruction_disassemble(struct ARM_LoadStoreInstruction_st * _this, char * _buffer, int _count, char * _args[]) {
   char rn_buffer[HADL_BUFFER_SIZE];
   char rd_buffer[HADL_BUFFER_SIZE];
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: LoadStoreInstruction");
   }
   {
      char _buf20[HADL_BUFFER_SIZE];
      {
         char * _buf310="R";
         char _buf121[HADL_BUFFER_SIZE];
         HADL_String_convert<HADL_Int32>(_buf121, _this->rn, 10, "", "");
         * _buf20=0;
         strcat(_buf20, _buf310);
         strcat(_buf20, _buf121);
      }
      strcpy(rn_buffer, _buf20);
   }
   {
      char _buf22[HADL_BUFFER_SIZE];
      {
         char * _buf350="R";
         char _buf124[HADL_BUFFER_SIZE];
         HADL_String_convert<HADL_Int32>(_buf124, _this->rd, 10, "", "");
         * _buf22=0;
         strcat(_buf22, _buf350);
         strcat(_buf22, _buf124);
      }
      strcpy(rd_buffer, _buf22);
   }
   {
      char _buf7[HADL_BUFFER_SIZE];
      {
         char _buf113[HADL_BUFFER_SIZE];
         char * _buf150=" ";
         char * _buf151=rd_buffer;
         char * _buf152=",";
         char _buf100[HADL_BUFFER_SIZE];
         {
            char * _buf112=_args[0];
            char * _tmpArgs[]= {_buf112};
            ARM_LoadStoreTransfer_disassemble((struct ARM_LoadStoreTransfer_st * )(_this->chunk_ARM_LoadStoreTransfer_st), _buf113, 1, _tmpArgs);
         }
         {
            char * _buf99=rn_buffer;
            char _buf95[HADL_BUFFER_SIZE];
            char * _tmpArgs[]= {_buf99, _buf95};
            {
               char _buf94[HADL_BUFFER_SIZE];
               char * _tmpArgs[]= {_buf94};
               {
                  char * _tmpArgs[]= {};
                  ARM_LoadStoreAddressCalculation_disassemble((struct ARM_LoadStoreAddressCalculation_st * )(_this->chunk_ARM_LoadStoreAddressCalculation_st), _buf94, 0, _tmpArgs);
               }
               ARM_LoadStoreOffset_disassemble((struct ARM_LoadStoreOffset_st * )(_this->chunk_ARM_LoadStoreOffset_st), _buf95, 1, _tmpArgs);
            }
            ARM_LoadStoreAddressingMode_disassemble((struct ARM_LoadStoreAddressingMode_st * )(_this->chunk_ARM_LoadStoreAddressingMode_st), _buf100, 2, _tmpArgs);
         }
         * _buf7=0;
         strcat(_buf7, _buf113);
         strcat(_buf7, _buf150);
         strcat(_buf7, _buf151);
         strcat(_buf7, _buf152);
         strcat(_buf7, _buf100);
      }
      strcpy(_buffer, _buf7);
   }
}

void ARM_LoadStoreAddressCalculation_disassemble(struct ARM_LoadStoreAddressCalculation_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: LoadStoreAddressCalculation");
   }
   * _buffer=0;
   switch(_this->_choice) {
      case ARM_LoadStoreAddressCalculation_UP_choice:
         {
            char * _buf60="+";
            strcat(_buffer, _buf60);
         }
         break;
      
      case ARM_LoadStoreAddressCalculation_DOWN_choice:
         {
            char * _buf39="-";
            strcat(_buffer, _buf39);
         }
         break;
      
   }
}

void ARM_LoadStoreTransfer_disassemble(struct ARM_LoadStoreTransfer_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: LoadStoreTransfer");
   }
   * _buffer=0;
   switch(_this->_choice) {
      case ARM_LoadStoreTransfer_LDR_choice:
         {
            char _buf51[HADL_BUFFER_SIZE];
            {
               char * _buf326="LDR";
               char * _buf327=_args[0];
               * _buf51=0;
               strcat(_buf51, _buf326);
               strcat(_buf51, _buf327);
            }
            strcat(_buffer, _buf51);
         }
         break;
      
      case ARM_LoadStoreTransfer_LDRH_choice:
         {
            char _buf85[HADL_BUFFER_SIZE];
            {
               char * _buf340="LDR";
               char * _buf341=_args[0];
               char * _buf342="H";
               * _buf85=0;
               strcat(_buf85, _buf340);
               strcat(_buf85, _buf341);
               strcat(_buf85, _buf342);
            }
            strcat(_buffer, _buf85);
         }
         break;
      
      case ARM_LoadStoreTransfer_LDRSH_choice:
         {
            char _buf43[HADL_BUFFER_SIZE];
            {
               char * _buf146="LDR";
               char * _buf147=_args[0];
               char * _buf148="SH";
               * _buf43=0;
               strcat(_buf43, _buf146);
               strcat(_buf43, _buf147);
               strcat(_buf43, _buf148);
            }
            strcat(_buffer, _buf43);
         }
         break;
      
      case ARM_LoadStoreTransfer_LDRB_choice:
         {
            char _buf86[HADL_BUFFER_SIZE];
            {
               char * _buf323="LDR";
               char * _buf324=_args[0];
               char * _buf325="B";
               * _buf86=0;
               strcat(_buf86, _buf323);
               strcat(_buf86, _buf324);
               strcat(_buf86, _buf325);
            }
            strcat(_buffer, _buf86);
         }
         break;
      
      case ARM_LoadStoreTransfer_LDRSB_choice:
         {
            char _buf72[HADL_BUFFER_SIZE];
            {
               char * _buf320="LDR";
               char * _buf321=_args[0];
               char * _buf322="SB";
               * _buf72=0;
               strcat(_buf72, _buf320);
               strcat(_buf72, _buf321);
               strcat(_buf72, _buf322);
            }
            strcat(_buffer, _buf72);
         }
         break;
      
      case ARM_LoadStoreTransfer_STR_choice:
         {
            char _buf76[HADL_BUFFER_SIZE];
            {
               char * _buf312="STR";
               char * _buf313=_args[0];
               * _buf76=0;
               strcat(_buf76, _buf312);
               strcat(_buf76, _buf313);
            }
            strcat(_buffer, _buf76);
         }
         break;
      
      case ARM_LoadStoreTransfer_STRH_choice:
         {
            char _buf80[HADL_BUFFER_SIZE];
            {
               char * _buf137="STR";
               char * _buf138=_args[0];
               char * _buf139="H";
               * _buf80=0;
               strcat(_buf80, _buf137);
               strcat(_buf80, _buf138);
               strcat(_buf80, _buf139);
            }
            strcat(_buffer, _buf80);
         }
         break;
      
      case ARM_LoadStoreTransfer_STRB_choice:
         {
            char _buf90[HADL_BUFFER_SIZE];
            {
               char * _buf129="STR";
               char * _buf130=_args[0];
               char * _buf131="B";
               * _buf90=0;
               strcat(_buf90, _buf129);
               strcat(_buf90, _buf130);
               strcat(_buf90, _buf131);
            }
            strcat(_buffer, _buf90);
         }
         break;
      
   }
}

void ARM_Immediate_LoadStoreOffset_disassemble(struct ARM_Immediate_st * _this, char * _buffer, int _count, char * _args[]) {
   char val_buffer[HADL_BUFFER_SIZE];
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: Immediate");
   }
   {
      char _buf15[HADL_BUFFER_SIZE];
      {
         char * _buf306="#";
         char * _buf307=_args[0];
         char _buf127[HADL_BUFFER_SIZE];
         HADL_String_convert<HADL_Int32>(_buf127, _this->val, 16, "0x", "");
         * _buf15=0;
         strcat(_buf15, _buf306);
         strcat(_buf15, _buf307);
         strcat(_buf15, _buf127);
      }
      strcpy(val_buffer, _buf15);
   }
   {
      char * _buf8=val_buffer;
      strcpy(_buffer, _buf8);
   }
}

void ARM_ShiftedRegister_LoadStoreOffset_disassemble(struct ARM_ShiftedRegister_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: ShiftedRegister");
   }
   {
      char _buf1[HADL_BUFFER_SIZE];
      {
         char * _buf286=_args[0];
         char _buf108[HADL_BUFFER_SIZE];
         char * _buf287=" ";
         char _buf107[HADL_BUFFER_SIZE];
         {
            char * _tmpArgs[]= {};
            ARM_GprRead_disassemble((struct ARM_GprRead_st * )(_this->chunk_ARM_GprRead_st), _buf108, 0, _tmpArgs);
         }
         {
            char * _tmpArgs[]= {};
            ARM_ShiftSpecification_disassemble((struct ARM_ShiftSpecification_st * )(_this->chunk_ARM_ShiftSpecification_st), _buf107, 0, _tmpArgs);
         }
         * _buf1=0;
         strcat(_buf1, _buf286);
         strcat(_buf1, _buf108);
         strcat(_buf1, _buf287);
         strcat(_buf1, _buf107);
      }
      strcpy(_buffer, _buf1);
   }
}

void ARM_LoadStoreAddressingMode_disassemble(struct ARM_LoadStoreAddressingMode_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: LoadStoreAddressingMode");
   }
   * _buffer=0;
   switch(_this->_choice) {
      case ARM_LoadStoreAddressingMode_PREINDEXED_choice:
         {
            char _buf89[HADL_BUFFER_SIZE];
            {
               char * _buf132="[";
               char * _buf133=_args[0];
               char * _buf134=",";
               char * _buf135=_args[1];
               char * _buf136="]";
               * _buf89=0;
               strcat(_buf89, _buf132);
               strcat(_buf89, _buf133);
               strcat(_buf89, _buf134);
               strcat(_buf89, _buf135);
               strcat(_buf89, _buf136);
            }
            strcat(_buffer, _buf89);
         }
         break;
      
      case ARM_LoadStoreAddressingMode_AUTOINDEXED_choice:
         {
            char _buf56[HADL_BUFFER_SIZE];
            {
               char * _buf300="[";
               char * _buf301=_args[0];
               char * _buf302=",";
               char * _buf303=_args[1];
               char * _buf304="]";
               char * _buf305="!";
               * _buf56=0;
               strcat(_buf56, _buf300);
               strcat(_buf56, _buf301);
               strcat(_buf56, _buf302);
               strcat(_buf56, _buf303);
               strcat(_buf56, _buf304);
               strcat(_buf56, _buf305);
            }
            strcat(_buffer, _buf56);
         }
         break;
      
      case ARM_LoadStoreAddressingMode_POSTINDEXED_choice:
         {
            char _buf47[HADL_BUFFER_SIZE];
            {
               char * _buf185="[";
               char * _buf186=_args[0];
               char * _buf187="]";
               char * _buf188=",";
               char * _buf189=_args[1];
               * _buf47=0;
               strcat(_buf47, _buf185);
               strcat(_buf47, _buf186);
               strcat(_buf47, _buf187);
               strcat(_buf47, _buf188);
               strcat(_buf47, _buf189);
            }
            strcat(_buffer, _buf47);
         }
         break;
      
   }
}

void ARM_LoadStoreMultipleInstruction_disassemble(struct ARM_LoadStoreMultipleInstruction_st * _this, char * _buffer, int _count, char * _args[]) {
   char rn_buffer[HADL_BUFFER_SIZE];
   char sr_buffer[HADL_BUFFER_SIZE];
   char rl_buffer[HADL_BUFFER_SIZE];
   {
      HADL_Debug_printMessage("(SYN) Disassembling syntax: LoadStoreMultipleInstruction");
   }
   {
      char _buf12[HADL_BUFFER_SIZE];
      {
         char * _buf315="R";
         char _buf126[HADL_BUFFER_SIZE];
         HADL_String_convert<HADL_Int32>(_buf126, _this->rn, 10, "", "");
         * _buf12=0;
         strcat(_buf12, _buf315);
         strcat(_buf12, _buf126);
      }
      strcpy(rn_buffer, _buf12);
   }
   {
      char * _buf14;
      
      if(_this->sr) {
         char * _buf118="^";
         _buf14=_buf118;
      }
      else _buf14="";
      strcpy(sr_buffer, _buf14);
   }
   {
      char _buf17[HADL_BUFFER_SIZE];
      {
         char * _buf308="{";
         char _buf128[HADL_BUFFER_SIZE];
         char * _buf309="}";
         HADL_String_convertList<HADL_Int32>(_buf128, _this->rl, "r", ",", 10, "", "");
         * _buf17=0;
         strcat(_buf17, _buf308);
         strcat(_buf17, _buf128);
         strcat(_buf17, _buf309);
      }
      strcpy(rl_buffer, _buf17);
   }
   {
      char _buf11[HADL_BUFFER_SIZE];
      {
         char _buf98[HADL_BUFFER_SIZE];
         char * _buf210=" ";
         char * _buf211=rn_buffer;
         char _buf106[HADL_BUFFER_SIZE];
         char * _buf212=",";
         char * _buf213=rl_buffer;
         char * _buf214=sr_buffer;
         {
            char * _buf97=_args[0];
            char * _tmpArgs[]= {_buf97};
            ARM_LoadStoreMultipleTransfer_disassemble((struct ARM_LoadStoreMultipleTransfer_st * )(_this->chunk_ARM_LoadStoreMultipleTransfer_st), _buf98, 1, _tmpArgs);
         }
         {
            char * _tmpArgs[]= {};
            ARM_LoadStoreMultipleWriteBack_disassemble((struct ARM_LoadStoreMultipleWriteBack_st * )(_this->chunk_ARM_LoadStoreMultipleWriteBack_st), _buf106, 0, _tmpArgs);
         }
         * _buf11=0;
         strcat(_buf11, _buf98);
         strcat(_buf11, _buf210);
         strcat(_buf11, _buf211);
         strcat(_buf11, _buf106);
         strcat(_buf11, _buf212);
         strcat(_buf11, _buf213);
         strcat(_buf11, _buf214);
      }
      strcpy(_buffer, _buf11);
   }
}

void ARM_LoadStoreMultipleTransfer_disassemble(struct ARM_LoadStoreMultipleTransfer_st * _this, char * _buffer, int _count, char * _args[]) {
   char inc_buffer[HADL_BUFFER_SIZE];
   char bfore_buffer[HADL_BUFFER_SIZE];
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: LoadStoreMultipleTransfer");
   }
   * _buffer=0;
   {
      char * _buf21;
      
      if(_this->inc) {
         char * _buf117="I";
         _buf21=_buf117;
      }
      else {
         char * _buf116="D";
         _buf21=_buf116;
      }
      strcpy(inc_buffer, _buf21);
   }
   {
      char * _buf23;
      
      if(_this->bfore) {
         char * _buf115="B";
         _buf23=_buf115;
      }
      else {
         char * _buf114="A";
         _buf23=_buf114;
      }
      strcpy(bfore_buffer, _buf23);
   }
   switch(_this->_choice) {
      case ARM_LoadStoreMultipleTransfer_LOAD_choice:
         {
            char _buf92[HADL_BUFFER_SIZE];
            {
               char * _buf316="LDM";
               char * _buf317=_args[0];
               char * _buf318=inc_buffer;
               char * _buf319=bfore_buffer;
               * _buf92=0;
               strcat(_buf92, _buf316);
               strcat(_buf92, _buf317);
               strcat(_buf92, _buf318);
               strcat(_buf92, _buf319);
            }
            strcat(_buffer, _buf92);
         }
         break;
      
      case ARM_LoadStoreMultipleTransfer_STORE_choice:
         {
            char _buf30[HADL_BUFFER_SIZE];
            {
               char * _buf282="STM";
               char * _buf283=_args[0];
               char * _buf284=inc_buffer;
               char * _buf285=bfore_buffer;
               * _buf30=0;
               strcat(_buf30, _buf282);
               strcat(_buf30, _buf283);
               strcat(_buf30, _buf284);
               strcat(_buf30, _buf285);
            }
            strcat(_buffer, _buf30);
         }
         break;
      
   }
}

void ARM_LoadStoreMultipleWriteBack_disassemble(struct ARM_LoadStoreMultipleWriteBack_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: LoadStoreMultipleWriteBack");
   }
   * _buffer=0;
   switch(_this->_choice) {
      case ARM_LoadStoreMultipleWriteBack_WRITE_BACK_choice:
         {
            char * _buf57="!";
            strcat(_buffer, _buf57);
         }
         break;
      
      case ARM_LoadStoreMultipleWriteBack_NO_WRITE_BACK_choice:
         {
            char * _buf50="";
            strcat(_buffer, _buf50);
         }
         break;
      
   }
}

void ARM_BranchInstruction_disassemble(struct ARM_BranchInstruction_st * _this, char * _buffer, int _count, char * _args[]) {
   char offset_buffer[HADL_BUFFER_SIZE];
   {
      HADL_Debug_printMessage("(SYN) Disassembling with syntax: BranchInstruction");
   }
   * _buffer=0;
   {
      char _buf19[HADL_BUFFER_SIZE];
      {
         char * _buf311="#";
         char _buf119[HADL_BUFFER_SIZE];
         {
            HADL_String_convert<HADL_Int32>(_buf119, _this->offset+8, 16, "0x", "");
         }
         * _buf19=0;
         strcat(_buf19, _buf311);
         strcat(_buf19, _buf119);
      }
      strcpy(offset_buffer, _buf19);
   }
   switch(_this->_choice) {
      case ARM_BranchInstruction_B_choice:
         {
            char * _buf67="B";
            strcat(_buffer, _buf67);
         }
         break;
      
      case ARM_BranchInstruction_BL_choice:
         {
            char * _buf27="BL";
            strcat(_buffer, _buf27);
         }
         break;
      
   }
   {
      char _buf25[HADL_BUFFER_SIZE];
      {
         char * _buf297=_args[0];
         char * _buf298=" ";
         char * _buf299=offset_buffer;
         * _buf25=0;
         strcat(_buf25, _buf297);
         strcat(_buf25, _buf298);
         strcat(_buf25, _buf299);
      }
      strcat(_buffer, _buf25);
   }
}

void ARM_InstructionKind_disassemble(struct ARM_InstructionKind_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling behavior: InstructionKind");
   }
   switch(_this->_choice) {
      case ARM_InstructionKind_DataProcessingInstruction_choice:
         ARM_DataProcessingInstruction_disassemble((struct ARM_DataProcessingInstruction_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_InstructionKind_LoadStoreInstruction_choice:
         ARM_LoadStoreInstruction_disassemble((struct ARM_LoadStoreInstruction_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_InstructionKind_LoadStoreMultipleInstruction_choice:
         ARM_LoadStoreMultipleInstruction_disassemble((struct ARM_LoadStoreMultipleInstruction_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_InstructionKind_BranchInstruction_choice:
         ARM_BranchInstruction_disassemble((struct ARM_BranchInstruction_st * )(_this->_target), _buffer, _count, _args);
         break;
      
   }
}

void ARM_DataProcessingOperation_disassemble(struct ARM_DataProcessingOperation_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling behavior: DataProcessingOperation");
   }
   switch(_this->_choice) {
      case ARM_DataProcessingOperation_CalculationOperation_choice:
         ARM_CalculationOperation_disassemble((struct ARM_CalculationOperation_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_DataProcessingOperation_ComparisonOperation_choice:
         ARM_ComparisonOperation_disassemble((struct ARM_ComparisonOperation_st * )(_this->_target), _buffer, _count, _args);
         break;
      
   }
}

void ARM_FlexibleOperand2_disassemble(struct ARM_FlexibleOperand2_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling behavior: FlexibleOperand2");
   }
   switch(_this->_choice) {
      case ARM_FlexibleOperand2_Immediate_choice:
         ARM_Immediate_disassemble((struct ARM_Immediate_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_FlexibleOperand2_RotatedImmediate_choice:
         ARM_RotatedImmediate_disassemble((struct ARM_RotatedImmediate_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_FlexibleOperand2_GprRead_choice:
         ARM_GprRead_disassemble((struct ARM_GprRead_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_FlexibleOperand2_ShiftedRegister_choice:
         ARM_ShiftedRegister_disassemble((struct ARM_ShiftedRegister_st * )(_this->_target), _buffer, _count, _args);
         break;
      
   }
}

void ARM_ShiftAmount_disassemble(struct ARM_ShiftAmount_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling behavior: ShiftAmount");
   }
   switch(_this->_choice) {
      case ARM_ShiftAmount_Immediate_choice:
         ARM_Immediate_disassemble((struct ARM_Immediate_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_ShiftAmount_GprRead_choice:
         ARM_GprRead_disassemble((struct ARM_GprRead_st * )(_this->_target), _buffer, _count, _args);
         break;
      
   }
}

void ARM_LoadStoreOffset_disassemble(struct ARM_LoadStoreOffset_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling behavior: LoadStoreOffset");
   }
   switch(_this->_choice) {
      case ARM_LoadStoreOffset_Immediate_choice:
         ARM_Immediate_disassemble((struct ARM_Immediate_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_LoadStoreOffset_ShiftedRegister_choice:
         ARM_ShiftedRegister_disassemble((struct ARM_ShiftedRegister_st * )(_this->_target), _buffer, _count, _args);
         break;
      
      case ARM_LoadStoreOffset_GprRead_choice:
         ARM_GprRead_disassemble((struct ARM_GprRead_st * )(_this->_target), _buffer, _count, _args);
         break;
      
   }
}

void ARM_Immediate_disassemble(struct ARM_Immediate_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling behavior: Immediate");
   }
   
   if(HADL_checkPath<HADL_Int32>(0, NULL, 0, 0, 0, _this->_parent, _this->_path, 1, ARM_FlexibleOperand2_Immediate_path))ARM_Immediate_FlexibleOperand2_ShiftAmount_disassemble(_this, _buffer, _count, _args);
   else
   if(HADL_checkPath<HADL_Int32>(0, NULL, 0, 0, 0, _this->_parent, _this->_path, 1, ARM_ShiftAmount_Immediate_path))ARM_Immediate_FlexibleOperand2_ShiftAmount_disassemble(_this, _buffer, _count, _args);
   else
   if(HADL_checkPath<HADL_Int32>(0, NULL, 0, 0, 0, _this->_parent, _this->_path, 1, ARM_LoadStoreOffset_Immediate_path))ARM_Immediate_LoadStoreOffset_disassemble(_this, _buffer, _count, _args);
   
}

void ARM_ShiftedRegister_disassemble(struct ARM_ShiftedRegister_st * _this, char * _buffer, int _count, char * _args[]) {
   {
      HADL_Debug_printMessage("(SYN) Disassembling behavior: ShiftedRegister");
   }
   
   if(HADL_checkPath<HADL_Int32>(0, NULL, 0, 0, 0, _this->_parent, _this->_path, 1, ARM_FlexibleOperand2_ShiftedRegister_path))ARM_ShiftedRegister_FlexibleOperand2_disassemble(_this, _buffer, _count, _args);
   else
   if(HADL_checkPath<HADL_Int32>(0, NULL, 0, 0, 0, _this->_parent, _this->_path, 1, ARM_LoadStoreOffset_ShiftedRegister_path))ARM_ShiftedRegister_LoadStoreOffset_disassemble(_this, _buffer, _count, _args);
   
}
#endif
   
