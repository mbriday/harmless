#!/usr/bin/python
#
# Generate the output of the Harmless simulator
# usage ./trace.py <code_file> <nb_inst>
# Execute the firsts nb_inst of code_file and generate output ready to be
# diff'ed.
#
# this script is called by test_behavior.py


import sys
import os

def get_info_string(f):
	string = ""
	for i in range(15):
		string += "%08x," % f.SRU_readR32(i)
	string += "%08x," % f.programCounter()
	string += "%08x" % f.CPSR()
	return string

def get_info_title():
	return "r0,...,r15,CPSR"


# Looks in arm irectory to find the processor arch
sys.path.append("../../arm_dbg")
sys.path.append("../arm_dbg")
from arm_dbg import arch

if len(sys.argv) != 3:
	print "Usage code_file nb_inst"
	os._exit(1)

f=arch()
f.SRU_CPSR_write32(0x13)             #cpsr init ot 0x13 (like gdb)
for i in range(16):
	f.SRU_writeR32(i,0)
f.SRU_writeR32(13,0x800) #sp init to 0x800
f.readCodeFile(sys.argv[1])

print get_info_string(f)
for i in range(int(sys.argv[2])):
	f.execInst(1)
	print get_info_string(f)

