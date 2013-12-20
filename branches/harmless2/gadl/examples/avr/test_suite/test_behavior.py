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
# It has to be in ../AT90CAN128/

# Test codes must have "% name of the test" on the fist line
# and "% inst: number_of_instruction" on the second one.

# The scripts need the AVR_XTOOLS environment variable
# Exemple :
# If GCC is in /usr/local/CrossPack-AVR/bin/avr-gcc
# set AVR_XTOOLS to "/usr/local/CrossPack-AVR/bin/avr-"
# you may put
# "export AVR_XTOOLS=/usr/local/CrossPack-AVR/bin/avr-gcc"
# In your shell init script ~/.bashrc

# BUGS :
#	This script can't be moved around and have to be executed right here

import os
import re
import sys

# Number of instruction executed for an elf-test
nbInstForElfFiles = 10000

#make sure that the python simulator is built
sys.path.append("../AT90CAN128")
try:
	from AT90CAN128 import arch
except ImportError:
	print "the avr simulator does not seem to be generated."
	print "try to compile it using gadl (gadl ./avr.hadl)"
	print "then update if necessary the Makefile in the generated"
	print "directory (AT90CAN128) and compile the simulator using:"
	print "make python"
	print "Swig and libelf should be installed, see documentation."
	sys.exit()

#
# Check if the system is ready
#

try:
	xtools = os.environ["AVR_XTOOLS"]
except KeyError:
	print "The AVR_XTOOLS environnement variable doesn't exist... Please define it."
	sys.exit()

xgcc=xtools + "gcc"
xobjdump=xtools+"objdump"

# check the crosstools
if not os.path.isfile(xgcc) :
	print "Can't find Cross GCC... aborting"
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
	return os.system(xgcc + " " + fn + " -o ./tmp/test_code.elf -DF_CPU=16000000 -mmcu=at90can128")

# Compile the given ".c" file
def handle_c(fn):
	return os.system(xgcc + " " + fn + " -o ./tmp/test_code.elf -DF_CPU=16000000 -mmcu=at90can128")

# Copy the given ".elf" file
def handle_elf(fn):
	return os.system("cp " + fn + " ./tmp/test_code.elf")

# Copy the given ".H86" file
def handle_h86(fn):
	return os.system("cp " + fn + " ./tmp/test_code.elf") #even if it's not an elf file...

#
# Start of the script
#

# If there are arguments then use them as test codes
if len(sys.argv)>1:
	test_files = sys.argv[1::(len(sys.argv)-1)]
else:
	print "no argument given, using all files in ./test_codes"
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
	if os.path.isdir(test_path) == True: #does not take car of directories.
		continue

	print "Analysing", test_file+"...",

	# Compile it
	if   file_ext(test_path) == "s":
		compile_ret = handle_s(test_path)
	elif file_ext(test_path) == "c":
		compile_ret = handle_c(test_path)
	elif file_ext(test_path) == "elf":
		compile_ret = handle_elf(test_path)
	elif file_ext(test_path) == "h86":
		compile_ret = handle_h86(test_path)
	else:
		print "Don't know how to handle this test"
		continue

	if compile_ret != 0:
		print "Error! Can't generate ELF from ",test_file
		continue

	# Get the name of the test and the number of instruction to execute
	if file_ext(test_path) != "elf" and file_ext(test_path) != "h86":
		file = open(test_path, "r")
		line = file.readline()
		m = re.search(r"\%\s*(.*)$", line)
		if m != None:
			print "Test \"" + m.group(1)+"\"",
		else:
			print "No test name! Use \"% Name\" in the first line."
			continue

		line = file.readline()
		m = re.search(r"\%\s*inst\s*:\s*(\d*)", line)
		inst = 100
		if m != None:
			inst = int(m.group(1))
			print "Execute",str(inst),"instructions.",
		else:
			print "No inst number! Use \"% inst: 42\" in the second line..."
			continue
	else:
		inst = nbInstForElfFiles # Number of instruction executed for an elf-test
		print "Execute",str(inst),"instructions.",

	# Calling the Harmless simulator
	os.system("sh -c \"./internal/trace.py ./tmp/test_code.elf "+str(inst)+" > ./tmp/trace_harmless_"+test_file+"\"")
	# Calling GDB Simulator
	os.system("sh -c \"./internal/trace_sim_gdb.sh ./tmp/test_code.elf "+str(inst)+" > ./tmp/trace_gdb_"+test_file+"\" 2>/dev/null") #remove an ugly 'killall' in stderr.

	#Calling diff on the output of the two simulator
	ret_diff = os.system("sh -c \"diff ./tmp/trace_gdb_"+test_file+" ./tmp/trace_harmless_"+test_file+ " > ./tmp/diff_"+test_file+"\"")

	if ret_diff == 0:
		print "OK!"
	else:
		print "FAIL! "+test_file+" diff :"
		os.system("sh -c \"head ./tmp/diff_"+test_file+"\"")
		# Give a default command to analyse the diff... Change it to fit your
		# tools. This line can be modified in order to directly call such a tool
		print "Why not try \"vimdiff tmp/trace_gdb_"+test_file+" tmp/trace_harmless_"+test_file+"\"?"
		break

# End
