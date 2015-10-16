# 
# p2a
# 
#  p2a is copyright (c) IRCCyN 2005+
#  p2a est protege par la loi sur la propriete intellectuelle
# 
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  

#version 2.0
#It can be called either by a simple 'make' command, or 'make OPTIM=1' to turn on optimisation flags.
#'make clean': remove obj files

#################################
#gadl should be compiled first: The 'libpm' is generated when running galgas ...
#################################

EXEC = a2cpp
SRCS= \
automata.cpp \
automataConfiguration.cpp \
main.cpp \
utils.cpp \
fileHeaderGeneration.cpp \
codeGenerator.cpp

#particular config:
CXX=g++
OPTIM=1
CFLAGS += $(INCLUDE_PATHS) -Wno-long-long -DLIBPM_MULTI_THREADING=0
#CFLAGS += -g
LDFLAGS +=
EXTRA_FILES_CLEAN=

#libpm related sources (these files are generated the firt time gadl is compiled).
LIBPM_PATH = ../gadl/libpm

SOURCES_DIR += $(strip $(LIBPM_PATH))/bdd
SOURCES_DIR += $(strip $(LIBPM_PATH))/cache
SOURCES_DIR += $(strip $(LIBPM_PATH))/collections
SOURCES_DIR += $(strip $(LIBPM_PATH))/command_line_interface
SOURCES_DIR += $(strip $(LIBPM_PATH))/files
SOURCES_DIR += $(strip $(LIBPM_PATH))/hash_map_generator
SOURCES_DIR += $(strip $(LIBPM_PATH))/streams
SOURCES_DIR += $(strip $(LIBPM_PATH))/strings
SOURCES_DIR += $(strip $(LIBPM_PATH))/time
SOURCES_DIR += $(strip $(LIBPM_PATH))/utilities
SOURCES_DIR += $(strip $(LIBPM_PATH))/gmp

INCLUDE_PATHS := -I$(LIBPM_PATH) $(patsubst %, -I%, $(SOURCES_DIR))

