ENTRY(_entryPoint)
SECTIONS
{
 . = 0x10000;
 .text : {
 crt0.s.o
 *(.text)
 }
 .data : { *(.data) *(.rodata)}
 .bss : { *(.bss) }
 . = . + 0x1000; /* 4kB of stack memory */
 stack_top = .;
 PROVIDE(__HEAP_START = stack_top );
}
