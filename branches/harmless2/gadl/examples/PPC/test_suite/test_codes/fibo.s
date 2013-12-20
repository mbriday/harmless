 # % Suite de fibonacci
 # % inst: 5
 # This is an example test. The first line is the name of the test
 # the second one is the number of instructions to execute during the test
 # and then an optionnal comment
 # fibonacci :
 # u(n) = u(n-1)+u(n-2)
 # u(0) = 1
 # u(1) = 1
 # finaly the assembly code of the test. beginning by the "_start" label.
# "_start" must be defined as a global symbol

.globl main
main:
init:
	li 1,1 # u(0) = 1
	li 2,1 # u(1) = 1

boucle:
	add 3,1,2 # somme
	mr 1,2
	mr 2,3
	ba boucle
	b test
test:
