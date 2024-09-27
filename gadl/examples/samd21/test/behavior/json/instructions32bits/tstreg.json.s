.text
.syntax unified
.thumb
.global _start
_start:
	TST.W r0, r2,lsl #0 
	TST.W r0, r9,lsl #0 
	TST.W r7, r2,lsl #0 
	TST.W r7, r9,lsl #0 
	TST.W r0, r2,lsl #4 
	TST.W r0, r9,lsl #4 
	TST.W r7, r2,lsl #4 
	TST.W r7, r9,lsl #4 
	TST.W r0, r2,lsl #31 
	TST.W r0, r9,lsl #31 
	TST.W r7, r2,lsl #31 
	TST.W r7, r9,lsl #31 
	TST.W r0, r2,lsr #0 
	TST.W r0, r9,lsr #0 
	TST.W r7, r2,lsr #0 
	TST.W r7, r9,lsr #0 
	TST.W r0, r2,lsr #4 
	TST.W r0, r9,lsr #4 
	TST.W r7, r2,lsr #4 
	TST.W r7, r9,lsr #4 
	TST.W r0, r2,lsr #31 
	TST.W r0, r9,lsr #31 
	TST.W r7, r2,lsr #31 
	TST.W r7, r9,lsr #31 
	TST.W r0, r2,asr #0 
	TST.W r0, r9,asr #0 
	TST.W r7, r2,asr #0 
	TST.W r7, r9,asr #0 
	TST.W r0, r2,asr #4 
	TST.W r0, r9,asr #4 
	TST.W r7, r2,asr #4 
	TST.W r7, r9,asr #4 
	TST.W r0, r2,asr #31 
	TST.W r0, r9,asr #31 
	TST.W r7, r2,asr #31 
	TST.W r7, r9,asr #31 
	TST.W r0, r2,ror #0 
	TST.W r0, r9,ror #0 
	TST.W r7, r2,ror #0 
	TST.W r7, r9,ror #0 
	TST.W r0, r2,ror #4 
	TST.W r0, r9,ror #4 
	TST.W r7, r2,ror #4 
	TST.W r7, r9,ror #4 
	TST.W r0, r2,ror #31 
	TST.W r0, r9,ror #31 
	TST.W r7, r2,ror #31 
	TST.W r7, r9,ror #31 
	b .
