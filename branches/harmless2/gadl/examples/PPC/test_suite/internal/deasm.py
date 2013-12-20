#!/usr/bin/python
# Usage : ./deasm.py <code_file> <number of instruction to disassemble>
# Disassemble the <number> first instruction of the given file.
# this file is called by test_syntax.sh
import sys

# Looks in powerpc directory to find the processor arch
sys.path.append("../../powerpc")
from powerpc import arch

f=arch()
f.readCodeFile(sys.argv[1])
f.setProgramCounter(0x0)

for i in range(int(sys.argv[2])/4):
	print f.disassemble(i*4, 4, 0)

