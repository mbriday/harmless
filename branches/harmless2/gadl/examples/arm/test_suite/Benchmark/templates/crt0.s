.global _entryPoint
_entryPoint:
 LDR sp, =stack_top
 BL main
 B .
 
