#!/usr/bin/python
import sys
sys.path.append("./samd21")
try:
    import samd21
except ImportError:
    print "simulator lib not generated"
    print "first run gadl:"
    print "$gadl ./samd21.cpu"
    print "Then go to the new samd21/ dir and build the python lib"
    print "$cd samd21"
    print "$make python"
    sys.exit()
    
sam = samd21.cpu()
core = sam.getCore(0)
core.readCodeFile('./boot.elf')
print core.disassemble(0x20000000,1,True);
core.printRegs()
