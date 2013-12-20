#!/usr/bin/python
import sys
#
# PROJET : Task / Stack observation
#
# Test Stack Analysis on PPC Harmless simulator
# offer two examples
#
# WARNING : Stack obersation & safety is not avaible

# Looks in powerpc directory to find the processor arch
sys.path.append("../../powerpc")
from powerpc import arch
from powerpc	import stackSpyController

f=arch()
# LONELY TEST
# Loop test of task switch
#f.readCodeFile("./lonely_app/lonely_exe")

# BASIC TEST
# Three task lauch by the main task
f.readCodeFile("./basic_test_app/app_exe")

stackCtrl=f.getStackSpyController()

# LONELY
##stackCtrl.setExclusionOnSystFunction("tpl_put_preempted_proc"); 	# Not avaible on PPC
#stackCtrl.addTaskToMonitor("Task 1 Extended","extendedTask_function",500);
#stackCtrl.addTaskToMonitor("Task 2 Basic","basicTask_function",500);
#stackCtrl.addTaskToMonitor("Task 3 Master","masterTask_function",500);

# BASIC TEST
stackCtrl.addTaskToMonitor("Task 1","startTask_function",256);
stackCtrl.addTaskToMonitor("Task 2","secondTask_function",256);
stackCtrl.addTaskToMonitor("Task 3","thirdTask_function",256);
stackCtrl.addTaskToMonitor("Task 4","fourthTask_function",256);

print "-- Task switching analysis --"
f.execInst(10000000) #run until breakpoint

print ">> Task List"
stackCtrl.printTaskList();

print ">> Switch List"
stackCtrl.printControllerSwitchList()
stackCtrl.writeTraceT3("trace.txt");

