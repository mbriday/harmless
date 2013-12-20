/* % Suite de fibonacci
 * % inst: 500
 * This is an example test. The first line is the name of the test
 * the second one is the number of instructions to execute during the test
 * and then an optionnal comment
 * fibonacci :
 * u(n) = u(n-1)+u(n-2)
 * u(0) = 1
 * u(1) = 1
 */

.globl main
main :
	mov r1, #1
	mov r2, #1
loop:
	add r3, r2, r1
	mov r1, r2
	mov r2, r3
	b loop
