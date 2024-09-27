.text
.syntax unified
.thumb
.global _start
_start:
	RSB.W r0, r0, #0 
	RSB.W r0, r2, #0 
	RSB.W r0, r7, #0 
	RSB.W r0, r0, #7 
	RSB.W r0, r2, #7 
	RSB.W r0, r7, #7 
	RSB.W r0, r0, #172 
	RSB.W r0, r2, #172 
	RSB.W r0, r7, #172 
	RSB.W r0, r0, #255 
	RSB.W r0, r2, #255 
	RSB.W r0, r7, #255 
	RSB.W r7, r0, #0 
	RSB.W r7, r2, #0 
	RSB.W r7, r7, #0 
	RSB.W r7, r0, #7 
	RSB.W r7, r2, #7 
	RSB.W r7, r7, #7 
	RSB.W r7, r0, #172 
	RSB.W r7, r2, #172 
	RSB.W r7, r7, #172 
	RSB.W r7, r0, #255 
	RSB.W r7, r2, #255 
	RSB.W r7, r7, #255 
	RSB.W r14, r0, #0 
	RSB.W r14, r2, #0 
	RSB.W r14, r7, #0 
	RSB.W r14, r0, #7 
	RSB.W r14, r2, #7 
	RSB.W r14, r7, #7 
	RSB.W r14, r0, #172 
	RSB.W r14, r2, #172 
	RSB.W r14, r7, #172 
	RSB.W r14, r0, #255 
	RSB.W r14, r2, #255 
	RSB.W r14, r7, #255 
	b .
