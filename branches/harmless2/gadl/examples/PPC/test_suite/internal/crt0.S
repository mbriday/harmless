# crt0.S

# Startup file
# initialize the stack Pointer with information provided by the linker
# Should be compiled (with 'as') and linked with any program aimed to run on Harmless PowerPC
# simulator

.text
.globl _start
_start:
	lis 1,_init_sp@h
	ori 1,1,_init_sp@l
	bl main
shouldNotHappen:
	b shouldNotHappen
