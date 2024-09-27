.text
.syntax unified
.thumb
.global _start
_start:
	ADDW r1, r0, #0
	ADDW r1, r2, #0
	ADDW r1, r7, #0
	ADDW r1, r0, #32
	ADDW r1, r2, #32
	ADDW r1, r7, #32
	ADDW r1, r0, #224
	ADDW r1, r2, #224
	ADDW r1, r7, #224
	ADDW r1, r0, #252
	ADDW r1, r2, #252
	ADDW r1, r7, #252
	ADDW r1, r0, #4095
	ADDW r1, r2, #4095
	ADDW r1, r7, #4095
	ADDW r5, r0, #0
	ADDW r5, r2, #0
	ADDW r5, r7, #0
	ADDW r5, r0, #32
	ADDW r5, r2, #32
	ADDW r5, r7, #32
	ADDW r5, r0, #224
	ADDW r5, r2, #224
	ADDW r5, r7, #224
	ADDW r5, r0, #252
	ADDW r5, r2, #252
	ADDW r5, r7, #252
	ADDW r5, r0, #4095
	ADDW r5, r2, #4095
	ADDW r5, r7, #4095
	ADDW r9, r0, #0
	ADDW r9, r2, #0
	ADDW r9, r7, #0
	ADDW r9, r0, #32
	ADDW r9, r2, #32
	ADDW r9, r7, #32
	ADDW r9, r0, #224
	ADDW r9, r2, #224
	ADDW r9, r7, #224
	ADDW r9, r0, #252
	ADDW r9, r2, #252
	ADDW r9, r7, #252
	ADDW r9, r0, #4095
	ADDW r9, r2, #4095
	ADDW r9, r7, #4095
	b .
