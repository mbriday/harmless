.text
.syntax unified
.thumb
.global _start
_start:
	SUBW r0, r0, #0
	SUBW r0, r2, #0
	SUBW r0, r7, #0
	SUBW r0, r0, #426
	SUBW r0, r2, #426
	SUBW r0, r7, #426
	SUBW r0, r0, #2748
	SUBW r0, r2, #2748
	SUBW r0, r7, #2748
	SUBW r0, r0, #2799
	SUBW r0, r2, #2799
	SUBW r0, r7, #2799
	SUBW r0, r0, #4095
	SUBW r0, r2, #4095
	SUBW r0, r7, #4095
	SUBW r5, r0, #0
	SUBW r5, r2, #0
	SUBW r5, r7, #0
	SUBW r5, r0, #426
	SUBW r5, r2, #426
	SUBW r5, r7, #426
	SUBW r5, r0, #2748
	SUBW r5, r2, #2748
	SUBW r5, r7, #2748
	SUBW r5, r0, #2799
	SUBW r5, r2, #2799
	SUBW r5, r7, #2799
	SUBW r5, r0, #4095
	SUBW r5, r2, #4095
	SUBW r5, r7, #4095
	SUBW r7, r0, #0
	SUBW r7, r2, #0
	SUBW r7, r7, #0
	SUBW r7, r0, #426
	SUBW r7, r2, #426
	SUBW r7, r7, #426
	SUBW r7, r0, #2748
	SUBW r7, r2, #2748
	SUBW r7, r7, #2748
	SUBW r7, r0, #2799
	SUBW r7, r2, #2799
	SUBW r7, r7, #2799
	SUBW r7, r0, #4095
	SUBW r7, r2, #4095
	SUBW r7, r7, #4095
	b .
