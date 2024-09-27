.text
.syntax unified
.thumb
.global _start
_start:
	CMN r0, #0 
	CMN r2, #0 
	CMN r7, #0 
	CMN r0, #7 
	CMN r2, #7 
	CMN r7, #7 
	CMN r0, #172 
	CMN r2, #172 
	CMN r7, #172 
	CMN r0, #255 
	CMN r2, #255 
	CMN r7, #255 
	b .
