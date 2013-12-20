#!/usr/bin/python
import ConfigParser
import os,sys
import subprocess
import shlex
import shutil
###############################################################################
# regression tests for Harmless generated simulators.
###############################################################################
# This script:
# -> search a .test configuration file in each subdir, or use subdirs in 
#    command line arguments.
# -> extract configuration from .test file (see readConfigFile function)
# -> search all the simulator configurations, in order to build simulators only
#    once.
# -> build simulator sources from gadl (rebuild gadl if required) 
#    - tmp/simulators -> check compilation OK.
# -> build simulator (python, gdb or standalone)
# For local files (declared with 'locals' instead of 'files')
# -> simulator sources are generated in the directory of the .test file.
# -> tests are applied in the same way.
# -> if the local file does not compile, generate an error log.
#	-> if there is already one, compare it with previous version.
#	   This may be a normal test (error detection)
# -> if there is an error in gadl compilation, sources are not compiled (no test)
# depending on the test required (in .test file)
#  * do nothing (just check that build is OK
#  * [compare] section -> run the python script and compare output with the 
#                         awaited one. If the comparison file does not exist,
#                         it is created.
#                         script working dir is the script dir.
#						  arguments given: -n simName -p simPath
#  * [custom] section  -> just run the python script, and get the return value 
#                         script working dir is the script dir.
#						  arguments given: -n simName -p simPath
#                         A return value of 0 is OK.
###############################################################################
# TODO:
# * test GDB server simulators.
# * in compare files: allow different targets associated with different compare
#                     files
###############################################################################



def readConfigFile(filename):
	""" This function reads a config file '.test', 
	    and set the values in the returned config dict.
		Keys in the config dict:
		* files : list of files to use (.hadl)
		* models : models related to files (same order than files)
		* targets : either gdb, standalone or python
		* stubs : true/false -> use of host file system.
		* pipelineTrace : true/false -> debug pipeline trace (much slower)
		* define : list of strings that are passed to the Makefile (separated by '+')
		* compareScript : a script to compare data output
		* compareFiles : reference output that will be compared to the current one.
		*
	"""
	configFile = ConfigParser.ConfigParser()
	configFile.read(filename)
	files=[] #target files.
	localList=[] #local target files.
	models=[]
	targets=[]
	stubs=True
	pipelineTrace=False
	define=[]
	compareScript=[]
	compareFiles=[]
	customScript=[]
	for section in configFile.sections():
		if(section == 'model'):
			try:
				models=configFile.get(section, "models").split(':')
			except:
				print "In the [model] section, you should define:"
				print " * a list of model files    : files=file1.hadl:file2.hadl..."
				print " * or a list of local model : locals=file1.hadl:file2.hadl..."
				print " * a list of model names (associated to files): models=model1:model2..."
			try:
				files=configFile.get(section, "files").split(':')
			except ConfigParser.NoOptionError:
				pass #error detected after.
			try:
				localList=configFile.get(section, "locals").split(':')
			except ConfigParser.NoOptionError:
				pass #error detected after.

		if(section == 'build'):
			try:
				targets=configFile.get(section, "target").split(':')
			except ConfigParser.NoOptionError:
				print "no target defined in file ",filename,"."
				print "Use 'standalone' as the default one"
				targets = ['standalone']
			try:
				stubs=configFile.getboolean(section,"stubs")
			except ConfigParser.NoOptionError:
				pass
			try:
				pipelineTrace=configFile.getboolean(section,"pipelineTrace")
			except ConfigParser.NoOptionError:
				pass
			try:
				define=configFile.get(section,"define").split(' ')
			except ConfigParser.NoOptionError:
				pass
		if(section == 'compare'):
			try:
				compareScript=configFile.get(section, "script").split(':')
				compareFiles=configFile.get(section, "files").split(':')
			except ConfigParser.NoOptionError:
				print "in the [compare] section, you should define:"
				print " * a list of scripts: script=run1.py:run2.py.."
				print " * a list of result files: file=result1.log:result2.log"
			if(len(compareScript) != len(compareFiles)):
				print "Configure File error: not as many scripts than result files!!"
		if(section == 'custom'):
			try:
				customScript=configFile.get(section, "script").split(':')
			except ConfigParser.NoOptionError:
				pass


	config = {}
	config['filename']=filename
	#model
	config['files']=files
	config['locals']=localList
	config['models']=models
	if len(config['files']) == 0 and len(config['locals']) == 0:
		print "In the [model] section, you should define:"
		print " * a list of model files    : files=file1.hadl:file2.hadl..."
		print " * or a list of local model : locals=file1.hadl:file2.hadl..."
		print " * a list of model names (associated to files): models=model1:model2..."
	if len(config['files']) != 0 and len(config['locals']) != 0:
		print "In the [model] section, you should define:"
		print "either a local file (using 'locals=')"
		print " *OR*  a list of files in example/ (using 'files=')"
		config['files'] = []
	
	#build
	config['targets']=targets
	config['stubs']=stubs
	config['pipelineTrace']=pipelineTrace
	config['define']=define
	#compare
	config['compareScript']=compareScript
	config['compareFiles']=compareFiles
	#custom
	config['customScript']=customScript
	return config

