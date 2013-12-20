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
	string = ""
	#r0-12, sp_usr, lr_usr
	for i in range(15):
		string += "%08X," % f.SRU_GPR_read32(i)
	#pc
	string += "%08X," % f.programCounter()
 	#r8_fiq
 	string += "%08X," % f.SRU_GPR_read32(16)
	#r9_fiq
	string += "%08X," % f.SRU_GPR_read32(17)
	#r10_fiq
	string += "%08X," % f.SRU_GPR_read32(18)
	#r11_fiq
	string += "%08X," % f.SRU_GPR_read32(19)
	#r12_fiq
	string += "%08X," % f.SRU_GPR_read32(20)
	#sp_fiq
	string += "%08X," % f.SRU_GPR_read32(21)
	#lr_fiq
	string += "%08X," % f.SRU_GPR_read32(22)
	#sp_irq
	string += "%08X," % f.SRU_GPR_read32(24)
	#lr_irq
	string += "%08X," % f.SRU_GPR_read32(25)
	#sp_svc
	string += "%08X," % f.SRU_GPR_read32(27)
	#lr_svc
	string += "%08X," % f.SRU_GPR_read32(28)
	#sp_abt
	string += "%08X," % f.SRU_GPR_read32(33)
	#lr_abt
	string += "%08X," % f.SRU_GPR_read32(34)
	#sp_und
	string += "%08X," % f.SRU_GPR_read32(30)
	#lr_und
	string += "%08X," % f.SRU_GPR_read32(31)
	#cpsr
	string += "%08X," % f.CPSR()	
	#spsr_fiq
	string += "%08X," % f.SPSR_FIQ()
	#spsr_irq
	string += "%08X," % f.SPSR_IRQ()
	#spsr_svc
	string += "%08X," % f.SPSR_SVC()
	#spsr_abt
	string += "%08X," % f.SPSR_ABT()
	#spsr_und
	string += "%08X," % f.SPSR_UNDEF()

	return string

# Looks in arm irectory to find the processor arch
sys.path.append("../../arm_dbg")
sys.path.append("../arm_dbg")
from arm_dbg import arch

if len(sys.argv) != 3:
	print "Usage code_file nb_inst"
	os._exit(1)

f=arch()
f.SRU_CPSR_write32(0x800000df)             #cpsr init ot 0x13 (like gdb)
for i in range(34):
	f.SRU_writeR32(i,0)
f.setSPSR_FIQ(0x10)
f.setSPSR_IRQ(0x10)
f.setSPSR_SVC(0x10)
f.setSPSR_ABT(0x10)
f.setSPSR_UNDEF(0x10)

	
f.readCodeFile(sys.argv[1])

print get_info_string(f)

for i in range(int(sys.argv[2])):
	f.execInst(1)
	print get_info_string(f)