LIBPM_SRCS := C_BDD.cpp
LIBPM_SRCS += C_BDD-and-operation.cpp
LIBPM_SRCS += C_BDD-find-or-add.cpp
LIBPM_SRCS += C_BDD-single-operand-ops.cpp
LIBPM_SRCS += F_Analyze_CLI_Options.cpp
LIBPM_SRCS += C_BoolCommandLineOption.cpp
LIBPM_SRCS += C_StringCommandLineOption.cpp
LIBPM_SRCS += C_StringListCommandLineOption.cpp
LIBPM_SRCS += C_UIntCommandLineOption.cpp
LIBPM_SRCS += C_builtin_CLI_Options.cpp
LIBPM_SRCS += C_ColoredConsole.cpp
LIBPM_SRCS += PMUInt128.cpp
LIBPM_SRCS += F_GetPrime.cpp
LIBPM_SRCS += C_ErrorOut.cpp
LIBPM_SRCS += C_String.cpp
LIBPM_SRCS += AC_OutputStream.cpp
LIBPM_SRCS += F_DisplayException.cpp
LIBPM_SRCS += C_ConsoleOut.cpp
LIBPM_SRCS += unicode_character_cpp.cpp
LIBPM_SRCS += unicode_string_routines.cpp
LIBPM_SRCS += MF_Assert.cpp
LIBPM_SRCS += basic-allocation.cpp
LIBPM_SRCS += MF_MemoryControl.cpp
LIBPM_SRCS += cpp-allocation.cpp
LIBPM_SRCS += C_PrologueEpilogue.cpp
LIBPM_SRCS += md5.cpp
LIBPM_SRCS += C_TextFileWrite.cpp
LIBPM_SRCS += C_SharedObject.cpp
LIBPM_SRCS += C_DateTime.cpp
LIBPM_SRCS += C_Timer.cpp
LIBPM_SRCS += F_mainForLIBPM.cpp
LIBPM_SRCS += C_FileManager.cpp
LIBPM_SRCS += C_Data.cpp
LIBPM_SRCS += AC_FileHandleForWriting.cpp
LIBPM_SRCS += AC_FileHandle.cpp
LIBPM_SRCS += C_BinaryFileWrite.cpp
LIBPM_SRCS += C_CommandLineOption.cpp
LIBPM_SRCS += C_BigInt.cpp
LIBPM_SRCS += 64-mp_bases.c
LIBPM_SRCS += 32-mp_bases.c
LIBPM_SRCS += mpn-invertappr.c
LIBPM_SRCS += mpn-sub_1.c
LIBPM_SRCS += mpn-toom_eval_dgr3_pm1.c
LIBPM_SRCS += mpz-clrbit.c
LIBPM_SRCS += mpz-set_ui.c
LIBPM_SRCS += mpn-lshift.c
LIBPM_SRCS += mpn-sub_n.c
LIBPM_SRCS += mpn-toom_eval_dgr3_pm2.c
LIBPM_SRCS += mpz-cmp.c
LIBPM_SRCS += mpz-setbit.c
LIBPM_SRCS += mpn-lshiftc.c
LIBPM_SRCS += mpn-submul_1.c
LIBPM_SRCS += mpn-toom_eval_pm1.c
LIBPM_SRCS += mpz-com.c
LIBPM_SRCS += mpz-sizeinbase.c
LIBPM_SRCS += mpn-mu_div_qr.c
LIBPM_SRCS += mpn-tdiv_qr.c
LIBPM_SRCS += mpn-toom_eval_pm2.c
LIBPM_SRCS += mpz-combit.c
LIBPM_SRCS += mpz-sub.c
LIBPM_SRCS += mpn-mul.c
LIBPM_SRCS += mpn-toom22_mul.c
LIBPM_SRCS += mpn-toom_eval_pm2exp.c
LIBPM_SRCS += mpz-export.c
LIBPM_SRCS += mpz-sub_ui.c
LIBPM_SRCS += mpn-mul_1.c
LIBPM_SRCS += mpn-toom2_sqr.c
LIBPM_SRCS += mpn-toom_eval_pm2rexp.c
LIBPM_SRCS += mpz-fdiv_qr.c
LIBPM_SRCS += mpz-swap.c
LIBPM_SRCS += mpn-mul_basecase.c
LIBPM_SRCS += mpn-toom32_mul.c
LIBPM_SRCS += mpn-toom_interpolate_12pts.c
LIBPM_SRCS += mpz-tdiv_qr.c
LIBPM_SRCS += mpn-mul_fft.c
LIBPM_SRCS += mpn-toom33_mul.c
LIBPM_SRCS += mpn-toom_interpolate_16pts.c
LIBPM_SRCS += mpz-fits_sint.c
LIBPM_SRCS += mpz-tstbit.c
LIBPM_SRCS += mpn-mul_n.c
LIBPM_SRCS += mpn-toom3_sqr.c
LIBPM_SRCS += mpn-toom_interpolate_5pts.c
LIBPM_SRCS += mpz-fits_uint.c
LIBPM_SRCS += mpz-xor.c
LIBPM_SRCS += mpn-add.c
LIBPM_SRCS += mpn-mulmod_bnm1.c
LIBPM_SRCS += mpn-toom42_mul.c
LIBPM_SRCS += mpn-toom_interpolate_6pts.c
LIBPM_SRCS += mpz-get_si.c
LIBPM_SRCS += mpn-add_1.c
LIBPM_SRCS += mpn-nussbaumer_mul.c
LIBPM_SRCS += mpn-toom43_mul.c
LIBPM_SRCS += mpn-toom_interpolate_7pts.c
LIBPM_SRCS += mpz-get_str.c
LIBPM_SRCS += root-assert.c
LIBPM_SRCS += mpn-add_n.c
LIBPM_SRCS += mpn-pre_divrem_1.c
LIBPM_SRCS += mpn-toom44_mul.c
LIBPM_SRCS += mpn-toom_interpolate_8pts.c
LIBPM_SRCS += mpz-get_ui.c
LIBPM_SRCS += mpn-addmul_1.c
LIBPM_SRCS += mpn-rshift.c
LIBPM_SRCS += mpn-toom4_sqr.c
LIBPM_SRCS += mpz-abs.c
LIBPM_SRCS += mpz-init.c
LIBPM_SRCS += root-errno.c
LIBPM_SRCS += mpn-bdiv_dbm1c.c
LIBPM_SRCS += mpn-sbpi1_div_qr.c
LIBPM_SRCS += mpn-toom53_mul.c
LIBPM_SRCS += mpz-add.c
LIBPM_SRCS += mpz-ior.c
LIBPM_SRCS += root-memory.c
LIBPM_SRCS += mpn-cmp.c
LIBPM_SRCS += mpn-sbpi1_divappr_q.c
LIBPM_SRCS += mpn-toom63_mul.c
LIBPM_SRCS += mpz-add_ui.c
LIBPM_SRCS += mpz-mul.c
LIBPM_SRCS += root-mp_bpl.c
LIBPM_SRCS += mpn-dcpi1_div_qr.c
LIBPM_SRCS += mpn-set_str.c
LIBPM_SRCS += mpn-toom6_sqr.c
LIBPM_SRCS += mpz-and.c
LIBPM_SRCS += mpz-mul_2exp.c
LIBPM_SRCS += root-mp_clz_tab.c
LIBPM_SRCS += mpn-dive_1.c
LIBPM_SRCS += mpn-sqr.c
LIBPM_SRCS += mpn-toom6h_mul.c
LIBPM_SRCS += mpz-neg.c
LIBPM_SRCS += root-mp_dv_tab.c
LIBPM_SRCS += mpn-divrem_1.c
LIBPM_SRCS += mpn-sqr_basecase.c
LIBPM_SRCS += mpn-toom8_sqr.c
LIBPM_SRCS += mpz-cdiv_qr.c
LIBPM_SRCS += mpz-realloc.c
LIBPM_SRCS += root-mp_minv_tab.c
LIBPM_SRCS += mpn-divrem_2.c
LIBPM_SRCS += mpn-sqrmod_bnm1.c
LIBPM_SRCS += mpn-toom8h_mul.c
LIBPM_SRCS += mpz-cfdiv_q_2exp.c
LIBPM_SRCS += mpz-set.c
LIBPM_SRCS += root-tal-notreent.c
LIBPM_SRCS += mpn-get_str.c
LIBPM_SRCS += mpn-sub.c
LIBPM_SRCS += mpn-toom_couple_handling.c
LIBPM_SRCS += mpz-clear.c
LIBPM_SRCS += mpz-set_str.c
LIBPM_SRCS += mpz-mul_ui.c
LIBPM_SRCS += mpz-cmp_ui.c
LIBPM_SRCS += mpz-cmp_si.c
LIBPM_SRCS += mpz-fdiv_q_ui.c
LIBPM_SRCS += mpz-cdiv_q_ui.c

