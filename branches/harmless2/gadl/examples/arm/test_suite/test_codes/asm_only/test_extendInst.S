/* % assembly extend inst test
 * % inst : 60
 */
 
.globl main
main :
	b label_SXTAB16
 
label_SXTAB16 :
/* SXTAB16{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>} */
	mov r1, #0xffffff00
	mov r2, #0x001c0000
	sxtab16 r0, r1, r2
	sxtab16 r0, r1, r2, ROR #8
	sxtab16 r0, r1, r2, ROR #16
	sxtab16 r0, r1, r2, ROR #24

label_SXTAB :
/* SXTAB{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>} */
	sxtab r3, r0, r2
	sxtab r3, r0, r2, ROR #8
	sxtab r3, r0, r2, ROR #16
	sxtab r3, r0, r2, ROR #24

label_SXTAH :
/* SXTAH{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>} */
	sxtah r4, r1, r3
	sxtah r4, r1, r3, ROR #8
	sxtah r4, r1, r3, ROR #16
	sxtah r4, r1, r3, ROR #24

label_SXTB16 :
/* SXTB16{<cond>} <Rd>, <Rm>{, <rotation>} */
	sxtb16 r5, r4
	sxtb16 r5, r4, ROR #8
	sxtb16 r5, r4, ROR #16
	sxtb16 r5, r4, ROR #24

label_SXTB :
/* SXTB{<cond>} <Rd>, <Rm>{, <rotation>} */
	sxtb r6, r2
	sxtb r6, r2, ROR #8
	sxtb r6, r2, ROR #16
	sxtb r6, r2, ROR #24

label_SXTH :
/* SXTH{<cond>} <Rd>, <Rm>{, <rotation>} */
	sxth r7, r3
	sxth r7, r3, ROR #8
	sxth r7, r3, ROR #16
	sxth r7, r3, ROR #24

label_UXTAB16 :
/* UXTAB16{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>} */
	uxtab16 r8, r5, r7
	uxtab16 r8, r5, r7, ROR #8
	uxtab16 r8, r5, r7, ROR #16
	uxtab16 r8, r5, r7, ROR #24

label_UXTAB :
/* UXTAB{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>} */
	uxtab r0, r8, r4
	uxtab r0, r8, r4, ROR #8
	uxtab r0, r8, r4, ROR #16
	uxtab r0, r8, r4, ROR #24
	
label_UXTAH :
/* UXTAH{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>} */
	uxtah r1, r1, r2
	uxtah r1, r1, r2, ROR #8
	uxtah r1, r1, r2, ROR #16
	uxtah r1, r1, r2, ROR #24

label_UXTB16 :
/* UXTB16{<cond>} <Rd>, <Rm>{, <rotation>} */
	uxtb16 r2, r0
	uxtb16 r2, r0, ROR #8
	uxtb16 r2, r0, ROR #16
	uxtb16 r2, r0, ROR #24
	
label_UXTB :
/* UXTB{<cond>} <Rd>, <Rm>{, <rotation>} */
	uxtb r3, r8
	uxtb r3, r8, ROR #8
	uxtb r3, r8, ROR #16
	uxtb r3, r8, ROR #24

label_UXTH :
/* UXTH{<cond>} <Rd>, <Rm>{, <rotation>} */
	uxth r4, r3
	uxth r4, r3, ROR #8
	uxth r4, r3, ROR #16
	uxth r4, r3, ROR #24

