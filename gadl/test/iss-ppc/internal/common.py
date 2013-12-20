#!/usr/bin/python

import os
import re
import sys

buildDir="build/" #dir where generated files are stored (.elf, .map)

# Returns the extension of the given filename
def file_ext(fn):
	return fn[fn.rfind(".")+1:len(fn)]

def file_without_ext(fn):
	return fn[0:fn.rfind(".")]

def buildFileName(fn,ext):
	f = buildDir+file_without_ext(os.path.basename(fn))+'.'+ext
	return f

def getElfFileName(test_path):
	#first test in the build dir (.c and .s files):
	result = buildFileName(test_path,'elf')
	if not os.path.isfile(result):
		result = file_without_ext(test_path)+'.elf' #binary files are not moved.
	return result

def readCFGFile(cfgFile,verbose):
	name = "no test name"
	inst = 100
	try:
		file = open(cfgFile, "r")
	except IOError:
		print 'cannot open config file ', cfgFile, ' -> comparison set to ', inst, 'instructions'
		return name,inst
	line = file.readline()
	m = re.search(r"\%\s*(.*)$", line)
	if m != None:
		name =  m.group(1)
	else:
		if verbose:
			print "No test name! Use \"% Name\" in the first line of the cfg file:"+cfgFile

	line = file.readline()
	m = re.search(r"\%\s*inst\s*:\s*(\d*)", line)
	if m != None:
		inst = int(m.group(1))
	else:
		if verbose:
			print "No inst number! Use \"% inst: 42\" in the second line..."
	return name,inst
