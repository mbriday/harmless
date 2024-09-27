.text
.syntax unified
.thumb
.global _start
_start:
	SBC r0, r0, #0 
	SBC r0, r2, #0 
	SBC r0, r7, #0 
	SBC r0, r0, #7 
	SBC r0, r2, #7 
	SBC r0, r7, #7 
	SBC r0, r0, #172 
	SBC r0, r2, #172 
	SBC r0, r7, #172 
	SBC r0, r0, #255 
	SBC r0, r2, #255 
	SBC r0, r7, #255 
	SBC r7, r0, #0 
	SBC r7, r2, #0 
	SBC r7, r7, #0 
	SBC r7, r0, #7 
	SBC r7, r2, #7 
	SBC r7, r7, #7 
	SBC r7, r0, #172 
	SBC r7, r2, #172 
	SBC r7, r7, #172 
	SBC r7, r0, #255 
	SBC r7, r2, #255 
	SBC r7, r7, #255 
	SBC r14, r0, #0 
	SBC r14, r2, #0 
	SBC r14, r7, #0 
	SBC r14, r0, #7 
	SBC r14, r2, #7 
	SBC r14, r7, #7 
	SBC r14, r0, #172 
	SBC r14, r2, #172 
	SBC r14, r7, #172 
	SBC r14, r0, #255 
	SBC r14, r2, #255 
	SBC r14, r7, #255 
	b .
