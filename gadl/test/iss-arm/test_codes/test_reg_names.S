/* % register names used by objdump
 * % inst : 5
 */

	.global main
main:
	stmia   sp, {r0-r15}
	mov     pc, lr
