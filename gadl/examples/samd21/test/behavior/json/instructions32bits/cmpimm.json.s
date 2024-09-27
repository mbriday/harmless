.text
.syntax unified
.thumb
.global _start
_start:
	CMP.W r0, #0 
	CMP.W r2, #0 
	CMP.W r7, #0 
	CMP.W r0, #7 
	CMP.W r2, #7 
	CMP.W r7, #7 
	CMP.W r0, #172 
	CMP.W r2, #172 
	CMP.W r7, #172 
	CMP.W r0, #255 
	CMP.W r2, #255 
	CMP.W r7, #255 
	b .
