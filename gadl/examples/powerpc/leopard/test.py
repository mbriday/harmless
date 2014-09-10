#!/opt/local/bin/python2.7
import sys

# Looks in leopard directory to find the processor arch
sys.path.append("./leopard")
try:
	from leopard import cpu
except ImportError:
	print "the leopard simulator does not seem to be generated."
	print "try to compile it using gadl "
	print "then update if necessary the Makefile in the generated"
	print "directory (leopard) and compile the simulator using:"
	print "make python"
	print "Swig and libelf should be installed, see documentation."
	sys.exit()

sim=cpu()
core0=sim.getCore(0)
core0.readCodeFile("./serial.elf")
sim.run(1000)
core0.printRegs()
core0.decoderStats()
