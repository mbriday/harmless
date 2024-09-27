.text
.syntax unified
.thumb
.global _start
_start:
	TST r0, #0 
	TST r2, #0 
	TST r7, #0 
	TST r0, #7 
	TST r2, #7 
	TST r7, #7 
	TST r0, #172 
	TST r2, #172 
	TST r7, #172 
	TST r0, #255 
	TST r2, #255 
	TST r7, #255 
	b .
