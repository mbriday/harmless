.text
.syntax unified
.thumb
.global _start
_start:
	USAT16 r1, #0,r1
	USAT16 r1, #0,r2
	USAT16 r1, #0,r6
	USAT16 r1, #6,r1
	USAT16 r1, #6,r2
	USAT16 r1, #6,r6
	USAT16 r1, #14,r1
	USAT16 r1, #14,r2
	USAT16 r1, #14,r6
	USAT16 r1, #15,r1
	USAT16 r1, #15,r2
	USAT16 r1, #15,r6
	USAT16 r5, #0,r1
	USAT16 r5, #0,r2
	USAT16 r5, #0,r6
	USAT16 r5, #6,r1
	USAT16 r5, #6,r2
	USAT16 r5, #6,r6
	USAT16 r5, #14,r1
	USAT16 r5, #14,r2
	USAT16 r5, #14,r6
	USAT16 r5, #15,r1
	USAT16 r5, #15,r2
	USAT16 r5, #15,r6
	USAT16 r9, #0,r1
	USAT16 r9, #0,r2
	USAT16 r9, #0,r6
	USAT16 r9, #6,r1
	USAT16 r9, #6,r2
	USAT16 r9, #6,r6
	USAT16 r9, #14,r1
	USAT16 r9, #14,r2
	USAT16 r9, #14,r6
	USAT16 r9, #15,r1
	USAT16 r9, #15,r2
	USAT16 r9, #15,r6
	b .
