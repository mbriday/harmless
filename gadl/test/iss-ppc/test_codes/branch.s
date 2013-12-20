# % Branch instructions test
# % inst: 100

.section .text
.globl main
main:
	li 5,10
	mtctr 5
my_loop:
	nop
	bdnz my_loop
	li 6,11
	cmpw 5,5,6
	bltl cr5,my_fct
	cmpw 5,6,5
	bltl cr5,my_fct
	ba _start

my_fct:
	addi 5,5,5
	blr


.section .data
mydata:
	.long 0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678
.section .bss 
	.space 40
SP:
	.long 0

