#!/usr/bin/python
#
# Generate the output of the Harmless simulator
# usage ./trace.py <code_file> <nb_inst>
# Execute the first nb_inst of code_file and generate output ready to be
# diff'ed.
#
# this script is called by test_behavior.py


import sys
import os

def get_info_string(f):
	string = "%04x," % f.programCounter()
	for i in range(32):
		string += "%02x," % f.sram_ram_read8(i)
	string += "%02x," % f.CCR()
	string += "%08x" % (f.SP()+0x800000) #gdb give a value > 16 bits?!
	return string

def get_info_title():
	return "PC,r0,...,r31,SREG, SP"


# Looks in AT90CAN128 directory to find the processor arch
sys.path.append("../AT90CAN128")
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


if len(sys.argv) != 3:
	print "Usage code_file nb_inst"
	os._exit(1)


f=arch()
if not f.readCodeFile(sys.argv[1]):
	sys.exit()
f.setCCR(0)
f.setSP(0)
for i in range(32):
	f.sram_ram_write8(i,0)

#print get_info_title()

print get_info_string(f)


for i in range(int(sys.argv[2])):
#	PC = f.programCounter()
#	print f.disassemble(PC,4,0)
	f.execInst(1)
	print get_info_string(f)