SRCS += $(LIBPM_SRCS)

# end of configuration...
########################################################
# compiler optimisation
CFLAGS_DEBUG = -O0 -g -Wall -fexceptions -Wno-deprecated -ansi -pedantic
CFLAGS_OPTIM = -DDO_NOT_GENERATE_CHECKINGS -O3 -funroll-loops -fomit-frame-pointer -fno-strict-aliasing -pipe -ffast-math -fexceptions
#-fstrength-reduce -frerun-loop-opt -fexpensive-optimizations -fschedule-insns2 


ifeq ($(strip $(OPTIM)),1)
	CFLAGS += $(CFLAGS_OPTIM)
	msg += "with optimizations "
else
	CFLAGS += $(CFLAGS_DEBUG)
	msg += "without optimizations "
endif
########################################################

OBJ_DIR = build

#OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
OBJ = $(foreach source,$(SRCS),$(OBJ_DIR)/$(source).o)
#DEPFILES = $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.dep))
DEPFILES = $(foreach source,$(SRCS),$(OBJ_DIR)/$(source).dep)

.PHONY: ALL
ALL: OBJ_DIR_CREATE $(EXEC)

########################################################

.PHONY: clean OBJ_DIR_CREATE
clean:
	@rm -rf $(OBJ_DIR) *~  $(EXTRA_FILES_CLEAN)

$(EXEC): $(OBJ) 
	@$(CXX) $(CFLAGS) -o $@ $(OBJ) 
	@echo linking.. $(EXEC)

# deps only on p2a related files (not with libpm).
$(OBJ_DIR)/%.cpp.o: %.cpp 
	@$(CXX) -MD -MF $(OBJ_DIR)/$<.dep -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(foreach sourceDir,$(SOURCES_DIR),$(eval -include $(OBJ_DIR)/${source}.dep))

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/bdd/%.cpp 
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/cache/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/collections/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/command_line_interface/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/files/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/hash_map_generator/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/streams/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/strings/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/time/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.cpp.o: $(LIBPM_PATH)/utilities/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.c.o: $(LIBPM_PATH)/gmp/%.c
	@gcc -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

OBJ_DIR_CREATE: 
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi;

#include dependancy files.
$(foreach source,$(SRCS),$(eval -include $(OBJ_DIR)/${source}.dep))

# vim:ft=make
