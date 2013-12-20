#!/usr/bin/python
import sys
import os
import time	# Useful to mesure execution timing for small amount of code

def compileTest(files, outputName):
	''' This function compile miBench exec. 
	First  arg is a list of source files
	Second arg is the output binary filename WITHOUT extension.
	'''
	try:
		xtools = os.environ["ARM_XTOOLS"]
	except KeyError:
		print "The ARM_XTOOLS environnement variable doesn't exist... Please define it."
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
	if not os.path.isfile("../internal/crt0.o") :
		os.system(xas + " ../internal/crt0-for-user-program.s -o ../internal/crt0.o -mfloat-abi=soft")
	#compile the file.	
	compileStr = xtools+"gcc -O3 -o "+outputName+".elf "
	for f in files:
		compileStr += f+" "
	print "compile file: "+outputName+".elf"
	compileStr += "internal/stub.c -g -lm -Wl,-n,-T./internal/script.ld,../internal/crt0.o,-Map,"+outputName+".map"
	print compileStr
	os.system(compileStr)

def printResult(resultDict):
	''' print results of the run of a benchmark.
	the parameter is a dictionnary containing full information
	'''
	try:
		deltaT = resultDict['timeEnd'] - resultDict['timeStart']
		print "time required for "+resultDict['name']+" : ", deltaT , "s"
		deltaInst = resultDict['nbInstEnd'] - resultDict['nbInstStart']
		print "nb instructions             : ", deltaInst
		deltaCycle = resultDict['nbCyclesEnd'] - resultDict['nbCyclesStart']
		print "nb cycle                    : ", deltaCycle
		print "simulator throughput        : ", deltaInst/(1000*deltaT), " Kinsts/s"
		print "simulator throughput        : ", deltaCycle/(1000*deltaT), " Kcycles/s"
	except KeyError, key:
		print "Internal Error: the key %s is not found to print results." %(key)
	

def prepareSimu(fileName):
	''' This function is called at the beginning of the simulation
	to set up the simulator (read code file, add breakpoint at end
	of scenario, ...
	It returns a valid instance of the simulator.
	'''
	# Looks in arm_dbg directory to find the processor arch
	sys.path.append("../../arm_dbg")
	from arm_dbg import arch
	simu=arch()
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

def runBench(dic):
	''' run a benchmark. It :
	* compiles the bench (if necessary), 
	* prepares the simulator
	* measure execution time 
	* prints results.
	'''
	if not os.path.exists(dic['exe']+".elf"):
		compileTest(dic['src'], dic['exe'])
	simu = prepareSimu(dic['exe']+".elf")
	if 'spec' in dic:
		dic['spec'](simu)
	#run!
	resultDict = mainSimu(simu, dic['exe']+".elf")
	printResult(resultDict)	

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

def main(argv=None):
    if argv is None:
        argv = sys.argv
	runBench({'exe': "./internal/bin/qsortSmall", 'src':['qsort/qsort_small.c'] , 'spec':qsortSpecific})
	runBench({'exe': "./internal/bin/qsortLarge", 'src':['qsort/qsort_large.c'] , 'spec':qsortSpecific})
	runBench({'exe': "./internal/bin/basicMathSmall", 
		'src':['basicmath/basicmath_small.c','basicmath/rad2deg.c','basicmath/cubic.c','basicmath/isqrt.c']})
	runBench({'exe': "./internal/bin/basicMathLarge", 
		'src':['basicmath/basicmath_large.c','basicmath/rad2deg.c','basicmath/cubic.c','basicmath/isqrt.c']})
	runBench({'exe': "./internal/bin/susanSmall", 'src':['susan/susanSmall.c'] , 'spec':susanSpecific})
	runBench({'exe': "./internal/bin/susanLarge", 'src':['susan/susanLarge.c'] , 'spec':susanSpecific})
if __name__ == "__main__":
    sys.exit(main())

