This test is used to compare the ISS with the one embedded in GDB.
There is a directory 'test_codes' with all codes:
	- Assembly ending with ".s"
	- C source code ".c"
	- Executable ".elf"
Each source file should also have a .cfg file with 2 lines like this:
% Description of the test (display). There is '% ' at the beginning
% inst: 100 //<- number of instructions to simulate

Then a build script is provided build.py
This script generates:
 * .elf files from .s and .c files (-> require the cross-compiler).
   It uses the crt0.s provided in internal/ 
 * .gdb the gdb output (-> require the cross-compiler).
*** It does not require the Harmless simulator ***
*** all generated files are located in the build/ directory ***

A test script: compare.py, is used to make tests, and compare output files.
No cross-compiler is required at this stage.
-> This compare script is called by the main python script 'runTests'.
