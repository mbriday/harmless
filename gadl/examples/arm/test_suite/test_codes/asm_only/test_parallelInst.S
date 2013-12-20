/* % assembly parallel inst test
 * % inst : 65
 */

.globl main
main :
	b label_QADD16

/* ____{<cond>} <Rd>, <Rn>, <Rm> */

label_QADD16 :
	mov r1, #0xffffff00
	mov r2, #0x001c0000
	qadd16 r0, r1, r2
	b label_QADD8

label_QADD8 : 
	qadd8 r3, r0, r2
	b label_QADDSUBX
	
label_QADDSUBX :
	qaddsubx r4, r3, r1
	b label_QSUB16
	
label_QSUB16 :
	qsub16 r5, r2, r4
	b label_QSUB8
	
label_QSUB8 :
	qsub8 r6, r3, r5
	b label_QSUBADDX

label_QSUBADDX :
	qsubaddx r7, r6, r4
	b label_SADD16
	
label_SADD16 :
	sadd16 r8, r7, r6
	b label_SADD8
	
label_SADD8 :
	sadd8 r2, r8, r5
	b label_SADDSUBX
	
label_SADDSUBX :
	saddsubx r3, r1, r7
	b label_SSUB16
	
label_SSUB16 :
	ssub16 r0, r3, r2
	b label_SSUB8
	
label_SSUB8 :
	ssub8 r6, r8, r0
	b label_SSUBADDX
	
label_SSUBADDX :
	ssubaddx r5, r2, r7
	b label_SHADD16
	
label_SHADD16 :
	shadd16 r8, r2, r0
	b label_SHADD8
	
label_SHADD8 :
	shadd8 r6, r7, r4
	b label_SHADDSUBX
	
label_SHADDSUBX :
	shaddsubx r3, r6, r8
	b label_SHSUB16
	
label_SHSUB16 :
	shsub16 r1, r3, r5
	b label_SHSUB8
	
label_SHSUB8 :
	shsub8 r4, r1, r2
	b label_SHSUBADDX
	
label_SHSUBADDX :
	shsubaddx r8, r3, r4
	b label_UADD16

label_UADD16:
	uadd16 r7, r2, r8
	b label_UADD8

label_UADD8 :
	uadd8 r1, r2, r6
	b label_UADDSUBX

label_UADDSUBX :
	uaddsubx r3, r6, r8 
	b label_USUB16
	
label_USUB16 :
	usub16 r4, r3, r1
	b label_USUB8
	
label_USUB8 :
	usub8 r5, r1, r0
	b label_USUBADDX

label_USUBADDX :
	usubaddx r5, r8, r7
	b label_UHADD16

label_UHADD16 :
	uhadd16 r2, r7, r4
	b label_UHADD8

label_UHADD8 :
	uhadd8 r5, r5, r2
	b label_UHADDSUBX
	
label_UHADDSUBX :
	uhaddsubx r2, r1, r4
	b label_UHSUB16

label_UHSUB16 :
	uhsub16 r8, r5, r3
	b label_UHSUB8

label_UHSUB8 :
	uhsub8 r4, r2, r7
	b label_UHSUBADDX
	
label_UHSUBADDX :
	uhsubaddx r7, r6, r2
	b label_UQADD16

label_UQADD16 :
	uqadd16 r6, r8, r2
	b label_UQADD8
	
label_UQADD8 :
	uqadd8 r0, r1, r6
	b label_UQADDSUBX
	
label_UQADDSUBX :
	uqaddsubx r3, r7, r0
	b label_UQSUB16
	label_UQSUB16 :
	uqsub16 r6, r2, r1
	b label_UQSUB8
	
label_UQSUB8 :
	uqsub8 r7, r2, r3
	b label_UQSUBADDX
	
label_UQSUBADDX :
	uqsubaddx r3, r1, r4

