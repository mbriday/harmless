.text
.syntax unified
.thumb
.global _start
_start:
	SSAT16 r1, #1,r1
	SSAT16 r1, #1,r2
	SSAT16 r1, #1,r6
	SSAT16 r1, #5,r1
	SSAT16 r1, #5,r2
	SSAT16 r1, #5,r6
	SSAT16 r1, #16,r1
	SSAT16 r1, #16,r2
	SSAT16 r1, #16,r6
	SSAT16 r5, #1,r1
	SSAT16 r5, #1,r2
	SSAT16 r5, #1,r6
	SSAT16 r5, #5,r1
	SSAT16 r5, #5,r2
	SSAT16 r5, #5,r6
	SSAT16 r5, #16,r1
	SSAT16 r5, #16,r2
	SSAT16 r5, #16,r6
	SSAT16 r9, #1,r1
	SSAT16 r9, #1,r2
	SSAT16 r9, #1,r6
	SSAT16 r9, #5,r1
	SSAT16 r9, #5,r2
	SSAT16 r9, #5,r6
	SSAT16 r9, #16,r1
	SSAT16 r9, #16,r2
	SSAT16 r9, #16,r6
	b .
