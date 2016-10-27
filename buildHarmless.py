#!/usr/bin/python
# -*- coding: UTF-8 -*-
# vim: set fileencoding=utf-8 :
# This script is used to build harmless tools automagically.
# Common build tools should be installed (make/gcc/..).

# The script:
# * check for the galgas version, and download the most recent version if necessary
# * generate gadl sources (c++) from the galgas description.
# * build a2cpp/p2a and gadl.

#tested on MacOS X (10.10) and Linux Ubuntu (12.04) - 32 bits.
#This should work either with Python 2.7 and 3.
#please report any error to harmless@irccyn.ec-nantes.fr

from __future__ import print_function
import sys
if sys.version_info[0] == 2 and sys.version_info[1] <= 6:
	print("Python version 2.7 minimum required")
	sys.exit(1)
if sys.version_info.major < 3: #python2.7 mini required
	from urllib2 import URLError,urlopen
	from urllib import urlretrieve
else:
	from urllib.request import urlopen, urlretrieve
	from urllib.error import URLError
import socket
import os, sys
import subprocess
import re

def scriptStep(verbose,num,msg):
	if verbose:
		line=' step '+str(num)+":"+msg+' '
		if len(line) & 1 == 1: #odd value
			line+=' '
		nbStar=(80-len(line))//2 #integer division 
		print('*'*nbStar+line+'*'*nbStar)
	return num+1

#Hook to print the download process of galgas.
def reporthook(a,b,c):
    # ',' at the end of the line is important!
    print('{val:3.1f}% of {size} bytes\r'.format(val=min(100, float(a * b) / c * 100),size=c),end='\r')
    #print "% 3.1f%% of %d bytes\r" % (min(100, float(a * b) / c * 100), c),
    sys.stdout.flush()

#code example extracted from:
#http://jimmyg.org/blog/2009/working-with-python-subprocess.html#checking-a-program-is-on-the-path
def whereis(program,scriptWorkingDir):
	paths = scriptWorkingDir+':'+os.environ.get('PATH', '')
	for path in paths.split(':'):
		if os.path.exists(os.path.join(path, program)) and \
			not os.path.isdir(os.path.join(path, program)):
			return os.path.join(path, program)
	return None

def downloadGalgas(URLGalgas,galgasVersion,forceSrc,scriptWorkingDir):
	#First: get the host.
	archiveName = ""
	archiveType = ""
	if forceSrc:
		archiveName = 'galgas-sources-lf.tar.bz2'
		archiveType = 'src'
	else:
		uname = os.uname()
		if uname[0] == 'Darwin': #Mac OS.
			archiveName = "galgas-tool.dmg"
			archiveType = 'dmg'
		elif uname[0] == 'Linux':
			if uname[4] == 'x86_64':
				archiveName = "galgas-x86-linux64.zip"
				archiveType = 'zip'
			elif uname[4][0] == 'i' and uname[4][2:4] == '86': #ix86
				archiveName = "galgas-x86-linux32.zip"
				archiveType = 'zip'
			else:
				print("The Linux host does not seem to be an x86 or x86_64 processor: "+uname[4])
				archiveName = 'galgas-sources-lf.tar.bz2'
				archiveType = 'src'
		else:
			#unknown host
			print("The host does not seem to be either Linux or Mac:"+uname[0])
			print("Cannot find a galgas binary that matches the host.")
			archiveName = 'galgas-sources-lf.tar.bz2'
			archiveType = 'src'
	#second: Download.
	try:
		#get last revision of Galgas
		#http://galgas.rts-software.org/download/lastRelease.php -> 2.3.7
		#http://galgas.rts-software.org/download/2.3.7/galgas-x86-linux32.zip
		URLGalgasArchive = URLGalgas+galgasVersion+'/'+archiveName
		print(' -> download last release of the Galgas compiler ('+URLGalgasArchive+')')
		print('and save it in '+scriptWorkingDir+'/'+archiveName)
		urlretrieve(URLGalgasArchive, scriptWorkingDir+'/'+archiveName, reporthook)
		print #\n
	except URLError:
		print("Error: Unable to get the last revision of galgas. Exit")
		sys.exit()
	#Third: extract.
	print("extract galgas compiler from the downloaded archive")
	if archiveType == 'dmg':
		#mount image file (dmg) using "hdid galgas-tool.dmg"
		output = subprocess.Popen(['hdid',scriptWorkingDir+'/'+archiveName], stdout=subprocess.PIPE).communicate()[0]
		print(output)
		#one output line should be like this.
		#/dev/disk2s2        	Apple_HFSX                     	/Volumes/GALGAS-TOOL
		for line in output.split(b'\n'):
			fields=line.split()
			if len(fields) >= 2:
				if fields[1] == b'Apple_HFSX':
					#found
					#copy the executable: call wait until command is complete.
					subprocess.call(['cp','-v',fields[2]+b'/galgas',scriptWorkingDir])
					#and umount image disk.
					subprocess.call(['umount',fields[2]])
	elif archiveType == 'zip': #Linux
		popenZip = subprocess.Popen(['unzip','-q',archiveName],cwd=scriptWorkingDir)
		popenZip.wait()		
	elif archiveType == 'src': #source package.
		print("Compile galgas from source, assuming an Unix host.")
		popenTar = subprocess.Popen(['tar','xjf',archiveName],cwd=scriptWorkingDir) #decompress
		popenTar.wait()		
		subprocess.call(['mv',scriptWorkingDir+'/'+'galgas',scriptWorkingDir+'/'+'galgasSrc']) #rename source directory
		popenBuildGalgas = subprocess.Popen(["make","galgas"],cwd=scriptWorkingDir+'/galgasSrc/makefile-unix') #assume a 32-bit Unix host
		popenBuildGalgas.wait() 
		subprocess.call(['mv',scriptWorkingDir+'/galgasSrc/makefile-unix/galgas',scriptWorkingDir]) #get back galgas binary
		subprocess.call(['rm','-rf',scriptWorkingDir+'/galgasSrc']) #remove source directory.
	#Fourth: remove archive.
	subprocess.call(['rm',scriptWorkingDir+'/'+archiveName])
	#Fifth: Test galgas (in case of downloading a binary target)
	#       if binary target does not run, try to unpack the source archive.
	if archiveType != 'src':
		try:
			if subprocess.call([scriptWorkingDir+'/galgas','--version']): #galgas run failed.
				print("The galgas binary does not seems to work...")
				print("retry using the galgas source package, it will take more time..")
				subprocess.call(['rm',scriptWorkingDir+'/galgas']) #remove galgas (as it does not run properly)
				downloadGalgas(URLGalgas,galgasVersion,True,scriptWorkingDir) #and get a new version from sources.
		except FileNotFoundError:
			print("Error during download, the Galgas compiler has not been correctly downloaded.")		

