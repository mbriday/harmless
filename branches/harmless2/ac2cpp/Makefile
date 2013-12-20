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

EXEC = ac2cpp
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
CFLAGS += -g #TODO: option à commenter quand debogage terminé
LDFLAGS +=
EXTRA_FILES_CLEAN=

#libpm related sources (these files are generated the firt time gadl is compiled).
LIBPM_PATH = ../gadl/galgas_sources/GALGAS_OUTPUT/libpm

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

INCLUDE_PATHS := -I$(LIBPM_PATH) $(patsubst %, -I%, $(SOURCES_DIR))

LIBPM_SRCS=C_BDD.cpp \
C_BDD-and-operation.cpp \
C_BDD-find-or-add.cpp \
C_BDD-single-operand-ops.cpp \
C_Display_BDD.cpp \
F_GetPrime.cpp \
C_ErrorOut.cpp \
C_String.cpp \
AC_OutputStream.cpp \
F_DisplayException.cpp \
C_ConsoleOut.cpp \
unicode_character_cpp.cpp \
unicode_string_routines.cpp \
MF_Assert.cpp \
basic-allocation.cpp \
MF_MemoryControl.cpp \
cpp-allocation.cpp \
C_PrologueEpilogue.cpp \
md5.cpp \
C_TextFileWrite.cpp \
C_SharedObject.cpp \
C_DateTime.cpp \
C_Timer.cpp \
F_mainForLIBPM.cpp \
C_FileManager.cpp \
C_Data.cpp \
AC_FileHandleForWriting.cpp \
AC_FileHandle.cpp \
C_BinaryFileWrite.cpp \
C_CommandLineOption.cpp \
F_Analyze_CLI_Options.cpp \
C_BoolCommandLineOption.cpp \
C_UIntCommandLineOption.cpp \
C_StringCommandLineOption.cpp \
C_builtin_CLI_Options.cpp \
C_ColoredConsole.cpp

SRCS += $(LIBPM_SRCS)

# end of configuration...
########################################################
# compiler optimisation
CFLAGS_DEBUG = -DDO_NOT_GENERATE_CHECKINGS -O0 -g -Wall -fexceptions -Wno-deprecated -ansi -pedantic
CFLAGS_OPTIM = -DDO_NOT_GENERATE_CHECKINGS -O0 -g -fstrength-reduce -frerun-loop-opt -fexpensive-optimizations -fschedule-insns2 -funroll-loops -fomit-frame-pointer -fno-strict-aliasing -pipe -ffast-math -fexceptions

ifeq ($(strip $(OPTIM)),1)
	CFLAGS += $(CFLAGS_OPTIM)
	msg += "with optimizations "
else
	CFLAGS += $(CFLAGS_DEBUG)
	msg += "without optimizations "
endif
########################################################

OBJ_DIR = .build

OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
DEPFILES = $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.dep))

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
$(OBJ_DIR)/%.o: %.cpp 
	@$(CXX) -MD -MF $(OBJ_DIR)/$<.dep -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(foreach sourceDir,$(SOURCES_DIR),$(eval -include $(OBJ_DIR)/${source}.dep))

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/bdd/%.cpp 
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/cache/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/collections/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/command_line_interface/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/files/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/hash_map_generator/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/streams/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/strings/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/time/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

$(OBJ_DIR)/%.o: $(LIBPM_PATH)/utilities/%.cpp
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo compiling $(msg)$< ...

OBJ_DIR_CREATE: 
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi;

#include dependancy files.
$(foreach source,$(SRCS),$(eval -include $(OBJ_DIR)/${source}.dep))

# vim:ft=make
