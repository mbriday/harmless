#!/usr/bin/python
# Usage : ./deasmOneInst.py <code_file> <instruction address>
#instruction address should be in hexa.
import sys
import os

scriptDir=os.path.abspath(os.path.dirname(sys.argv[0]))
sys.path.append(scriptDir+"/../../powerpc")
from powerpc import arch

f=arch()
f.readCodeFile(sys.argv[1])
print f.disassemble(int(sys.argv[2],16), 4, 0)
print "function", f.whichFunctionAtAddress(f.PC())

