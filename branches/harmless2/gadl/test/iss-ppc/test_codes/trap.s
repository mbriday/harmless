# % TRAP instructions test
# % inst: 100

.section  ".vectorPI","ax"

.globl main, PI_handler

PI_handler:
	addi 6,6,1
	nop
	nop
	rfi

.section .text
main:
	li 5,10
	twlt 6,5
	nop
	nop
	nop
	ba main

