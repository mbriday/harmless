.syntax unified
.thumb
.section .text

.global sc_handler
.type   sc_handler, %function

/*---------------------------------------------------------------------------*/
sc_handler:
	bx lr

.global _start
.type   _start, %function

_start:
	svc	#1
	b	.
	
