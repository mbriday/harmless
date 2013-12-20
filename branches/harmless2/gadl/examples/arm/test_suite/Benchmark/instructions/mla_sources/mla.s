.globl main
main :
	mov r0, #0xad0
	mov r1, #0x13
	mov r2, #0xc00
	b mla
	
mla :
	mlas r1, r0, r1, r2
	b mla
