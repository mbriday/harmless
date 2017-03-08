#!/usr/bin/python
# Usage : ./deasm.py <code_file> <number of instruction to disassemble>
# Disassemble the <number> first instruction of the given file.
# this file is called by test_syntax.sh
import sys

# Looks in powerpc directory to find the processor arch
sys.path.append("../samd21")
from samd21 import *

uc=cpu()
sam=uc.getCore(0)
sam.readCodeFile(sys.argv[1])
#sam.setProgramCounter(0x0)

print sam.disassemble(i*2, int(sys.argv[2]), True)

