ENTRY(_Reset)
SECTIONS
{
 . = 0x10000;
 .text : {
 startup.s.o
 *(.text)
 }
 .data : { *(.data) *(.rodata)}
 .bss : { *(.bss) }
 . = . + 0x1000; /* 4kB of stack memory */
 stack_top = .;
}