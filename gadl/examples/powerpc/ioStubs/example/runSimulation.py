#!/usr/bin/python
import sys

# Looks in arm_dbg directory to find the processor arch
sys.path.append("../../powerpc")
from powerpc import arch

f=arch()
f.readCodeFile("./exe")
f.useIOStubs()
f.execInst(100000)

