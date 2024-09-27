.text
.syntax unified
.thumb
.global _start
_start:
	orr r1, r0, #0 
	orr r1, r2, #0 
	orr r1, r7, #0 
	orr r1, r0, #7 
	orr r1, r2, #7 
	orr r1, r7, #7 
	orr r1, r0, #172 
	orr r1, r2, #172 
	orr r1, r7, #172 
	orr r1, r0, #255 
	orr r1, r2, #255 
	orr r1, r7, #255 
	orr r5, r0, #0 
	orr r5, r2, #0 
	orr r5, r7, #0 
	orr r5, r0, #7 
	orr r5, r2, #7 
	orr r5, r7, #7 
	orr r5, r0, #172 
	orr r5, r2, #172 
	orr r5, r7, #172 
	orr r5, r0, #255 
	orr r5, r2, #255 
	orr r5, r7, #255 
	orr r9, r0, #0 
	orr r9, r2, #0 
	orr r9, r7, #0 
	orr r9, r0, #7 
	orr r9, r2, #7 
	orr r9, r7, #7 
	orr r9, r0, #172 
	orr r9, r2, #172 
	orr r9, r7, #172 
	orr r9, r0, #255 
	orr r9, r2, #255 
	orr r9, r7, #255 
	b .
