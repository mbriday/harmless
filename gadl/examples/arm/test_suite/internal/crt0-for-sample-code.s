/****************************************************************************/
/*               Mode Definition                                            */
/****************************************************************************/

   ARM_MODE_USER  = 0x10      /* Normal User Mode                             */ 
   ARM_MODE_FIQ   = 0x11      /* FIQ Fast Interrupts Mode                     */
   ARM_MODE_IRQ   = 0x12      /* IRQ Standard Interrupts Mode                 */
   ARM_MODE_SVC   = 0x13      /* Supervisor Interrupts Mode                   */
   ARM_MODE_ABORT = 0x17      /* Abort Processing memory Faults Mode          */
   ARM_MODE_UNDEF = 0x1B      /* Undefined Instructions Mode                  */
   ARM_MODE_SYS   = 0x1F      /* System Running in Priviledged Operating Mode */
   ARM_MODE_MASK  = 0x1F

/****************************************************************************/
/*   Interrupt bit masks                                                    */
/****************************************************************************/
   
   I_BIT          = 0x80      /* disable IRQ when I bit is set */
   F_BIT          = 0x40      /* disable IRQ when I bit is set */

   VICIntEnClear  = 0xFFFFF014

/****************************************************************************/
/*               Vector table                                               */
/****************************************************************************/

   .section .vectors,"ax"
   .code 32

_vectors:
   ldr pc, ResetAddr    /* Reset                 */
   ldr pc, UndefAddr    /* Undefined instruction */
   ldr pc, SWIAddr      /* Software interrupt    */
   ldr pc, PAbortAddr   /* Prefetch abort        */
   ldr pc, DAbortAddr   /* Data abort            */
   .word 0xB8A06F58
   ldr pc, IRQAddr      /* IRQ interrupt         */
   ldr pc, FIQAddr      /* FIQ interrupt         */


ResetAddr:     .word ResetHandler
UndefAddr:     .word UndefHandler
SWIAddr:       .word SWIHandler
PAbortAddr:    .word PAbortHandler
DAbortAddr:    .word DAbortHandler
ReservedAddr:  .word 0
IRQAddr:       .word IRQHandler
FIQAddr:       .word FIQHandler

/****************************************************************************/
/*                           Reset handler                                  */
/****************************************************************************/

   .section .init, "ax"
   .code 32
   
   .global ResetHandler
   .global ExitFunction
   .extern main

ResetHandler:
/* Wait for the oscillator is stable */   
   nop
   nop
   nop
   nop
   nop
   nop
   nop
   nop
   
/* Setup a stack for each mode */    
   msr   CPSR_c, #ARM_MODE_UNDEF | I_BIT | F_BIT   /* Undefined Instruction Mode */     
   ldr   sp, =__stack_und_end
   
   msr   CPSR_c, #ARM_MODE_ABORT | I_BIT | F_BIT   /* Abort Mode */
   ldr   sp, =__stack_abt_end
   
   msr   CPSR_c, #ARM_MODE_FIQ | I_BIT | F_BIT     /* FIQ Mode */   
   ldr   sp, =__stack_fiq_end
   
   msr   CPSR_c, #ARM_MODE_IRQ | I_BIT | F_BIT     /* IRQ Mode */   
   ldr   sp, =__stack_irq_end
   
   msr   CPSR_c, #ARM_MODE_SVC | I_BIT | F_BIT     /* Supervisor Mode */
   ldr   sp, =__stack_svc_end

/*--- Initialize PLL and system clock */
   bl    initialize_lpc2200_pll

/* Clear .bss section */
   ldr   r1, =__bss_start__
   ldr   r2, =__bss_end__
   ldr   r3, =0
bss_clear_loop:
   cmp   r1, r2
   strne r3, [r1], #+4
   bne   bss_clear_loop
   
/*--- Clear all remaining interrupt enables */
/*    (they can be still enabled after a soft reset) */
   mvn   r0, #0
   ldr   r1, =VICIntEnClear
   str   r0, [r1]

/*--- Enable FIQ and IRQ interrupts */
   mrs   r0, cpsr
   bic   r0, r0, #I_BIT | F_BIT
   msr   cpsr, r0

   
   mov   r0, #0 /* No arguments */
   mov   r1, #0 /* No arguments */
   bl    main

ExitFunction:
   b ExitFunction   
   
/****************************************************************************/

   .ltorg

/****************************************************************************/

  .end
