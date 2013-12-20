## PROJECT : Stack / Task observation
## NAME : Class for executig one simulation on an elf file
## DESCRIPTION :
## Read .stack option file associated to binary elf file and
## Simulate for one binary elf file and mesure time of simulation
##

## FILES PARSING ##
import ConfigParser
import string

## TIME EVALUATION ##
import time	# Usefull to mesure execution timing for small amount of code
import sys

# PARAMETERS
CONFIG_STACK_STRING="stack"				# A stack declaration in "name_of_program.stack" have to contain "stack"
CONFIG_EXCLUSION_STRING="exclusion"		# A exclusion function declaration in "name_of_program.stack" have to contain "exclusion"

class Simulator:
	#"""Provide simplified way to call simulator"""
	def __init__(self,simulatorPath,binPath,modelName,nbInstrSimulation,taskMonitor,stackMonitor):
		sys.path.append(simulatorPath)
		self.m_binPath=binPath
		self.m_simPath=simulatorPath
		self.m_modelName=modelName
		self.m_nbInstrSimulation=nbInstrSimulation
		self.m_taskMonitor=taskMonitor
		self.m_stackMonitor=stackMonitor
		
		#from modelName import arch ## will not work need to use import function primitive
		from powerpc import arch	## Model NAME Have to be change Here !!!!
		
		self.m_arch=arch()
		# to correct using paramet string
		self.m_arch.readCodeFile(binPath)
		
		if taskMonitor:			    ## Model NALE Have to be change Here !!!!
			from powerpc	import stackSpyController
			self.m_stackCtrl=self.m_arch.getStackSpyController()

	
	# Actually lauch simulation
	def executeSimulation(self):
		t1=time.clock()
		self.m_arch.execInst(self.m_nbInstrSimulation)
		t2=time.clock()
		return (t2-t1)
			
	# Provide ability to print result of simulation on cout
	def printResults(self):
		if self.m_taskMonitor:
			print "-- Analyse des changements de taches et surveillance de pile --"
			print ">> Task List"
			self.m_stackCtrl.printTaskList();
			print ">> Switch List"
			self.m_stackCtrl.printControllerSwitchList()
			self.m_stackCtrl.writeTraceT3("trace.txt");	
	
	## PARSING TEST ##
	def contains(self,theString, theQueryValue):
	  return theString.find(theQueryValue) > -1
	
	# READ .stack configuration file
	def configureStackFromFile(self,filename):
		#Debug
		#print "FILENAME :"+filename
		#print "OPTION Stack Moninor",self.m_taskMonitor
		# Exec
		if(self.m_taskMonitor) :
			print "Configure Stack Monitor"
			stackList = ConfigParser.ConfigParser()
			stackList.read(filename)
		
			# DEBUG
			#print stackList.sections()
			
			for section in stackList.sections():
			
				if self.contains(section,CONFIG_STACK_STRING):
					print "STACK DECLARATION"
					print  "name : ",stackList.get(section, "name")
					print "mainFunction : ", stackList.get(section, "mainFunction")
					print  "size : ", stackList.getint(section, "sizeOfStack")
					print
					self.m_stackCtrl.addTaskToMonitor(stackList.get(section, "name"),stackList.get(section, "mainFunction"),stackList.getint(section, "sizeOfStack"));
					
				elif self.contains(section,CONFIG_EXCLUSION_STRING) and self.m_stackMonitor :
					print "EXCLUSION FUNCTION"
					print "name : ",stackList.get(section, "name")
					print
					self.m_stackCtrl.setExclusionOnSystFunction(stackList.get(section, "name"));
	
