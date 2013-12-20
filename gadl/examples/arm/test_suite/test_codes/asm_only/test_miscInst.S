/* % assembly misc inst test
 * % inst : 30
 */
 
.globl main
main :
  b label_PKHBT
  
label_PKHBT :
/* PKHBT {<cond>} <Rd>, <Rn>, <Rm> {, LSL #<shift_imm>} */
	mov r1, #0x00ff0000
	mov r2, #0x0000ab
	pkhbt r0, r1, r2
	pkhbt r0, r1, r2, LSL #2
	b label_PKHTB
	
label_PKHTB :
/* PKHTB {<cond>} <Rd>, <Rn>, <Rm> {, ASR #<shift_imm>} */
	pkhtb r3, r0, r2
	pkhtb r3, r0, r2, ASR #3
	b label_REV
	
label_REV :
/* REV{<cond>} Rd, Rm */
	rev r4, r3
	b label_REV16

label_REV16 :
/* REV16{<cond>} Rd, Rm */
	rev16 r5, r4
	b label_REVSH

label_REVSH :
/* REVSH{<cond>} Rd, Rm */
	revsh r6, r1
	b label_SEL

label_SEL :
/* SEL{<cond>} <Rd>, <Rn>, <Rm> */
	sel r7, r3, r6
	b label_SSAT

label_SSAT :
/* SSAT{<cond>} <Rd>, #<immed>, <Rm>{, <shift>} */
	/*mov r1, #0x00ff0000
	ssat r0, #24, r1
	ssat r0, #24, r1, LSL #1
	ssat r0, #24, r1, ASR #1
	b label_USAT

label_USAT :
label_SSAT16 :
label_USAT16 :*/

