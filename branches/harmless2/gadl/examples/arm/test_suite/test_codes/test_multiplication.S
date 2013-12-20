/* % assembly mult test
 * % inst : 1000
 */


.globl main
main :
  b label_MLA

label_MLA :
/* MLA{<cond>}{S} <Rd>, <Rm>, <Rs>, <Rn> */ 
	mov r1, #0x0a
	mov r2, #0xff
	mov r3, #0xd6
	mlas r0, r1, r2, r2
	b label_MUL
  
label_MUL :
/* MUL{<cond>}{S} <Rd>, <Rm>, <Rs> */
	muls r4, r0, r1
	/*b label_SMLAxy*/
	b label_SMLAL

/*label_SMLAxy :*/
/* SMLAL<x><y>{<cond>} <RdLo>, <RdHi>, <Rm>, <Rs> */
/*	smlalbb r5, r6, r4, r3
	smlalbt r7, r8, r5, r6
	smlaltb r1, r2, r7, r8
	smlaltt r0, r3, r1, r2
	b label_SMLAD*/

/*label_SMLAD :*/
/* SMLAD{X}{<cond>} <Rd>, <Rm>, <Rs>, <Rn> */
/*	smlad r2, r4, r6, r8
	smladx r1, r3, r5, r7
	b label_SMLAL*/

label_SMLAL :
/* SMLAL{<cond>}{S} <RdLo>, <RdHi>, <Rm>, <Rs> */
	smlals r3, r4, r1, r2
	/*b label_SMLALxy*/
	b label_SMULL
	
/*label_SMLALxy :/*
/* SMLAL<x><y>{<cond>} <RdLo>, <RdHi>, <Rm>, <Rs> */
/*	smlalbb r0, r1, r0, r4
	smlalbt r4, r6, r7, r0
	smlaltb r5, r8, r4, r4
	smlaltt r8, r2, r2, r3
	b label_SMLALD*/
	
/*label_SMLALD :*/
/* SMLALD{X}{<cond>} <RdLo>, <RdHi>, <Rm>, <Rs> */
/*	smlald r3, r4, r0, r1
	smlaldx r1, r2, r3, r4
	b label_SMLAWy*/

/*label_SMLAWy :*/
/* SMLAW<y>{<cond>} <Rd>, <Rm>, <Rs>, <Rn> */
/*	smlawb r5, r6, r7, r8
	smlawt r0, r5, r4, r3
	b label_SMLSD*/

/*label_SMLSD :*/
/* SMLSD{X}{<cond>} <Rd>, <Rm>, <Rs>, <Rn> */
/*	smlsd r4, r0, r5, r8
	smlsdx r2, r1, r3, r4
	b label_SMLSLD*/
	
/*label_SMLSLD :*/
/* SMLSLD{X}{<cond>} <RdLo>, <RdHi>, <Rm>, <Rs> */
/*	smlsld r0, r1, r3, r4
	smlsldx r7, r8, r5, r6
	b label_SMMLA*/
	
/*label_SMMLA :*/
/* SMMLA{R}{<cond>} <Rd>, <Rm>, <Rs>, <Rn> */
/*	smmla r2, r0, r1, r7
	smmlar r3, r7, r8, r0
	b label_SMMLS*/
	
/*label_SMMLS :*/
/* SMMLS{R}{<cond>} <Rd>, <Rm>, <Rs>, <Rn> */
/*	smmls r4, r5, r6, r7
	smmlsr r3, r4, r5, r6
	b label_SMMUL*/
	
/*label_SMMUL :/*
/* SMMUL{R}{<cond>} <Rd>, <Rm>, <Rs> */
/*	smmul r2, r1, r0
	smmulr r6, r2, r5
	b label_SMUAD*/
	
/*label_SMUAD :*/
/* SMUAD{X}{<cond>} <Rd>, <Rm>, <Rs> */
/*	smuad r4, r7, r3
	smuadx r8, r1, r0
	b label_SMULxy*/
	
/*label_SMULxy :*/
/* SMUL<x><y>{<cond>} <Rd>, <Rm>, <Rs> */
/*	smulbb r0, r8 ,r1
	smulbt r1, r7, r2
	smultb r2, r6, r3
	smultt r3, r5, r4
	b label_SMULL*/
	
label_SMULL :
/* SMULL{<cond>}{S} <RdLo>, <RdHi>, <Rm>, <Rs> */
	smulls r4, r5, r0, r1
	/*b label_SMULWy*/
	b label_UMLAL
	
/*label_SMULWy :*/
/* SMULW<y>{<cond>} <Rd>, <Rm>, <Rs> */
/*	smulwb r8, r4, r7
	smulwt r4, r6, r3
	b label_SMUSD*/
	
/*label_SMUSD :*/
/* SMUSD{X}{<cond>} <Rd>, <Rm>, <Rs> */
/*	smusd r5, r4, r3
	smusdx r2, r8, r1
	b label_UMAAL*/
	
/*label_UMAAL :*/
/* UMAAL{<cond>} <RdLo>, <RdHi>, <Rm>, <Rs> */
/*	umaal r6, r2, r3, r5
	b label_UMLAL*/
	
label_UMLAL :
/* UMLAL{<cond>}{S} <RdLo>, <RdHi>, <Rm>, <Rs> */
	umlals r0, r3, r1, r2
	b label_UMULL
	
label_UMULL :
/* UMULL{<cond>}{S} <RdLo>, <RdHi>, <Rm>, <Rs> */
	mov r7, #0
	umulls r5, r6, r7, r8
	
	b main

