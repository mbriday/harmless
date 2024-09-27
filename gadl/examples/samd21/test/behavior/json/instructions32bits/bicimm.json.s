.text
.syntax unified
.thumb
.global _start
_start:
	BIC r1, r0, #0 
	BIC r1, r7, #0 
	BIC r1, r0, #7 
	BIC r1, r7, #7 
	BIC r1, r0, #172 
	BIC r1, r7, #172 
	BIC r1, r0, #255 
	BIC r1, r7, #255 
	BIC r5, r0, #0 
	BIC r5, r7, #0 
	BIC r5, r0, #7 
	BIC r5, r7, #7 
	BIC r5, r0, #172 
	BIC r5, r7, #172 
	BIC r5, r0, #255 
	BIC r5, r7, #255 
	BIC r9, r0, #0 
	BIC r9, r7, #0 
	BIC r9, r0, #7 
	BIC r9, r7, #7 
	BIC r9, r0, #172 
	BIC r9, r7, #172 
	BIC r9, r0, #255 
	BIC r9, r7, #255 
	b .
