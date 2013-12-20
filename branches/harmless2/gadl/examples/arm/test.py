#!/usr/bin/python
import sys

# Looks in AT90CAN128 directory to find the processor arch
sys.path.append("./arm_dbg")
from arm_dbg import arch

f=arch()
f.readCodeFile("./test_suite/mibench/internal/bin/basicMathSmall.elf")
f.addBreakpoint("main")
f.execInst(10000000) #run until breakpoint
nbInst = 0
for i in range(20):
	print f.disassemble(f.PC(),1,1)
	f.execInst(1) #run until breakpoint
#	print f.SRU_GPR_read32(0) #print register R0
f.decoderStats()
print "nb cycles : ", f.getNBCycles()