def getFileHADL(scriptWorkingDir,filename,isLocal=False):
	fileAbs = None
	if isLocal:
		fileAbs=os.path.join(scriptWorkingDir,filename)
	else:
		gadlDir=gadlDirectory(scriptWorkingDir)
		fileAbs=os.path.join(gadlDir+'/examples',filename)
	return fileAbs
	
def gadlDirectory(scriptWorkingDir):
	return os.path.join(scriptWorkingDir,'..')

def generatedSimulatorSrcDirectory(scriptWorkingDir):
	return os.path.join(scriptWorkingDir,'tmp/simulators')

def logDirectory(scriptWorkingDir):
	return os.path.join(scriptWorkingDir,'tmp/log')

def compareFile(comparePath,logFileName,nbDoneFail,nbDoneUncon):
	if os.path.exists(comparePath):
		#File exists, make a diff.
		ret_diff = os.system("diff "+comparePath+" "+logFileName+">/dev/null")
		if ret_diff != 0:
			print "*** ERROR ***: Test script differs!!!"
			print "*** script initial file  : ",comparePath
			print "*** script current output: ",logFileName
			nbDoneFail = nbDoneFail + 1
	else:
		#File does not exists. Create it.
		print "*** -> compare file",comparePath,"does not exists. Create it."
		#print "copy",logFileName,"->",comparePath
		shutil.copyfile(logFileName,comparePath)
		nbDoneUncon = nbDoneUncon + 1
	return nbDoneFail,nbDoneUncon

def buildSimSources(scriptWorkingDir,configList):
	""" This function explore the list of config, and
	generate required simulator sources, using gadl.
	Each simulator is only build once (even if it is referenced
	many times in config files).
	Simulator sources are generated in directory 
	generatedSimulatorSrcDirectory().
	-> exits if there is a compilation error of description in example/
	-> return a dict of entries (for local files). Each entry is a bool (compilOK)
	"""
	#first check that gadl is built.
	gadlDir=gadlDirectory(scriptWorkingDir)
	try:
		subprocess.call([gadlDir+'/gadl','--version']) #test gadl binary
	except OSError:
		#there was a problem.
		print "I did not found a gadl compiler in:",gadlDir+'/gadl'
		print "I first have to build gadl from sources.."
		harmlessRoot=os.path.join(scriptWorkingDir,'../..')
		subprocess.call([harmlessRoot+'/buildHarmless.py'])
	#Eliminate files that appear several times in configs (for global files in example/
	fileSet=set()
	for config in configList:
		fileSet |= set(config['files'])
	#set a build and log dir.
	simDir=generatedSimulatorSrcDirectory(scriptWorkingDir)
	os.system("mkdir -p "+simDir)
	logDir=logDirectory(scriptWorkingDir)
	os.system("mkdir -p "+logDir)
	processList = []
	FDList = []
	errorFileNameList = []
	errorLogFileNameList = []
	processListLocal = []
	fileNameList = []
	#then build simulator sources.
	print "there are ",len(fileSet)," simulator sources from example/ to generate (gadl)."
	for file in fileSet: #specific for models in examples/
		fileAbs=getFileHADL(scriptWorkingDir,file,False)
		#os.path.join(gadlDir+'/examples',file)
		print '\tbuild simulator from ',file,'.'
		processList.append(subprocess.Popen([gadlDir+'/gadl',fileAbs],cwd=simDir))
	nbLocals = 0
	for config in configList: #local files are generated in the script directory.
		for file in config['locals']:
			nbLocals = nbLocals+1	
	print "there are ",nbLocals," simulator sources for local tests to generate (gadl)."
	currentLocal = 0
	for config in configList: #local files are generated in the script directory.
		scriptDir = os.path.dirname(config['filename'])			
		for file in config['locals']:
			fileName = os.path.join(scriptDir,file)
			fileAbs=getFileHADL(scriptWorkingDir,fileName,True)
			print "\tbuild simulator from local model (in script dir)",fileName
			logFileName = os.path.join(logDirectory(scriptWorkingDir),"gadl_"+str(currentLocal))			
			FD=open(logFileName,"w")
			FDList.append(FD)
			fileNameList.append(fileName)
			errorFileNameList.append(fileName+".buildLog")
			errorLogFileNameList.append(logFileName)
			processListLocal.append(subprocess.Popen([gadlDir+'/gadl',fileAbs],cwd=scriptDir,stdout=FD,stderr=subprocess.STDOUT))
			currentLocal = currentLocal + 1
	
	# and then wait for end of build.
	for process,file in zip(processList,fileSet): #globol files (in example/) should not generate an error.
		process.wait()
		if(process.returncode): #test gadl binary
			#there was an error
			print "There was an error when generating sources from ",file
			sys.exit(1)
	buildLocalsOK = {}
	for process,FD,errorLog,logFileName,filename in zip(processListLocal,FDList,errorFileNameList,errorLogFileNameList,fileNameList):
		process.wait()
		FD.close()
		if(process.returncode): #test gadl binary
			#there was an error
			nbDoneFail,nbDoneUncon = compareFile(errorLog,logFileName,0,0)
			if nbDoneFail == 0:
				print "There was a 'normal' error when generating sources, see ",errorLog
		buildLocalsOK[filename] = (process.returncode != 0)
	return buildLocalsOK

