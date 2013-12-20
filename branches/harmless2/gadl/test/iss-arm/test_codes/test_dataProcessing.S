/* % assembly data proc test
% inst: 800
*/

.globl main
main:
  b label_ADC
  
label_ADC:
/* ADC{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
	adcs r0, r0, #3 /* #<immediat> */
    adcs r1, r0, r0 /* <Rm> */
	adcs r2, r0, r1, LSL #30 /* <Rm>, LSL #<shift_imm> */
	adcs r3, r1, r2, LSL r1 /* <Rm>, LSL <Rs> */
	adcs r4, r2, r3, LSR #19 /* <Rm>, LSR #<shift_imm> */
	adcs r5, r3, r4, LSR r1 /* <Rm>, LSR <Rs> */
	adcs r6, r4, r5, ASR #6 /* <Rm>, ASR #<shift_imm> */
	adcs r7, r5, r6, ASR r0 /* <Rm>, ASR <Rs> */
	adcs r8, r6, r7, ROR #7 /* <Rm>, ROR #<shift_imm> */
	adcs r9, r7, r8, ROR r1 /* <Rm>, ROR <Rs> */
	adcs r0, r8, r9, RRX /* <Rm>, RRX */
/* Flag test */
	mov r0, #0
	adcs r0, r0, #0x80000000 /* N Flag */
	adcs r0, r0, r0 /* Z Flag + C Flag + V Flag */
	mov r1, #0x7fffffff
	adcs r0, r1, #0 /* V Flag */
	b label_ADD

label_ADD: 
/* ADD{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
	adds r0, r3, r4, ASR #21
	b label_AND 

label_AND:
/* AND{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */ 
	ands r1, r2, r3, ROR #2
	b label_BIC

label_BIC:
/* BIC{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
/* Addressing shifter operand test */
	bics r0, r0, #0x80000000 /* #<immediat> -- carryout = 31 bit*/
	bics r0, r0, #0x00000003 /* #<immediat> -- carryout = C Flag */
    bics r1, r0, r0 /* <Rm> -- carryout = C Flag */
	mov r1, #0x80000000
	bics r2, r0, r1, LSL #1 /* <Rm>, LSL #<shift_imm> -- carryout = 32-shift_imm bit*/
	mov r0, #0
	bics r3, r1, r2, LSL r0 /* <Rm>, LSL <Rs> -- carryout = C Flag */
	mov r0, #1
	mov r2, #0x80000000
	bics r3, r1, r2, LSL r0 /* <Rm>, LSL <Rs> -- carryout = 32-Rs[7:0] bit*/
	mov r1, #0x000000ff
	bics r3, r1, r2, LSL r1 /* <Rm>, LSL <Rs> -- carryout = 0 */
	mov r1, #0x00000020
	mov r2, #0x00000001
	bics r3, r1, r2, LSL r1 /* <Rm>, LSL <Rs> -- carryout = 0 bit */
	mov r0, #0xa0000000
	bics r4, r2, r0, LSR #0 /* <Rm>, LSR #<shift_imm> -- carryout = 31 bit */
	bics r4, r2, r0, LSR #30 /* <Rm>, LSR #<shift_imm> -- carryout = shift-1 bit */
	bics r0, r1, r2, RRX /* <Rm>, RRX */
	b label_CMN
	
label_CMN: 
/* CMN{<cond>} <Rn>, <shifter_operand> */
	cmn r0, #10
	b label_CMP
	
label_CMP: 
/* CMP{<cond>} <Rn>, <shifter_operand> */
	/* C Flag & V Flag test */
	mov r1, #0x40000000
	cmp r1, #0x50000000 /* ~C Flag */
	mov r2, #0x90000000
	cmp r2, #0x80000000 /* C Flag */
	mov r2, #0x80000000
	cmp r2, #0 /* V Flag */
	mov r3, #0
	cmp r3, r2
	cmp r1, r3
	cmp r1, #1
	b label_EOR
	
label_EOR: 
/* EOR{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
	eors r0, r4, #0xff00
	b label_MOV
	
label_MOV:
/* MOV{<cond>}{S} <Rd>, <shifter_operand> */
	movs r1, r2
	b label_MVN

label_MVN:
/* MVN{<cond>}{S} <Rd>, <shifter_operand> */
	mvns r4, r7, LSL #2
	b label_ORR

label_ORR:
/* ORR{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
	orrs r5, r3, r1, RRX
	b label_RSB

label_RSB:
/* RSB{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
	rsbs r7, r8, r2, ASR #5
	b label_RSC

label_RSC:
/* RSC{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
	rscs r3, r1, r7, LSR #8
	b label_SBC

label_SBC:
/* SBC{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
	sbcs r5, r5, r1
	b label_SUB

label_SUB:
/* SUB{<cond>}{S} <Rd>, <Rn>, <shifter_operand> */
	subs r2, r6, r0, LSL #9
	b label_TEQ

label_TEQ: 
/* TEQ{<cond>} <Rn>, <shifter_operand> */
	teq r4, r3, LSR #1
	b label_TST

label_TST:
/* TST{<cond>} <Rn>, <shifter_operand> */
	tst r8, r7, ROR #3
   b main
