#!/usr/bin/python

## PROJECT : Stack / Task observation
## NAME : Automatic simulation script for elf folder (with timing analysis)
## DESCRIPTION :
## Simulation script executed all elf binary file in one folder
## using .stack file to configure automaticly
## Timing of simulation is write in a result file
##
## Input Script PARAMETERS ##
## All parameters are required (no parser/ no disctionnary)
## TODO : real parameters with -t options
##
## ALL OPTION (number and order have to be respected)
## simulator_path (string path folder)
## result_path (string path file)
## exePath (string path folder)
## nb_instruction_simulation (string -> number)
## bool_taskMonitorMode (string False/True)
## bool_stackMonitorMode (string False/True)
## bool_actionOn (string False/True)

# IMPORT
import os
import sys
import bench_simulator
import ConfigParser
import string
import re

### FUNCTIONS ###

## FILE EXTENSION ##
# Returns the extension of the given filename
def file_ext(fn):
	return fn[fn.rfind(".")+1:len(fn)]
## FILE NAME
def file_name(fn):
	return fn[0:fn.rfind(".")]
	
#NB_INSTR_ELF_FILE=1000000000
NB_INSTR_ELF_FILE=1000000 # DEFAULT VALUE OVERIDE BY SCRIPT PARAMETERS
M_MODEL_NAME="arm_opt" # COULD NOT BE APPLY --> TO DO : correct it
					# l.32 & 38 bench_simulator.py have to be change

# Default parameters
nbInstrSimulation=NB_INSTR_ELF_FILE
modelName=M_MODEL_NAME

# Read parameters
param=sys.argv

if len(param)>=7 :
	######################
	# PARAMETERS READING #
	######################
	# PARAM Simulator Path
	simPath=param[1]
	# PARAM Results Path
	resPath=param[2]
	# PARAM Executable Path
	exePath=param[3]
	# PARAM Nb instruction simulation
	nbInstrSimulation=int(param[4])
	# PARAM Task Monitoring
	if param[5]=="True" :
		boolTaskMonitor=True
	elif  param[5]=="False":
		boolTaskMonitor=False
	else :
		boolTaskMonitor=False
	
	# PARAM Stack Monitoring
	if param[6]=="True" :
		boolStackMonitor=True
	elif param[6]=="False":
		boolStackMonitor=False
	else :
		boolStackMonitor=False
	
	# PARAM Action
	if param[7]=="True" :
		boolActionOn=True
	elif param[7]=="False" :
		boolActionOn=False
	else :
		boolActionOn=False
	
    ##########################################################
	# SIMULATOR EXECUTION (Execute for ALL elf in directory) #
	##########################################################
	test_files = os.listdir(exePath)	# Read list of files in folder
	test_files.sort()					# Sort file list
	
	# Info
	print "Simulation of ",M_MODEL_NAME,"modele name have to be change l.32 & 38 in bench_simulator.py"
	
	# For all executable simulate and get time
	for test_file in test_files:
		#if file_ext(test_path) == "elf":
		if file_ext(test_file)=="elf" :
			execName=test_file
			configName=file_name(execName)+".stack"
			execPath=exePath+"/"+execName
			configPath=exePath+"/"+configName
			print execPath
			sim=bench_simulator.Simulator(simPath,execPath,modelName,nbInstrSimulation,boolTaskMonitor,boolStackMonitor)
			sim.configureStackFromFile(configPath)
			t=sim.executeSimulation()
			
			# DEBUG
			#sim.printResults()
		
			# FILE RESULT WRITING
			
			# Configure Parser
			Config = ConfigParser.ConfigParser()
			Config.read(resPath)
			
			# No bench done for this file
			if not(Config.has_section(configName)) :
				print "HAS NO SECTION"
				Config.add_section(configName)	# Section is name with executable name
			
			# Store result
			if boolStackMonitor and boolTaskMonitor :
				Config.set(configName,'StackMonitorTime',t)
			elif boolTaskMonitor :
				Config.set(configName,'TaskMonitorTime',t)
			elif boolActionOn :
				Config.set(configName,'ActionOnlyTime',t)
			else :
				Config.set(configName,'NoActionTime',t)
			
			# Write result in file
			resultFile = open(resPath,'w')
			Config.write(resultFile)
			resultFile.close()
			
			# OUTPUT
			print "Time of execution :",t,"s"
	
# FAIL
else :
	print "Warning : more args recquired"





