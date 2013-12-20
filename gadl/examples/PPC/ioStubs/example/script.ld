/*
 * custom PPC LD script
 *
 * Allow to build static executable that run on PPC without any OS
 *
 * In order to use the SystemCall or the Program Interrupt, the handlers of
 * these exceptions have to be in dedicated sections:
 * ".vectorPI" for the ProgramInterrupt handler
 * ".vectorSC" for the SystemCall handler
 *
 * export the _init_sp symbol which is the summit of the stack at startup
 * SP should be set to this value in _start
 */

STACK_SIZE = 10M;

ENTRY(_start)

MEMORY
{
    IT_sect (ax) : org = 0, l = 0x3000
	ram (wax) : org = 0x3000, l = 20M /* Make sure that this memory can contain the code, dat and the stack */
}

SECTIONS
{
	. = ALIGN(4);
	.text  : { *(.text) *(.rodata) } > ram
	. = ALIGN(4);
	.data  : { *(.sdata) *(.data) } > ram
	. = ALIGN(4);
    .bss : {
      __bss_start__ = . ;
      *(.bss)
      *(COMMON)
      . = ALIGN(4);
      __bss_end__ = . ;
    } > ram
    end = .;
	
	. += STACK_SIZE; /* Stack alocation */
	. = ALIGN(4) - 4;
	_init_sp = . ; /* the _init_sp symbol point on the summit of the stack */

	.vector 0x700 : { *(.vectorPI ) }> IT_sect
	.vector 0xC00 : { *(.vectorSC ) }> IT_sect
}

