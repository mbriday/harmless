/* % assembly load store test
 * % inst : 600
 */
 
.globl main
main :
	b label_LDR
	
label_LDR :
/* LDR{<cond>} <Rd>, <addressing_mode> */
/* addressing mode tests */
	/* [<Rn>, #+/-<offset_12>] */
	ldr r0, [pc, #-0x004]
	/* [<Rn>, +/-<Rm>] */
	mov r1, #0x008
	ldr r0, [pc, +r1]
	/* [<Rn>, +/-<Rm>, <shift> #<shift_imm>] */
	ldr r0, [pc, +r1, LSL # 1]
	mov r2, #0x080 
	ldr r0, [pc, +r2, LSR # 1]
	ldr r0, [pc, -r2, ASR # 5]
	ldr r0, [pc, -r2, ROR # 3]
	/* [<Rn>, #+/-<offset_12>]! */
	ldr r0, [pc, #-0x00c]
	/* [<Rn>, +/-<Rm>]! */
	mov r2, pc
	mov r1, #0x010
	ldr r0, [r2, -r1]!
	/* [<Rn>, +/-<Rm>, <shift> #<shift_imm>]! */
	mov r2, pc
	ldr r0, [r2, -r1, LSR #2]!
	/* [<Rn>], #+/-<offset_12> */
	mov r2, pc
	ldr r0, [r2], #-0x01b
	/* [<Rn>], +/-<Rm> */
	mov r2, pc
	ldr r0, [r2], -r1
	/* [<Rn>], +/-<Rm>, <shift> #<shift_imm> */
	mov r2, pc
	ldr r0, [r2], -r2, LSR #6
	b label_LDRB
	
label_LDRB :
/* LDR{<cond>}B <Rd>, <addressing_mode> */
	mov r2, pc
	ldrb r0, [r2, +r1]
	b label_LDRBT
	
label_LDRBT :
/* LDR{<cond>}BT <Rd>, <post_indexed_addressing_mode> */
	mov r2, pc
	ldrbt r0, [r2], +r1
	b label_LDRD
	
label_LDRD :
/* LDR{<cond>}D <Rd>, <addressing_mode> */
	mov r2, pc
	#ldrd r0, [r2, +r1]
	b label_LDREX
	
label_LDREX :
/* LDREX{<cond>} <Rd>, [<Rn>] */
	mov r2, pc
	#ldrex r0, [r2]
	b label_LDRH
	
label_LDRH :
/* LDR{<cond>}H <Rd>, <addressing_mode> */
	mov r2, pc
	ldrh r0, [r2, +r1]
	b label_LDRSB
	
label_LDRSB :
/* LDR{<cond>}SB <Rd>, <addressing_mode> */
	mov r2, pc
	ldrsb r0, [r2, +r1]
	b label_LDRSH
	
label_LDRSH :
/* LDR{<cond>}SH <Rd>, <addressing_mode>  */
	mov r2, pc
	ldrsh r0, [r2, +r1]
	b label_LDRT
	
label_LDRT :
/* LDR{<cond>}T <Rd>, <post_indexed_addressing_mode> */
	mov r2, pc
	ldrt r0, [r2], -r1
	b label_LDM
	
label_LDM :
/* LDM{<cond>}<addressing_mode> <Rn>{!}, <registers> */
	
/* LDM{<cond>}<addressing_mode> <Rn>, <registers_without_pc>^ */
	mov r2, pc
	ldmia r2, {r0, r1, r3}^
	mov r2, pc
	ldmib r2, {r0, r1, r3}^
	mov r2, pc
	ldmda r2, {r0, r1, r3}^
	mov r2, pc
	ldmdb r2, {r0, r1, r3}^
/* LDM{<cond>}<addressing_mode> <Rn>{!}, <registers_and_pc>^ */

	b main
