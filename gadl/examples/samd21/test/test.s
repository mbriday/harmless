.text
.syntax unified
.global _start
_start:
	rsb	r12, r0, r4, lsr #14
	pkhtb	r11, r1, r8, asr #13
	add.w	r5, r1, r10, lsl #23
    blx	0x4483d8						// opcode f003 e34e
	orns	r6, r0, #3065427638 		//=> opcode f070 36b6
