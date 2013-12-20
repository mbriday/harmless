#!/usr/bin/python
#
# Execute code until string is print on UART0
# usage ./trace.py <code_file> [nb_inst_max [<breakpoint_name>]]
# breakpoint_name can be a label or an hexa address


import sys
import os

# Looks in arm directory to find the processor arch
sys.path.append("../../arm_dbg")
sys.path.append("../arm_dbg")
from arm_dbg import arch

i_max = 40000000000 # default value for nb_inst_max

if len(sys.argv) < 2:
	print "Usage code_file [nb_inst_max [<breakpoint_name>]]"
	os._exit(1)
	
if len(sys.argv) >= 3:
	i_max = int(sys.argv[2])
	
#initialisation
f=arch()
f.SRU_CPSR_write32(0x13)             #cpsr init ot 0x13 (like qemu)
for i in range(16):
	f.SRU_writeR32(i,0)
f.SRU_writeR32(13,0x800) #sp init to 0x800
f.readCodeFile(sys.argv[1])

#if len(sys.argv) == 4 :
#	# add breakpoint, 2 formats : 0x__ and a label
#	if(sys.argv[3][:2] == "0x") :
#		f.addBreakpoint(int(sys.argv[3], 16))
#	else :
#		f.addBreakpoint(sys.argv[3])
	
f.runUntil(int(sys.argv[3], 16), i_max);
print "PC : %08x" % f.programCounter()
print "nb : %d" % f.getNBInstructions()