def launchTestsOnTarget(scriptWorkingDir,configList,modelName,target,simDir):
	""" This function is called when a config is done and the simulator binary
	has been built. It should perform required tests on target.
	"""
	print 'test... for',modelName,'on target',target
	nbDone = 0
	nbDoneFail = 0  #script failed.
	nbDoneUncon = 0 #script is unconclusive (regeneration)
	processList = [] #list of processes (exec in //)
	FDList = [] #file descriptors related to script output.
	compareFileList = []
	logFileNameList = []
	#start each script (comparison based).
	for config in configList:
		#stops when the shortest ends.
		for script,compareFiles in zip(config['compareScript'],config['compareFiles']):
			#script may have arguments.
			scriptParts=script.split(' ')
			scriptName=scriptParts[0]

			scriptDir = os.path.dirname(config['filename'])
			#scriptPath=os.path.join(,scriptName)
			comparePath=os.path.join(scriptDir,compareFiles)
			print '\trun script',scriptParts[0],'(',' '.join(scriptParts[1:]),')'
			cmd = 'python '+script
			cmd = cmd + ' -p ' + simDir +' -n ' + modelName
			#print 'commande ',cmd
			
			logFileName = os.path.join(logDirectory(scriptWorkingDir),"script_"+str(nbDone)+'_'.join(scriptParts))
			FD=open(logFileName,"w")
			FDList.append(FD)
			processList.append(subprocess.Popen(shlex.split(cmd),cwd=scriptDir,stdout=FD,stderr=subprocess.STDOUT))
			compareFileList.append(comparePath)
			logFileNameList.append(logFileName)
			nbDone = nbDone+1
	#then compare output.
	for process,FD,comparePath,logFileName in zip(processList,FDList,compareFileList,logFileNameList):
		process.wait()
		FD.close();
		nbDoneFail,nbDoneUncon = compareFile(comparePath,logFileName,nbDoneFail,nbDoneUncon)
	#done for compare scripts. Now custom scripts.
	for config in configList:
		for script in config['customScript']:
			customScriptDir = os.path.dirname(config['filename'])
			print '\trun custom script',os.path.join(customScriptDir,script)
			cmd='python '+script+' -p '+simDir+' -n '+modelName
			os.chdir(customScriptDir) #change working dir.
			#print 'cwd '+os.getcwd()
			#print cmd
			ret_diff = os.system(cmd)
			if ret_diff != 0:
				print "*** ERROR *** custom script failed"
				nbDoneFail = nbDoneFail + 1
			os.chdir(scriptWorkingDir) #back to the script dir.
			nbDone = nbDone+1			
	return nbDone,nbDoneFail,nbDoneUncon

