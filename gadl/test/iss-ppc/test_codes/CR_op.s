# % CR operation test
# % inst: 100

.section .text
.globl main
main:
	lis 5, 0x4000 # 0 in bit 0 and 1 in bit 1
	mtcr 5
	crand 3,0,0
	crandc 3,0,0
	creqv 3,0,0
	crnand 3,0,0
	crnor 3,0,0
	cror 3,0,0
	crorc 3,0,0
	crxor 3,0,0
	crand 3,0,1
	crandc 3,0,1
	creqv 3,0,1
	crnand 3,0,1
	crnor 3,0,1
	cror 3,0,1
	crorc 3,0,1
	crxor 3,0,1
	crand 3,1,0
	crandc 3,1,0
	creqv 3,1,0
	crnand 3,1,0
	crnor 3,1,0
	cror 3,1,0
	crorc 3,1,0
	crxor 3,1,0
	crand 3,1,1
	crandc 3,1,1
	creqv 3,1,1
	crnand 3,1,1
	crnor 3,1,1
	cror 3,1,1
	crorc 3,1,1
	crxor 3,1,1
    mcrf 1,0
	ba main

