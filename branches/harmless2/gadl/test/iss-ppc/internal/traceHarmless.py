#!/usr/bin/python
#
# Generate the output of the Harmless simulator
# usage ./trace.py <code_file> <nb_inst>
# Execute the fisrts nb_inst of code_file and generate output ready to be
# diff'ed.
#
# this script is called by test_behavior.py


import sys
import os

def get_info_string(f):
	string = "%08x," % f.programCounter()
	for i in range(32):
		string += "%08x," % f.reg_read32(i)
	string += "%08x," % f.XER()
	string += "%08x," % f.CR()
	string += "%08x," % f.CTR()
	string += "%08x," % f.LR()
	string += "%08x" % f.MSR()
	return string

def get_info_title():
	return "PC,r0,...,r31,XER,CR,CTR,LR,MSR"

def traceHarmless(sim,elf,inst,outputFileH):
	f=sim.core()
	f.readCodeFile(elf)
	f.setExecutionMode(sim.core.ISS)
	f.setCR(0)
	f.setCTR(0)
	f.setLR(0)
	f.setXER(0)
	f.setMSR(0x2002)
	f.setSRR0(0)
	f.setSRR1(0)
	for i in range(32):
		f.reg_write32(i,0)
	
	output = open(outputFileH, "w")
	output.write(get_info_string(f)+"\n")

	for i in range(inst):
		f.execInst(1)
	
		# If the previous instruction is a System call or a succesful trap, execute
		# the next instruction without printing it. This is made to match behavior
		# of PSIM
		if f.programCounter()== 0xC00 or f.programCounter() == 0x700 :
			f.execInst(1)
		output.write(get_info_string(f)+"\n")
	
	output.close()
