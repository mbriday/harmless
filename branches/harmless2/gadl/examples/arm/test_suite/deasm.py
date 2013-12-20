#!/usr/bin/python
import sys

sys.path.append("../arm_dbg")
from arm_dbg import arch

f=arch()
f.readCodeFile(sys.argv[1])
#start = 0x00003000
#start = f.programCounter()
#f.setProgramCounter(start)

for i in range(int(sys.argv[2])):
	pc = start+i*4
	mnemo = f.disassemble(pc, 4, 0)
	print "%8x: %08x  %s" % (pc, f.mem_read32(pc), mnemo)