def reOrderConfig(configList):
	""" One should re-order the configuration data:
		One list of dictionnaries
	"""
	newList = []
	for config in configList:
		for modelName,filename in zip(config['models'],config['files']):
			for target in config['targets']:
				makeStr=getMakefileParam(config)
				#Ok. Now search if entry is in the list.
				found = False
				for entry in newList:
					if (entry['models'] == modelName) and (entry['targets'] == target) and (entry['make'] == makeStr) and (entry['file'] == filename) and entry['local'] == False:
						   entry['config'].append(config)
						   found = True
				if not found:
					#print "add global entry ",filename
					entry = {}
					entry['models'] = modelName
					entry['targets'] = target
					entry['make'] = makeStr
					entry['file'] = filename
					entry['local'] = False
					entry['config'] = []
					entry['config'].append(config)
					newList.append(entry)
		#now add locals. One entry for each local.
		for modelName,filename in zip(config['models'],config['locals']):
			for target in config['targets']:
				makeStr=getMakefileParam(config)
				entry = {}
				entry['models'] = modelName
				entry['targets'] = target
				entry['make'] = makeStr
				entry['file'] = filename
				entry['local'] = True
				entry['config'] = []
				entry['config'].append(config)
				newList.append(entry)
	return newList

def getMakefileParam(config):
	makeStr = ''
	#first, get the DEFINES
	#list is sorted -> same options => same makefile string.
	defStr = ' '.join(sorted(config['define'])) #join list, with ' ' as separator.
	#One should add the 'HOST_IS_LITTLE_ENDIAN' param (for arm or i386)
	machine = os.uname()[4]
	if machine=='x86_64':
		makeStr += 'HOST64=1'
		defStr += ' -DHOST_IS_LITTLE_ENDIAN'
	elif machine=='i686':
		makeStr += 'HOST64=0'
		defStr += ' -DHOST_IS_LITTLE_ENDIAN'
	else:
		print "*** internal error: unable to find machine ",machine

	if config['stubs']:
		makeStr += ' USE_IO_STUBS=1'
		makeStr += ' IO_STUBS_SRC_DIR=./stubs'
	else:
		makeStr += ' USE_IO_STUBS=0'
	if config['pipelineTrace']:
		makeStr += ' GADL_WITH_PIPELINE_TRACE=1'
	else:
		makeStr += ' GADL_WITH_PIPELINE_TRACE=0'
	makeStr += ' DEFINES=\''+defStr+'\''
	return makeStr

def	printResults(totalDone,totalFail,totalUncon,totalGadlError,totalBuildError):
	print
	print '*'*80
	print '*** build results ***'
	print '* nb simulators failed to generate (to src)',totalGadlError,'*'
	print '* nb simulators failed to build (from src) ',totalBuildError,'*'
	print '*** tests results ***'
	print '* nb test script done          ',totalDone,'*'
	print '* nb test script failed        ',totalFail,'*'
	print '* nb test script unconclusive  ',totalUncon,'*'
	totalOK = totalDone-totalFail-totalUncon
	print '* nb test OK                   ',totalOK,
	if totalDone > 0:
		totalOKPercent = (min(100, float(totalOK) / totalDone * 100))
		print '-> % 3.1f%% *' % totalOKPercent,
	print '\n'+'*'*80

def	buildTargetAndRunTests(scriptWorkingDir,newList,buildLocalsOK):
	""" This function apply each test.
	    * It first compiles the simulator
		* then it search for configs that match this simulator, and apply test.
	"""
