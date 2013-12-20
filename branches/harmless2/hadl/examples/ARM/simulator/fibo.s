
   .set     N_FIBO, 10
   
@ -------------------------------------------------------------------
@ Variables
@ -------------------------------------------------------------------

            .bss
            .align 4

tab:        .space 1024

stack:      .space 256
stack_base:

@ -------------------------------------------------------------------
@ Programme principal
@ -------------------------------------------------------------------

            .text
            .arm
            .align 4
   
            .global start

start:

   ldr   sp, =stack_base

   ldr   r0, =tab

   mov   r4, #1
   str   r4, [r0], #4
   str   r4, [r0], #4
   
   mov   r1, #(N_FIBO-2)

loop:
   ldr   r4, [r0, #-4]
   ldr   r5, [r0, #-8]
   add   r5, r4, r5
   str   r5, [r0], #4
   
   subs  r1, r1, #1
   bne   loop
   
forever:
   b     forever


