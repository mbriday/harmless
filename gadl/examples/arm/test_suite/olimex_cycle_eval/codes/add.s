@######
@ ADD #
@######

.globl main
main :
	mov r0, #0xF000000
	b boucle
boucle :
	nop
	nop
	nop
	nop
	add r1, r2, r3
	nop
	nop
	nop
	nop
	nop
	nop 
	subs r0, r0, #0x1
	bne boucle
	b _end
	
_end:
	b .
	