#	for entry in newList:
#		print "model  ",entry['models'],
#		print ",target ",entry['targets'],
#		print ",make ",entry['make'],
#		print ",[ ",len(entry['config']),"]"
#	return newList
	nbSimsDone=0
	totalDone = 0
	totalFail = 0
	totalUncon = 0
	totalBuildError = 0
	totalGadlError = 0
	nbSims=len(newList)
	for entry in newList:
		modelName=entry['models']
		target=entry['targets']
		makeStr=entry['make']
		isLocal = entry['local']
		simDir = ''
		fileAbs = ''
		modelFile = ''
		compileOk = True
		if isLocal:
			config = entry['config'][0] #There is only one (local)
			scriptDir = os.path.dirname(config['filename'])
			simDir=os.path.join(scriptWorkingDir,os.path.join(scriptDir,modelName))
			fileAbs=getFileHADL(scriptWorkingDir,os.path.join(scriptDir,entry['file']),True)
			modelFile = os.path.join(scriptDir,entry['file'])
			compileOk = buildLocalsOK[modelFile]
		else:
			simDir=os.path.join(generatedSimulatorSrcDirectory(scriptWorkingDir),modelName)
			fileAbs=getFileHADL(scriptWorkingDir,entry['file'],False)
		
		if compileOk:
			#copy the stubDir if it exists.
			stubDir=os.path.join(os.path.dirname(fileAbs),'ioStubs/simulatorSource')
			if os.path.isdir(stubDir):
				stubDirDst = simDir+'/stubs'
				if not os.path.isdir(stubDirDst):
					shutil.copytree(stubDir,stubDirDst)

			#print "current simDir",simDir
			if os.path.isdir(simDir):
				#build the simulator (first clean any previous build).
				print "-> Make target",entry['targets'],"for",
				if isLocal:
					print "local",
				print "model",modelName
				popenMake = subprocess.Popen(['make','clean'],cwd=simDir)
				popenMake.wait()
				cmd = 'make '+target+' '+makeStr+' -j9'
				logFileName = os.path.join(logDirectory(scriptWorkingDir),"build"+str(nbSimsDone))
				logFD = open(logFileName,"w")
				logFD.write("**********\n")
				logFD.write("target:"+target+'\n')
				logFD.write("modelName:"+modelName+'\n')
				logFD.write("build parameters:"+makeStr+'\n')
				logFD.write("**********\n")
				popenMake = subprocess.Popen(shlex.split(cmd),cwd=simDir,stdout=logFD,stderr=subprocess.STDOUT)
				popenMake.wait()
				if(popenMake.returncode): #test target build binary
					#compilation failed.
					print "ERROR: compilation failed : return code ",popenMake.returncode
					print "ERROR: compilation log is ",logFileName
					print "ERROR: no test performed"
					totalBuildError = totalBuildError+1
				else:
					#launch the test.
					nbDone,nbDoneFail,nbDoneUncon=launchTestsOnTarget(scriptWorkingDir,entry['config'],modelName,target,simDir)
					totalDone = totalDone + nbDone
					totalFail = totalFail + nbDoneFail
					totalUncon = totalUncon + nbDoneUncon
				logFD.close()
			else:
				print "-> ERROR: The simulator sources are not present: ",simDir
			#update stats...
			nbSimsDone=nbSimsDone+1
			print "-> % 3.1f%% done." % (min(100, float(nbSimsDone) / nbSims * 100))
		else:
			#compile not OK for local file
			print "** Skip local model \'",modelFile,"\' (did not compile correctly)"
			totalGadlError = totalGadlError + 1
	printResults(totalDone,totalFail,totalUncon,totalGadlError,totalBuildError)
		

if __name__ == '__main__':
	pathname = os.path.dirname(sys.argv[0])        
	configList = []
	scriptWorkingDir = os.path.abspath(pathname)
	if len(sys.argv) > 1:
		scriptDirs = sys.argv[1:]
	else:
		scriptDirs = os.listdir(scriptWorkingDir)
	#search all directories.
	#and in these directories, search for '.test' configuration files.
	#Maybe there are more than one .test file in one dir.
	#all configurations are stored in the configList.
	for dir in scriptDirs:
		if os.path.isdir(dir):
			#ok, found one subdirectory.
			for filename in os.listdir(dir):
				extension = os.path.splitext(filename)[1][1:].strip() 
				if(extension == 'test'):
					scriptFile=os.path.join(dir,filename)
					print 'use config file \'',scriptFile,'\''
					configList.append(readConfigFile(scriptFile))
	#ok. Now, we get all the 'config' files.
	#Next step is to build simulator sources for models that are declared
	buildLocalsOK = buildSimSources(scriptWorkingDir,configList) 
	#Then, we need to re-order config list in order to make all tests
	#related to one build comfiguration (same target/build options)
	newList=reOrderConfig(configList)
	#and we make the tests related to each build configuration.
	buildTargetAndRunTests(scriptWorkingDir,newList,buildLocalsOK)
