.text
.syntax unified
.thumb
.global _start
_start:
	orn.w r1, r0, #0 
	orn.w r1, r7, #0 
	orn.w r1, r0, #7 
	orn.w r1, r7, #7 
	orn.w r1, r0, #172 
	orn.w r1, r7, #172 
	orn.w r1, r0, #255 
	orn.w r1, r7, #255 
	orn.w r5, r0, #0 
	orn.w r5, r7, #0 
	orn.w r5, r0, #7 
	orn.w r5, r7, #7 
	orn.w r5, r0, #172 
	orn.w r5, r7, #172 
	orn.w r5, r0, #255 
	orn.w r5, r7, #255 
	orn.w r9, r0, #0 
	orn.w r9, r7, #0 
	orn.w r9, r0, #7 
	orn.w r9, r7, #7 
	orn.w r9, r0, #172 
	orn.w r9, r7, #172 
	orn.w r9, r0, #255 
	orn.w r9, r7, #255 
	b .
