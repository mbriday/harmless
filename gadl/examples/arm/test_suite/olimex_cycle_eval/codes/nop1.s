@########
@ NOP+1 #
@########


.PORT0:
	.word  0xE0028000 @base port 0
@PORT0: IOPIN@0, IOSET@4 IODIR@8 IOCLR@C

.globl main
main :
	bl configP09
restart:
	bl toggleP09
	mov r0, #0xF0000
boucle :
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop 
	subs r0, r0, #0x1
	bne boucle
	b restart
	
configP09:
	ldr r0, .PORT0
	ldr r1, [r0, #8]
	orr r1, r1, #0x200 @set P0.9 to output.
	str r1, [r0, #8]
	mov pc, lr


toggleP09:
	ldr r0, .PORT0
	mov r2, #0x200 @
	ldr r1, [r0, #0] @read P0.	
	ands r1, r1, #0x200 @ get back only P09 and update status (z)
	strne r2, [r0, #0xc]  @clear P0.9
	streq r2, [r0, #4]	@set   P0.9
	mov pc, lr
