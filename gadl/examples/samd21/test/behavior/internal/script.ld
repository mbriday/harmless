/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                                   Link script                              */
/*                                                                            */
/*                                   stm32f303                                */
/*                                                                            */
/* <INIT_POLICY>                                                              */
/* - NO_INIT :          used for variables that are never cleared and never   */
/*                      initialized.                                          */
/* - CLEARED :          used for variables that are cleared to zero after     */
/*                      every reset.                                          */
/* - POWER_ON_CLEARED : used for variables that are cleared to zero only      */
/*                      after power on reset.                                 */
/* - INIT :             used for variables that are initialized with values   */
/*                      after every  reset.                                   */
/* - POWER_ON_INIT :    used for variables that are initialized with values   */
/*                      only after power on reset.                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                                   Configuration                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ENTRY(_start)

/* Highest address of the user mode stack */
_estack = 0x20003000;    /* end of 12K RAM on AHB bus*/

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0;      /* required amount of heap  */
_Min_Stack_Size = 0x400; /* required amount of stack */

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                                   Memory                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/* Specify the memory areas for stm32f303 */
MEMORY
{
  VECTOR (rx)     : ORIGIN = 0x08000000, LENGTH = 0x168
  FLASH (rx)      : ORIGIN = 0x08000168, LENGTH = 0xFE98
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 12K
  MEMORY_B1 (rx)  : ORIGIN = 0x60000000, LENGTH = 0x0
}

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                                    Code                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
 * code and const of the operating system (Trampoline).
 * this section is not accessible from an untrusted process
 */
SECTIONS {
  . = ALIGN(4);
  /* --- code of OS --- */
  text : {
    *(.text)
  } >RAM
  . = ALIGN(4);
}

