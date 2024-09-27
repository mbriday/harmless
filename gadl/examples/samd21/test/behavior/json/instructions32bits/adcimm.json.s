.text
.syntax unified
.thumb
.global _start
_start:
	ADC.W r0, r0, #0 
	ADC.W r0, r2, #0 
	ADC.W r0, r7, #0 
	ADC.W r0, r0, #7 
	ADC.W r0, r2, #7 
	ADC.W r0, r7, #7 
	ADC.W r0, r0, #172 
	ADC.W r0, r2, #172 
	ADC.W r0, r7, #172 
	ADC.W r0, r0, #255 
	ADC.W r0, r2, #255 
	ADC.W r0, r7, #255 
	ADC.W r7, r0, #0 
	ADC.W r7, r2, #0 
	ADC.W r7, r7, #0 
	ADC.W r7, r0, #7 
	ADC.W r7, r2, #7 
	ADC.W r7, r7, #7 
	ADC.W r7, r0, #172 
	ADC.W r7, r2, #172 
	ADC.W r7, r7, #172 
	ADC.W r7, r0, #255 
	ADC.W r7, r2, #255 
	ADC.W r7, r7, #255 
	ADC.W r14, r0, #0 
	ADC.W r14, r2, #0 
	ADC.W r14, r7, #0 
	ADC.W r14, r0, #7 
	ADC.W r14, r2, #7 
	ADC.W r14, r7, #7 
	ADC.W r14, r0, #172 
	ADC.W r14, r2, #172 
	ADC.W r14, r7, #172 
	ADC.W r14, r0, #255 
	ADC.W r14, r2, #255 
	ADC.W r14, r7, #255 
	b .
