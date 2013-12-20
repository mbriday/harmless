/* % register names used by objdump
 * % inst : 50
 */

	.global main
main:
	stmia   sp, {r0-r15}
	mov     pc, lr
