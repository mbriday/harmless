.text
.syntax unified
.thumb
.global _start
_start:
	BFC r1, #0, #1 
	BFC r1, #5, #1 
	BFC r1, #11, #1 
	BFC r1, #0, #9 
	BFC r1, #5, #9 
	BFC r1, #11, #9 
	BFC r1, #0, #17 
	BFC r1, #5, #17 
	BFC r1, #11, #17 
	BFC r5, #0, #1 
	BFC r5, #5, #1 
	BFC r5, #11, #1 
	BFC r5, #0, #9 
	BFC r5, #5, #9 
	BFC r5, #11, #9 
	BFC r5, #0, #17 
	BFC r5, #5, #17 
	BFC r5, #11, #17 
	BFC r9, #0, #1 
	BFC r9, #5, #1 
	BFC r9, #11, #1 
	BFC r9, #0, #9 
	BFC r9, #5, #9 
	BFC r9, #11, #9 
	BFC r9, #0, #17 
	BFC r9, #5, #17 
	BFC r9, #11, #17 
	b .
