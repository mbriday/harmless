Put in this directory all the test codes with correct extension
	- Assembly ending with ".s"
	- C source code ".c"
	- Executable ".elf"

Test codes sources must have "% name of the test" on the fist line
and "% inst: number_of_instruction" on the second one.

Example:

# % This is a test
# % inst: 100
# It will be executed on 100 instructions

or

/* %This is a test
 * % inst: 100
 */
