.LSP:
	.word _init_sp

.text
.globl _entryPoint
_entryPoint:
    ldr	sp, .LSP
	b main
	
_end:
	nop
