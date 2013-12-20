#!/usr/bin/python
import sys
import os
import time	# Useful to mesure execution timing for small amount of code

def file_without_ext(fn):
	return fn[0:fn.rfind(".")]

#name (with the .elf)
def getElfFile(name,option):
	return "internal/"+option["target"]+"/bin/"+name+".elf"

def compileTest(files, outputName, option):
	''' This function compile miBench exec. 
	First  arg is a list of source files
	Second arg is the output binary filename WITHOUT extension.
	'''
	#check target.
	target = option['target']
	if target == "arm":
		crossCompilerVarName = "ARM_XTOOLS"
		asflags = "-mfloat-abi=soft"
		cflags = "-g -nostdlib -mfloat-abi=soft -lm -lc -lgcc" #both c- and ld-flags.
	elif target == "ppc":
		crossCompilerVarName = "PPC_XTOOLS"
		asflags = ""
		cflags = "-g -lm -msoft-float" #both c- and ld-flags.
	else:
		print "error: unknown target : ",target
		sys.exit(1)
	#go!
	try:
		xtools = os.environ[crossCompilerVarName]
	except KeyError:
		print "The cross compiler",crossCompilerVarName,"environnement variable doesn't exist... Please define it."
		sys.exit()
	xgcc=xtools + "gcc"
	xas= xtools + "as"
	# check the crosstools
	if not os.path.isfile(xgcc) :
		print "Can't find Cross GCC... aborting"
		sys.exit()
	if not os.path.isfile(xas) :
		print "Can't find Cross asm... aborting"
		sys.exit()
	# check that crt0.o has been compiled... and if not compile it
	tDir="./internal/"+target+"/" #targetDir
	if not os.path.isfile(tDir+"crt0.o") :
		os.system(xas + " "+tDir+"crt0.s -o "+tDir+"crt0.o "+asflags)
	#compile the file.
	output = getElfFile(outputName,option)
	compileStr = xtools+"gcc -O3 -o "+output+" "
	for f in files:
		compileStr += f+" "
	compileStr += tDir+"stub.c "+cflags+" -Wl,-n,-T"+tDir+"script.ld,"+tDir+"crt0.o,-Map,"+file_without_ext(output)+".map"
	os.system(compileStr)

def printResult(resultDict, option):
	''' print results of the run of a benchmark.
	the parameter is a dictionnary containing full information
	'''
	try:
		print "bench result for "+resultDict['name']
		deltaInst = resultDict['nbInstEnd'] - resultDict['nbInstStart']
		print "nb instructions      : ", deltaInst
		deltaCycle = resultDict['nbCyclesEnd'] - resultDict['nbCyclesStart']
		print "nb cycle             : ", deltaCycle
		if option['time']:
			deltaT = resultDict['timeEnd'] - resultDict['timeStart']
			print "computation time     : ", deltaT , "s"
			print "simulator throughput : ", deltaInst/(1000*deltaT), " Kinsts/s"
			print "simulator throughput : ", deltaCycle/(1000*deltaT), " Kcycles/s"
	except KeyError, key:
		print "Internal Error: the key %s is not found to print results." %(key)
	

def prepareSimu(sim,fileName):
	''' This function is called at the beginning of the simulation
	to set up the simulator (read code file, add breakpoint at end
	of scenario, ...
	It returns a valid instance of the simulator.
	'''
#	# Looks in arm_dbg directory to find the processor arch
#	sys.path.append("../tmp/simulators/arm_dbg")
#	from arm_dbg import arch
	simu=sim.arch()
	simu.readCodeFile(fileName)
	simu.useIOStubs()
	simu.addBreakpoint("shouldNotHappen")
	return simu

