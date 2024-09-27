.text
.syntax unified
.thumb
.global _start
_start:
	mvn.w r1, #0 
	mvn.w r1, #7 
	mvn.w r1, #172 
	mvn.w r1, #255 
	mvn.w r5, #0 
	mvn.w r5, #7 
	mvn.w r5, #172 
	mvn.w r5, #255 
	mvn.w r9, #0 
	mvn.w r9, #7 
	mvn.w r9, #172 
	mvn.w r9, #255 
	b .
