#!/usr/bin/python
import sys

# Looks in AT90CAN128 directory to find the processor arch
sys.path.append("./AT90CAN128")
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

f=arch()
f.readCodeFile("./trampoline.elf")
f.addBreakpoint("function_of_task_startTask")
nbInst = 0
f.printRegs()
#disassemble one instruction.
print f.disassemble(f.programCounter(),1,True)
for i in range(20):
	f.execInst(100000) #run until breakpoint
	print "current function: ",	f.whichFunctionAtAddress(f.programCounter())
	print f.getNBInstructions() - nbInst,  " instructions between 2 breakpoints"
	nbInst = f.getNBInstructions()
f.printRegs()
f.decoderStats()
print "nb cycles : ", f.getNBCycles()
