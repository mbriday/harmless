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

def traceHarmless(sim,elf,inst,outputFileH):
	output = open(outputFileH, "w")
	
	f=sim.arch()
	f.SRU_CPSR_write32(0x13)             #cpsr init ot 0x13 (like gdb)
	for i in range(16):
		f.SRU_writeR32(i,0)
	f.SRU_writeR32(13,0x800) #sp init to 0x800
	f.readCodeFile(elf)
	
	output.write(get_info_string(f)+"\n")
	for i in range(inst):
		f.execInst(1)
		output.write(get_info_string(f)+"\n")
	output.close()
