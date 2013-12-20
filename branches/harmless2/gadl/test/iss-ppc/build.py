#!/usr/bin/python

#This script is used to 
# -> compile .elf examples from source files (C and asm).
# -> output the GDB trace for these files.

# This script requires a cross-compiler (gcc), but does not require any Harmless simulator.
# The other script (compare.py) does not require any cross-compiler but needs the Harmless simulator,
# and obvioulsy files generated from this script.

# The scripts need the PPC_XTOOLS environnement variable
# Example :
# If GCC is in ~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-gcc
# set PPC_XTOOLS to "~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-"
# you may put
# "export PPC_XTOOLS=~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-"
# In your shell init script ~/.bashrc

import os
import re
import sys
sys.path.append('internal')
from common	import * #internals.

try:
	xtools = os.environ["PPC_XTOOLS"]
except KeyError:
	print "The PPC_XTOOLS environnement variable doesn't exist...",
	print "Please define it: export PPC_XTOOLS=path/to/cross-compiler/powerpc-elf-"
	sys.exit()

xgcc=xtools + "gcc"
xas= xtools + "as"
buildDir="build/" #dir where generated files are stored (.elf, .map)

# check the crosstools
if not os.path.isfile(xgcc) :
	print "Can't find Cross GCC... aborting"
	sys.exit()

if not os.path.isfile(xas) :
	print "Can't find Cross assembler... aborting"
	sys.exit()

# Compile the given ".s" file
def handle_s(fn):
	elf=buildFileName(fn,'elf')
	mapFile=buildFileName(fn,'map')
	return os.system(xgcc + " " + fn + " -o "+elf+" -g -Wl,-n,-Tinternal/script.ld,"+buildDir+"crt0.o,-Map,"+mapFile+" -nostdlib")

# Compile the given ".c" file
def handle_c(fn):
	elf=buildFileName(fn,'elf')
	mapFile=buildFileName(fn,'map')
	return os.system(xgcc + " " + fn + " -o "+elf+" -g -Wl,-n,-Tinternal/script.ld,"+buildDir+"crt0.o,-Map,"+mapFile+" -nostdlib")

#
# Start of the script
#

# If there are arguments then use them as test codes
if len(sys.argv)>1:
	test_files = sys.argv[1:]
else:
	test_files = os.listdir("./test_codes")

test_files.sort()

# Create temporary directory
os.system("mkdir -p "+buildDir)

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

	if test_path[-1] == '~': #does not take care of files ending with ~
		continue
	if test_path[-3:] == 'swp': #does not take care of files ending with swp
		continue
	if test_path[-3:] == 'cfg': #does not take care of config files.
		continue
	if os.path.isdir(test_path) == True: #does not take care of directories.
		continue

	print "Analysing ", test_file,
	sys.stdout.flush()

	# check that crt0.o has been compiled... and if not compile it
	if not os.path.isfile(buildDir+"crt0.o") :
		os.system(xas + " internal/crt0.s -o "+buildDir+"crt0.o")
	
	# Compile it
	if   file_ext(test_path) == "s":
		compile_ret = handle_s(test_path)
	elif   file_ext(test_path) == "S":
		compile_ret = handle_s(test_path)
	elif file_ext(test_path) == "c":
		compile_ret = handle_c(test_path)
	elif file_ext(test_path) == "elf":
		pass
	else:
		print "Don't know how to handle this test"
		continue
	print ".",
	sys.stdout.flush()

	if compile_ret != 0:
		print "Error! Can't generate ELF from ",test_file
		continue

	# Get the name of the test and the number of instruction to execute
	cfg=file_without_ext(test_path)+'.cfg'
	name,inst = readCFGFile(cfg,True)

	sys.stdout.flush()
	# Calling GDB Simulator
	elf=getElfFileName(test_path)
	os.system("ln -fs ../"+elf+" "+buildDir+"__gdb.elf") #gdb script uses this filename.
	outputFile = buildDir+"trace_"+file_without_ext(test_file)+"_gdb"
	#print "cd internal && ./trace_sim_gdb.sh ../"+elf+" "+str(inst)+" > ../"+outputFile+" && cd .."
	os.system("cd internal && ./trace_sim_gdb.sh "+str(inst)+" > ../"+outputFile+" && cd ..")
	print "."
	sys.stdout.flush()
# End
