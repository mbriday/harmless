#!/usr/bin/python
# -*- coding: latin1 -*-

# if not working:
# export PYTHONPATH=$PYTHONPATH:`pwd`/hc12
import hc12

def printHC12Regs(f):
	print "A :  %02x B :  %02x D:%04x CCR:  %02x" % (f.A(), f.B(), f.D(), f.CCR());
	print "PC:%04x SP:%04x X:%04x Y  :%04x" % (f.PC(), f.SP(), f.X(), f.Y());

f=hc12.arch()
f.readCodeFile("./fibo.sr")
f.setProgramCounter(0xC03B)
i = 0
while i < 10:
	print "******* instruction %4d ********" % (i);
	f.execInst(1)
	printHC12Regs(f)
	i = i+1
f.decoderStats()
