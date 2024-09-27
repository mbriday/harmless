.text
.syntax unified
.thumb
.global _start
_start:
	teq r0, #0 
	teq r2, #0 
	teq r7, #0 
	teq r0, #7 
	teq r2, #7 
	teq r7, #7 
	teq r0, #172 
	teq r2, #172 
	teq r7, #172 
	teq r0, #255 
	teq r2, #255 
	teq r7, #255 
	b .
