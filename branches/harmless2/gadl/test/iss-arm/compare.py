#!/usr/bin/python

#arguments:
# * the simulator path
# * the model name (-> the python library name)
#
#TODO: should be called from this location: use of relative paths.

import os
import re
import sys
sys.path.append('./internal')
from common	import * #internals.

def run(sim, files):

	# If there are arguments then use them as test codes
	if files:
		test_files = files
	else:
		test_files = os.listdir("./test_codes")
	
	test_files.sort()
	
	# Check for build dir.
	if not os.path.isdir(buildDir):
		print "test codes are not built, and GDB simulator traces cannot be found."
		print "please install first a cross-compiler and run ./build.py to generate gdb traces."
		print "Abording test."
		sys.exit()
	# Main loop on each code files
	for test_file in test_files:
		if files:
			test_path = test_file #if the file is specified then use it
			# and strip the now useless directory
			test_file = test_file[test_file.rfind("/")+1:len(test_file)]
		else:
			# if files come from the search in the ./test_codes/ directory,
			# then add the correct path
			test_path = "./test_codes/" + test_file
	
		# only take care of files with a cfg file.
		if not file_ext(test_path) == "cfg":
			continue
	
		print "Analysing ", test_file,
		sys.stdout.flush()
	
		# Get the name of the test and the number of instruction to execute
		cfg=file_without_ext(test_path)+'.cfg'
		name,inst = readCFGFile(cfg,True)
	
		sys.stdout.flush()
		# Calling the Harmless simulator
		elf=getElfFileName(test_path)
		outputFileH = buildDir+"trace_"+file_without_ext(test_file)+"_harmless"
		sys.path.append('./internal')
		import traceHarmless
		traceHarmless.traceHarmless(sim,elf,inst,outputFileH)
		print ".",
		sys.stdout.flush()
		#Calling diff on the output of the two simulator
		outputFileG = buildDir+"trace_"+file_without_ext(test_file)+"_gdb"
		outputDiff = buildDir+"diff_"+file_without_ext(test_file)
		diff_cmd = "sh -c \"diff "+outputFileG+" "+outputFileH+" > "+outputDiff+"\""
		ret_diff = os.system(diff_cmd)
		if ret_diff == 0:
			print "OK!"
		else:
			print "FAILED! "+test_file+" diff :"
			os.system("sh -c \"head "+outputDiff+"\"")
			# Give a default command to analyse the diff... Change it to fit your
			# tools. This line can be modified in order to directly call such a tool
			print "Why not try \"vimdiff "+outputFileG+" "+outputFileH+"\"?"
			return False
	return True

def usage():
	print "usage: python compare.py -s path -n name [-h] files"
	print "       -h|--help: This help"
	print "       -p|--simPath xxx: simulator path"
	print "       -n|--simName xxx: simulator name"
	print "       files. Files to test (default: use all files in test_codes/)"

import getopt
def handleCLIOptions(argv):
	simPath = "NoPath"
	simName = "NoName"
	files = None
	try:
		opts, files = getopt.getopt(argv, "htp:n:", ["help","time","simPath","simName"])
	except getopt.GetoptError:
		usage()
		sys.exit(2)
	for opt, arg in opts:
		if opt in ("-h", "--help"):
			usage()
			sys.exit(0)
		elif opt in ("-p", "--simPath"):
			simPath = arg
		elif opt in ("-n", "--simName"):
			simName = arg
	#Ok. Try to load the simulator lib.
	if os.path.isdir(simPath):
		sys.path.append(simPath)
	else:
		print "Invalid path for simulator: "+simPath
		usage()
		sys.exit(2)
	try:
		sim=__import__(simName)
	except ImportError:
		print "the "+simName+" simulator does not seem to be generated "
		print "(in "+simPath+")"
		usage()
		sys.exit(2)
	return sim, files

if __name__ == '__main__':
	sim,files = handleCLIOptions(sys.argv[1:])
	if not run(sim,files):
		sys.exit(1)
