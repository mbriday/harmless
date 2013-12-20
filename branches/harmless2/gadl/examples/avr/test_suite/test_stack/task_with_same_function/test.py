#!/usr/bin/python
import sys

# PROJECT : Task / Stack observation
# TEST : test task scheduling detection when to task share same main function
# DESCRIPTION :
# Task 2, 3 and 4 share the same main function : functionOfBothTask
# Stack observation is abble to correctly work in this case this test verify it

#avr-objdump -d AVRTrampolineBinTest1 > temp.txt
# Looks in AT90CAN128 directory to find the processor arch
#sys.path.append("./avr_simulator_stack_check")
sys.path.append("../../../AT90CAN128")
try:
	from AT90CAN128 import arch
except ImportError:
	print "the avr simulator does not seem to be generated."
	print "try to compile it using gadl (gadl ./avr.hadl)"
	print "then update if necessary the Makefile in the generated"
	print "directory (AT90CAN128) and compile the simulator using:"
	print "make python"
	print "Swig and libelf should be installed, see documentation."
	sys.exit()
try:
	from AT90CAN128	import stackSpyController
except ImportError:
	print "the avr simulator does not seem to support stack/task monitoring."
	print "You should recompile the simulator, using the following build options (Makefile)"
	print "DEFINES += -DGADL_SP_CHECK_ALLOWED"
	print "DEFINES += -DGADL_SP_FAILURE_CHECK_ALLOWED"
	sys.exit()

f=arch()
f.readCodeFile("./task_same_function")

stackCtrl=f.getStackSpyController()

stackCtrl.setExclusionOnSystFunction("tpl_put_preempted_proc");
stackCtrl.addTaskToMonitor("Task 1","startTask_function",250);
#stackCtrl.addTaskToMonitor("Task 2","secondTask_function",250);
#stackCtrl.addTaskToMonitor("Task 3","thirdTask_function",250);
#stackCtrl.addTaskToMonitor("Task 4","fourthTask_function",250);
#stackCtrl.addTaskToMonitor("Task 5","eventTask_function",250);
stackCtrl.addTaskToMonitor("Task 2","functionOfBothTask",250);
stackCtrl.addTaskToMonitor("Task 3","functionOfBothTask",250);
stackCtrl.addTaskToMonitor("Task 4","functionOfBothTask",250);

print "-- Task / Stack Observation --"
f.execInst(10000000) #run until breakpoint

print ">> Task List"
stackCtrl.printTaskList();

print ">> Switch List"
stackCtrl.printControllerSwitchList()
stackCtrl.writeTraceT3("trace.txt");
