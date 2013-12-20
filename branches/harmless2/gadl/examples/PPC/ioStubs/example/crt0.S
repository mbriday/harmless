# crt0.S

# Startup file
# initialize the stack Pointer with information provided by the linker
# Should be compiled (with 'as') and linked with any program aimed to run on Harmles PowerPC
# simulator

.text
.globl _start
_start:
	lis 2,__bss_start__@h
	ori 2,2,__bss_start__@l
	lis 3,__bss_end__@h
	ori 3,3,__bss_end__@l
	li  4,0	/* value */
	b _start_bss_clear_loop
_bss_clear_loop:
	addi 2, 2, 4
	stw  4, 0(2)
_start_bss_clear_loop:
	cmpw  cr7,2, 3
	bne+  cr7,_bss_clear_loop
	li  2, 0  /* reset r2 */
	

/* init stack pointer */
	lis 1,_init_sp@h
	ori 1,1,_init_sp@l

/* call main */
	li  3, 0  /* No arguments */
	li  4, 0  /* No arguments */
	ba main
shouldNotHappen:
	b shouldNotHappen