def installGalgas(verbose,scriptWorkingDir):
	galgasProg = whereis('galgas',scriptWorkingDir)
	URLGalgas = "http://galgas.rts-software.org/download/"
	galgasSiteOk = True #internet connexion?
	#first, get the latest galgas version (and check Internet connexion)
	galgasVersion = ""
	try:
		resp = urlopen(URLGalgas+'lastRelease.php')
		galgasVersion = resp.read(100).decode("utf-8")
	except URLError:
		galgasSiteOk = False

	if galgasProg is None:
		#no galgas found -> download.
		if not galgasSiteOk:
			print("I could not find any version of the galgas compiler, "+
			      "which is mandatory to build the Harmless compiler. ")
			print("The galgas web site: "+URLGalgas+" is not reachable.")
			print("Please check your Internet connection.")
			print("You can set your proxy configuration using the command")
			print("export http_proxy=\"http://proxyIP:proxyPort\"")
			print("(before calling this script)")
			sys.exit()
		else:
			print("I could not find the galgas compiler in the PATH")
			downloadGalgas(URLGalgas,galgasVersion,False,scriptWorkingDir)
	else: #galgas found, check version.
		if galgasSiteOk:
			#note: subprocess.check_output only appeared in v2.7 and is not available on MacOS 10.6
			output = subprocess.Popen([galgasProg,"--version",'-q'], stdout=subprocess.PIPE).communicate()[0]
			m = re.search(b'.*\s:\s+(.*), build.*$', output)
			if m != None:
				currentGalgasVersion = m.group(1).decode("utf-8")
				if currentGalgasVersion == galgasVersion:
					if verbose:
						print("galgas version OK ("+galgasVersion+")")
				else:
					print("The galgas compiler is installed, but the galgas version does not match.")
					print("installed:   "+currentGalgasVersion)
					print("last version "+galgasVersion)
					downloadGalgas(URLGalgas,galgasVersion,False,scriptWorkingDir)
			else:
				print("internal error: I found the galgas compiler, but I cannot find its version.")
				print("latest version available is: "+galgasVersion)
				downloadGalgas(URLGalgas,galgasVersion,False,scriptWorkingDir)
		else: #no Internet connexion, don't try to update.
			if verbose:
				print("no Internet connexion. Cannot try to update the Galgas compiler.")
	return whereis('galgas',scriptWorkingDir)
			