def mainSimu(simu, filename):
	''' main simulation function.
	All things are set previously, so this function simply
	measure the execution time.
	It returns a dictionnary containing timings and nb insts/cycles 
	simulated
	'''
	resultDict = {'name':filename}
	resultDict['nbInstStart']  = simu.getNBInstructions()
	resultDict['nbCyclesStart']= simu.getNBCycles()
	resultDict['timeStart']    =time.time()
	#run the bench
	simu.execInst(1000000000)
	resultDict['timeEnd']    =time.time()
	resultDict['nbInstEnd']  = simu.getNBInstructions()
	resultDict['nbCyclesEnd']= simu.getNBCycles()
	return resultDict

def runBench(dic, option):
	''' run a benchmark. It :
	* compiles the bench (if necessary), 
	* prepares the simulator
	* measure execution time 
	* prints results.
	'''
	exe = getElfFile(dic['exe'],option)
	if not os.path.exists(exe):
		compileTest(dic['src'], dic['exe'],option)
	simu = prepareSimu(option['sim'],exe)
	if 'spec' in dic:
		dic['spec'](simu)
	#run!
	resultDict = mainSimu(simu, exe)
	printResult(resultDict, option)	

def qsortSpecific(simu):
	''' specific simulation script for QSort benchs.
	'''
	#run until load is complete 
	simu.addBreakpoint("qsort") 
	simu.execInst(100000000)
	#measure will end just before output printing.
	simu.addBreakpoint("printf")

def susanSpecific(simu):
	''' specific simulation script for Susan benchs.
	'''
	#run until load is complete 
	simu.addBreakpoint("setup_brightness_lut") 
	simu.execInst(100000000)
	#measure will end just before writing to file.
	simu.addBreakpoint("put_image")

def usage():
	print "miBench test suite for Harmless"
	print "adapted automotive tests from http://www.eecs.umich.edu/mibench/"
	print "usage: python mibench.py -s path -n name [-t] [-h]"
	print "       -h|--help: This help"
	print "       -t|--time: print computation time for each test (default no)"
	print "       -p|--simPath xxx: simulator path"
	print "       -n|--simName xxx: simulator name"
	print "       -e|--exec xxx: exec target (either arm or ppc)"

import getopt
def handleCLIOptions(argv):
	printTime = False #default
	simPath = "NoPath"
	simName = "NoName"
	execTarget = "arm"
	try:
		opts, args = getopt.getopt(argv, "htp:n:e:", ["help","time","simPath=","simName=","exec="])
	except getopt.GetoptError:
		usage()
		sys.exit(2)
	for opt, arg in opts:
		if opt in ("-h", "--help"):
			usage()
			sys.exit(0)
		elif opt in ("-t", "--time"):
			printTime = True
		elif opt in ("-p", "--simPath"):
			simPath = arg
		elif opt in ("-n", "--simName"):
			simName = arg
		elif opt in ("-e", "--exec"):
			execTarget = arg
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
	option = {'time': printTime, 'sim':sim,'target':execTarget}
	return option

def main(argv=None):
    if argv is None:
        argv = sys.argv
	option = handleCLIOptions(argv[1:])
	runBench({'exe': "qsortSmall", 'src':['qsort/qsort_small.c'] , 'spec':qsortSpecific},option)
	runBench({'exe': "qsortLarge", 'src':['qsort/qsort_large.c'] , 'spec':qsortSpecific},option)
	runBench({'exe': "basicMathSmall", 
		'src':['basicmath/basicmath_small.c','basicmath/rad2deg.c','basicmath/cubic.c','basicmath/isqrt.c']},option)
	runBench({'exe': "basicMathLarge", 
		'src':['basicmath/basicmath_large.c','basicmath/rad2deg.c','basicmath/cubic.c','basicmath/isqrt.c']},option)
	runBench({'exe': "susanSmall", 'src':['susan/susanSmall.c'] , 'spec':susanSpecific},option)
	runBench({'exe': "susanLarge", 'src':['susan/susanLarge.c'] , 'spec':susanSpecific},option)
if __name__ == "__main__":
    sys.exit(main())

