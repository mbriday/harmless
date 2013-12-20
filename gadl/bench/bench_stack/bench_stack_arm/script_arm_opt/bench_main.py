#!/usr/bin/python
## ARM BENCH TEST
## PROJECT : Stack / Task observation
## NAME : Stack analysis Benchmark script with automatic building
## DESCRIPTION :
## Automaticly build simulator with various option
## for each option it lauch a simulation script who executed all elf binary file in one folder
## using .stack file to configure automaticly

# Idee : lancer T3 directement a la fin de chaque simu

##############################
#     BENCH PARAMETERS       #
##############################

# PATH PARAMETERS TO BENCH
SIMULATOR_PATH="../../../../examples/arm/arm_opt/"		# Simulator folder
RESULT_PATH="bench_result.txt"		# Target for result file
EXECS_PATH="../bench_exec"			# ELF Binary .elf & .stack config files folder
NB_INSTR_SIMULATION=10000000		# How long simulation will execute
## !! MODEL NAME have to be udpated manually in two subfiles !!!
## from AT90CAN128 import arch
## update AT90CAN128 to your desire CPU
##############################

## IMPORT ##
## CONSOLE PRG LAUCHING ##
import sys,shlex,subprocess	# Execute makefile from within python script
#http://docs.python.org/library/subprocess.html
import ConfigParser
import glob
import os
import sys
import math

# SCRIPT PARAMETERS
## simulator_path 
#param=sys.argv
#if len(param)>=4 :

# Const parameters for lauching "bench_simulation_script.py"
OPT_NO_ACTION=" False False False"
OPT_ACTION_ONLY=" False False True"
OPT_TASK_MONITOR_ONLY=" True False True"
OPT_STACK_MONITOR=" True True True"

# Path writing
simPath=SIMULATOR_PATH
resPath=RESULT_PATH
exePath=EXECS_PATH

#########################
# MAIN SCRIPT FUNCTIONS #
#########################

## PATCHING SOURCES ##
def patchSources():
	command_line="sed \"s/sram_getChunk/mem_getChunk/g\" "+SIMULATOR_PATH+"stackObserver.cpp > "+SIMULATOR_PATH+"temp"
	args=shlex.split(command_line)
	p = subprocess.Popen(args,bufsize=-1,close_fds=True,shell=False)
	p.wait()	# Wait the end
	command_line="mv "+SIMULATOR_PATH+"temp "+SIMULATOR_PATH+"stackObserver.cpp"
	args=shlex.split(command_line)
	p = subprocess.Popen(args,bufsize=-1,close_fds=True,shell=False)
	p.wait()	# Wait the end

## AUTOMATIC COMPILATION
# IN : 
# - stringOptions : custom building option
def compileSimulator(stringOptions):
	# CLEAN
	command_line="make clean -C "+simPath
	args=shlex.split(command_line)
	p = subprocess.Popen(args,bufsize=-1,close_fds=True,shell=False)
	p.wait()	# Wait the end
	
	# BUILD
	print "!!! WARNING 4 CORE COMPILATION !!!"
	command_line="make -j1 -C "+simPath+" "+"DEFINES+=-DHOST_IS_LITTLE_ENDIAN  DEFINES+=-DUSE_LIBELF LIBELF=1 DEFINES+=-DHOST64 "+stringOptions
	args=shlex.split(command_line)
	p = subprocess.Popen(args,bufsize=-1,close_fds=True,shell=False)
	p.wait()	# Wait end of building

## CLEAN OF OLD PYTHON SCRIPT
# Maybe usefull to prevent any reuse of old simulator between two simulation
def cleanPyc():
	os.remove("bench_simulator.pyc")

## SIMULATION EXECUTION : call "bench_simulation_script.py"
# Recquire a separate script execution to allow reload of new simulator between 2 simulation
# IN
# - stringOptions : OPT_xxxxx const to control simulator parameters
def executeSimulator(stringOptions):
	# CLEAN
	command_line="./bench_simulation_script.py "+simPath+" "+resPath+" "+exePath+" "+str(NB_INSTR_SIMULATION)+" "+stringOptions
	args=shlex.split(command_line)
	p = subprocess.Popen(args,bufsize=-1,close_fds=True,shell=False)
	p.wait()	# Wait the end


#############################################
################ SCRIPT #####################
#############################################

# CLEAN RESULT FILE
resultFile = open(resPath,'w')
resultFile.close()

# PATCH SOURCES !!
patchSources()

# FIRST SIMULATION NO ACTION (FASTER)
compileSimulator("DEFINES+=-DGADL_NO_ACTION DEFINES-=-DUSE_INTERACTIVE_SIMULATION")
executeSimulator(OPT_NO_ACTION)
cleanPyc()

# FIRST SIMULATION ACTION ON ONLY (ACTION but no stack/task monitoring)
compileSimulator("DEFINES-=-DGADL_NO_ACTION DEFINES+=-DUSE_INTERACTIVE_SIMULATION")
executeSimulator(OPT_ACTION_ONLY)
cleanPyc()

# THIRD SIMULATION NO STACK USE MONITOR (use only stack scheduling)
compileSimulator("DEFINES-=-DGADL_NO_ACTION DEFINES+=-DUSE_INTERACTIVE_SIMULATION DEFINES+=-DGADL_SP_CHECK_ALLOWED DEFINES-=-DGADL_SP_FAILURE_CHECK_ALLOWED")
executeSimulator(OPT_TASK_MONITOR_ONLY)
cleanPyc()

# FOURTH SIMULATION ALL (all stack/taks monitoring functions)
compileSimulator("DEFINES-=-DGADL_NO_ACTION  DEFINES+=-DUSE_INTERACTIVE_SIMULATION DEFINES+=-DGADL_SP_CHECK_ALLOWED DEFINES+=-DGADL_SP_FAILURE_CHECK_ALLOWED")
executeSimulator(OPT_STACK_MONITOR)
cleanPyc()


########################################
######### % PER CALCULATION ############
########################################

# Configure a parser
benchCalculationParser = ConfigParser.ConfigParser()
# Read time data
benchCalculationParser.read(resPath)

# For all simulation read time and calculate %
for testFile in benchCalculationParser.sections():
	# Time Value reading
	stackMonitorTime=benchCalculationParser.getfloat(testFile, "StackMonitorTime")	
	taskMonitorTime=benchCalculationParser.getfloat(testFile, "TaskMonitorTime")	
	actionOnlyTime=benchCalculationParser.getfloat(testFile, "ActionOnlyTime")	
	noActionTime=benchCalculationParser.getfloat(testFile, "NoActionTime")	

	# File
	print
	print testFile

	# % value calating & writing
	perc=abs((stackMonitorTime-noActionTime)/noActionTime)*100.0
	print "StackMonitor/NoAction : ",perc
	benchCalculationParser.set(testFile,'%StackMonitorTime',perc)
	
	perc=abs((taskMonitorTime-noActionTime)/noActionTime)*100.0
	print "taskMonitorTime/NoAction : ",perc
	benchCalculationParser.set(testFile,'%TaskMonitorTime',perc)
	
	perc=abs((actionOnlyTime-noActionTime)/noActionTime)*100.0
	print "ActionOnlyTime/NoAction : ",perc
	benchCalculationParser.set(testFile,'%ActionOnlyTime',perc)
	
	perc=abs((noActionTime-noActionTime)/noActionTime)*100.0
	print "StackMonitorTime/NoAction : ",perc
	benchCalculationParser.set(testFile,'%NoActionTime',perc)


# Write result in file
resultFile = open(resPath,'w')
benchCalculationParser.write(resultFile)
resultFile.close()


