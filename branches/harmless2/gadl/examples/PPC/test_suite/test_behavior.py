#!/usr/bin/python

# Test of a behavior description
# usage ./test_behavior.py [<test_file> [<test file> [etc...]]]
#
# The Harmless simulator is compared with the GDB simulator on codes (ASM, C or
# binary elf files)in the test_codes/ directory (if there is no
# argument, if any, only the code files of the arguments are compared).
# Each one of them is compiled in ./tmp/test_code.elf. This file is
# executed by both simulator and the trace is compared
# If there is a difference, "diff" is shown.
#
# the harmless simulator have to be compiled before executing this script.
# It has to be in ../powerpc/

# Test codes must have "% name of the test" on the fist line
# and "% inst: number_of_instruction" on the second one.

# The scripts need the PPC_XTOOLS environnement variable
# Exemple :
# If GCC is in ~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-gcc
# set PPC_XTOOLS to "~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-"
# you may put
# "export PPC_XTOOLS=~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-"
# In your shell init script ~/.bashrc

# BUGS :
#	This script can't be moved around and have to be executed right here

import os
import re
import sys

# Number of instruction executed for an elf-test
nbInstForElfFiles = 3000

#
# Check if the system is ready
#

#make sure that the python simulator is built
sys.path.append("../powerpc")
try:
	from powerpc import arch
except ImportError:
	print "the powerpc simulator does not seem to be generated (in ../powerpc/)"
	print "try to compile it using gadl (gadl ppc_iss.hadl)"
	print "then compile the simulator (in the generated dir) using:"
	print "make python"
	print "Swig tool should be installed"
	sys.exit()

try:
	xtools = os.environ["PPC_XTOOLS"]
except KeyError:
	print "The PPC_XTOOLS environnement variable doesn't exist... Please define it."
	sys.exit()

xgcc=xtools + "gcc"
xas= xtools + "as"
xobjdump=xtools+"objdump"

# check the crosstools
if not os.path.isfile(xgcc) :
	print "Can't find Cross GCC... aborting"
	sys.exit()

if not os.path.isfile(xas) :
	print "Can't find Cross assembler... aborting"
	sys.exit()

if not os.path.isfile(xobjdump) :
	print "Can't find Cross objdump... aborting"
	sys.exit()


#
# Miscellaneous functions
#

# Returns the extension of the given filename
def file_ext(fn):
	return fn[fn.rfind(".")+1:len(fn)]

# Compile the given ".s" file
def handle_s(fn):
	return os.system(xgcc + " " + fn + " -o ./tmp/test_code.elf -g -Wl,-n,-Tinternal/script.ld,internal/crt0.o,-Map,tmp/test_code.map -nostdlib")

# Compile the given ".c" file
def handle_c(fn):
	return os.system(xgcc + " " + fn + " -o ./tmp/test_code.elf -g -Wl,-n,-Tinternal/script.ld,internal/crt0.o,-Map,tmp/test_code.map -nostdlib")

# Copy the given ".elf" file
def handle_elf(fn):
	return os.system("cp " + fn + " ./tmp/test_code.elf")

#
# Start of the script
#

# If there are arguments then use them as test codes
if len(sys.argv)>1:
	test_files = sys.argv[1:]
else:
	test_files = os.listdir("./test_codes")

test_files.sort()

# Create tmporary directory
os.system("mkdir -p tmp")

# Main loop on each code files
for test_file in test_files:
	if len(sys.argv)>1:
		test_path = test_file #if the file is specified then use it
		# and strip the now useless directory
		test_file = test_file[test_file.rfind("/")+1:len(test_file)]
	else:
		# if files come from the search in the ./test_codes/ directory,
		# then add the correct path
		test_path = "./test_codes/" + test_file

	if test_path[-1] == '~': #does not take car of files ending with ~
		continue
	if test_path[-3:] == 'swp': #does not take car of files ending with swp
		continue
	if os.path.isdir(test_path) == True: #does not take care of directories.
		continue

	print "Analysing ", test_file,
	sys.stdout.flush()

	# check that crt0.o has been compiled... and if not compile it
	if not os.path.isfile("internal/crt0.o") :
		os.system(xas + " internal/crt0.s -o internal/crt0.o")
	
	# Compile it
	if   file_ext(test_path) == "s":
		compile_ret = handle_s(test_path)
	elif   file_ext(test_path) == "S":
		compile_ret = handle_s(test_path)
	elif file_ext(test_path) == "c":
		compile_ret = handle_c(test_path)
	elif file_ext(test_path) == "elf":
		compile_ret = handle_elf(test_path)
	else:
		print "Don't know how to handle this test"
		continue
	print ".",
	sys.stdout.flush()

	if compile_ret != 0:
		print "Error! Can't generate ELF from ",test_file
		continue

	# Get the name of the test and the number of instruction to execute
	if file_ext(test_path) != "elf":
		file = open(test_path, "r")
		line = file.readline()
		m = re.search(r"\%\s*(.*)$", line)
		if m != None:
			print "Test \"" + m.group(1)+"\"",
			sys.stdout.flush()
		else:
			print "No test name! Use \"% Name\" in the first line."
			continue

		line = file.readline()
		m = re.search(r"\%\s*inst\s*:\s*(\d*)", line)
		inst = 100
		if m != None:
			inst = int(m.group(1))
			print "Execute",str(inst),"instructions.",
			sys.stdout.flush()
		else:
			print "No inst number! Use \"% inst: 42\" in the second line..."
			continue
	else:
		inst = nbInstForElfFiles # Number of instruction executed for an elf-test
		print "Execute",str(inst),"instructions.",
		sys.stdout.flush()

	# Calling the Harmless simulator
	os.system("sh -c \"./internal/trace.py ./tmp/test_code.elf "+str(inst)+" > ./tmp/trace_harmless_"+test_file+"\"")
	print ".",
	sys.stdout.flush()
	# Calling GDB Simulator
	os.system("cd internal && ./trace_sim_gdb.sh ../tmp/test_code.elf "+str(inst)+" > ../tmp/trace_gdb_"+test_file+" && cd ..")
	print ".",
	sys.stdout.flush()
	#Calling diff on the output of the two simulator
	ret_diff = os.system("sh -c \"diff ./tmp/trace_gdb_"+test_file+" ./tmp/trace_harmless_"+test_file+ " > ./tmp/diff_"+test_file+"\"")

	if ret_diff == 0:
		print "OK!"
	else:
		print "FAILED! "+test_file+" diff :"
		os.system("sh -c \"head ./tmp/diff_"+test_file+"\"")
		# Give a default command to analyse the diff... Change it to fit your
		# tools. This line can be modified in order to directly call such a tool
		print "Why not try \"vimdiff tmp/trace_gdb_"+test_file+" tmp/trace_harmless_"+test_file+"\"?"
		break

# End
