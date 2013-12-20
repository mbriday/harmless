# crt0.S

# Startup file
# initialize the stack Pointer with information provided by the linker
# Should be compiled (with 'as') and linked with any program aimed to run on Harmless ARM
# simulator

.LSP:
	.word	_init_sp

.text
.globl _start
_start:
    ldr	sp, .LSP
	bl main
end:
	b end
