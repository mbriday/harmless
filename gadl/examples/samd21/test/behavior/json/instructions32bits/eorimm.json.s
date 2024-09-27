.text
.syntax unified
.thumb
.global _start
_start:
	eor r1, r0, #0 
	eor r1, r2, #0 
	eor r1, r7, #0 
	eor r1, r0, #7 
	eor r1, r2, #7 
	eor r1, r7, #7 
	eor r1, r0, #172 
	eor r1, r2, #172 
	eor r1, r7, #172 
	eor r1, r0, #255 
	eor r1, r2, #255 
	eor r1, r7, #255 
	eor r5, r0, #0 
	eor r5, r2, #0 
	eor r5, r7, #0 
	eor r5, r0, #7 
	eor r5, r2, #7 
	eor r5, r7, #7 
	eor r5, r0, #172 
	eor r5, r2, #172 
	eor r5, r7, #172 
	eor r5, r0, #255 
	eor r5, r2, #255 
	eor r5, r7, #255 
	eor r9, r0, #0 
	eor r9, r2, #0 
	eor r9, r7, #0 
	eor r9, r0, #7 
	eor r9, r2, #7 
	eor r9, r7, #7 
	eor r9, r0, #172 
	eor r9, r2, #172 
	eor r9, r7, #172 
	eor r9, r0, #255 
	eor r9, r2, #255 
	eor r9, r7, #255 
	b .
