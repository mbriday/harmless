
   .section .text, "ax"
   .code 32
   
/*--------------------------------------------------------------------------*/
/*                           Entry point                                    */
/*--------------------------------------------------------------------------*/
.LabelSP:
	.word	_init_sp

.global _entryPoint  
.global shouldNotHappen
_entryPoint:
/*--- Clear bss section */
   ldr   r1, =__bss_start__
   ldr   r2, =__bss_end__
   mov   r3, #0
_bss_clear_loop:
   cmp   r1, r2
   strne r3, [r1], #+4
   bne   _bss_clear_loop

/*then init stack pointer */
   ldr	sp, .LabelSP

/*--- Call main */    
   mov   r0, #0 /* No arguments */
   mov   r1, #0 /* No arguments */
   bl    main
shouldNotHappen:
   b shouldNotHappen
/*--------------------------------------------------------------------------*/

   .ltorg

/*--------------------------------------------------------------------------*/