def buildFailed(step):
    print('*'*80)
    print("build failed at step"+step)
    print("You may contact harmless@irccyn.ec-nantes.fr")
    print('*'*80)
    sys.exit(step)

if __name__ == '__main__':
	#get script path directory (as built is done relatively to that dir):
	pathname = os.path.dirname(sys.argv[0])        
	scriptWorkingDir = os.path.abspath(pathname)
	
	verbose = True
	ok=True
	step = 1
	socket.setdefaulttimeout(5) #not to stop the script for a long time if there is no connection.
	#check if galgas is installed
	step=scriptStep(verbose,step,"Check galgas compiler")
	galgasTool=installGalgas(verbose,scriptWorkingDir)
	if galgasTool:

		step=scriptStep(verbose,step,"extract libpm, required by p2a and a2cpp")
		if subprocess.call([galgasTool,'--extract-libpm='+scriptWorkingDir+'/gadl/libpm','-q']):
                    buildFailed(step-1)

		step=scriptStep(verbose,step,"compile p2a tool")
		popenP2A = subprocess.Popen(["make",'-j9'],cwd=scriptWorkingDir+'/p2a')
		if popenP2A.wait():
                    buildFailed(step-1)

		step=scriptStep(verbose,step,"compile a2cpp tool")
		popenA2CPP = subprocess.Popen(["make",'-j9'],cwd=scriptWorkingDir+'/a2cpp')
		if popenA2CPP.wait():
                    buildFailed(step-1)

		step=scriptStep(verbose,step,"compile libelf")
		libelfFile = 'libelf-0.8.13'
		logPID = open('./compilationLog.txt', 'w')
		libelfArchive = libelfFile+'.tar.gz'
		popenLibElf = subprocess.Popen(['tar','xzf','gadl/'+libelfFile+'.tar.gz'],cwd=scriptWorkingDir)
		if popenLibElf.wait():
                    buildFailed(step-1)
		print("configure "+libelfFile+"...")
		popenLibElf = subprocess.Popen(['./configure','--enable-compat',
			'--enable-shared=no','--prefix='+scriptWorkingDir+'/libelf'],stdout=logPID,cwd=scriptWorkingDir+'/'+libelfFile)
		if popenLibElf.wait():
                    buildFailed(step-1)
		print("make "+libelfFile+"...")
		popenLibElf = subprocess.Popen(['make','CFLAGS=-fPIC','LDFLAGS=-fPIC','-j9'],stdout=logPID,cwd=scriptWorkingDir+'/'+libelfFile)
		if popenLibElf.wait():
                    buildFailed(step-1)
		print("install "+libelfFile+" in ./libelf")
		popenLibElf = subprocess.Popen(['make','install'],stdout=logPID,cwd=scriptWorkingDir+'/'+libelfFile)
		if popenLibElf.wait():
                    buildFailed(step-1)
		logPID.close

		step=scriptStep(verbose,step,"generate gadl C++ sources using galgas")
		popenGalgas = subprocess.Popen([galgasTool,'gadl/gadl.galgasProject','-q'],cwd=scriptWorkingDir)
		if popenGalgas.wait():
                    buildFailed(step-1)

		step=scriptStep(verbose,step,"compile gadl tool")
		gadlLoc = scriptWorkingDir
		host64 = False
		uname = os.uname()
		if uname[0] == 'Darwin': #Mac OS.
			gadlLoc = gadlLoc+"/gadl/makefile-macosx"
			host64=True
		else:
			gadlLoc = gadlLoc+"/gadl/makefile-unix"
		# popenGADL = subprocess.Popen(["make",'gadl','-f','makefile','-j9'],cwd=gadlLoc)
		popenGADL = subprocess.Popen(["./build+release.py",'all', '-1'],cwd=gadlLoc) # -1 means processor count + 1
		if popenGADL.wait():
                    buildFailed(step-1)

		subprocess.call(['mv',gadlLoc+'/gadl',scriptWorkingDir+'/gadl/gadl'])
		print('*'*80)
		print('test generated compiler:')
		if not subprocess.call([scriptWorkingDir+'/gadl/gadl','--version']): #test gadl binary.
			print('* Gadl, the Harmless compiler is succesfully compiled:')
			print('* -> '+scriptWorkingDir+'/gadl/gadl')
			print('* You can generate simulators from description examples. For the PowerPC:')
			print('* \tcd '+scriptWorkingDir+'/gadl/examples/PPC')
			print('* \t../../gadl ./ppc.hadl')
			print('* A directory \'powerpc\' is created (from the CPU model name in description).')
			print('* Then compile the simulator:')
			print('* \tcd powerpc')
			print('* \tmake standalone')
		else:
			print('* There was a problem and the gadl compilation failed')
		print('*'*80)
