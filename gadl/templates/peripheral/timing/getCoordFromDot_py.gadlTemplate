#!/usr/bin/python
# vim: set fileencoding=utf-8 :

import os
import subprocess
import re
import sys

#code example extracted from:
#http://jimmyg.org/blog/2009/working-with-python-subprocess.html#checking-a-program-is-on-the-path
def whereis(program):
    for path in os.environ.get('PATH', '').split(':'):
        if os.path.exists(os.path.join(path, program)) and \
           not os.path.isdir(os.path.join(path, program)):
            return os.path.join(path, program)
    return None

def processDotLine(line):
	#we get only node positions:
	#we get lines that matches:
	# pos="\d+(\.\d+)?,\d+(\.\d+)? -> pos="12.34,56,78
	# and values \d+ are set in groups 'x' and 'y', node id is in 'id'.
	#edges are not taken into account -> there is the 'e' char : pos="e\d+...
	#but no '->' which means transitions.
	#we only take care of the integer value in coordinates.
	regExpPlace = re.compile('\s*(?P<id>\w+).*pos="(?P<x>\d+)(\.\d+)?,(?P<y>\d+)(\.\d+)?.*')
	result = regExpPlace.match(line)
	if result:
		print 'point '+result.group('id')+' '+result.group('x')+' '+result.group('y')
#	regExpTransition = re.compile('\s*(?P<idSrc>\w+)\s*->\s*(?P<idDst>\w+).*pos="e,(?P<idTrans>.*)".*')
#	result = regExpTransition.match(line)
#	if result:
#		transitionPoints = [];
#		transPoints = result.group('idTrans').split(' ') #split points separated by ' ' 
#		print result.group('idSrc')+' -> '+result.group('idDst')+' : ',
#		for point in transPoints:
#			pointXY = point.split(',')
#			print pointXY[0]+'x'+pointXY[1]+' ',
#			#transitionPoints += { 'x' : pointXY[0], 'y' : pointXY[1]}
#		print transitionPoints

if __name__ == '__main__':
	#check that 'dot' program is available
	dotProg = whereis('dot')
	if dotProg is None:
		print "The program 'dot' is not in the path. "
		print "All automata states will be at the same place in Uppaal."
		print "Please install graphviz tools http://www.graphviz.org/  for a better output."
	else:
		#found it. Great!
		inputFile = "test.dot"
		if len(sys.argv)>1:
			inputFile = sys.argv[1]
		tmpResultFile = inputFile+"__tmp"
		#use de program to get positions.
		#print dotProg+" "+inputFile+" -o "+tmpResultFile
		subprocess.call([dotProg,inputFile,"-o",tmpResultFile])
		if os.path.exists(tmpResultFile):
			#open the result file.
			fd = open(tmpResultFile,'r')
			currentLine = ''
			for line in fd.xreadlines():
				lastChar = line.rstrip()[-1]
				if lastChar == ';':
					processDotLine(currentLine)
					currentLine = ''
				else:
					currentLine = currentLine + line.rstrip()
			fd.close()
			os.remove(tmpResultFile)
		else:
			print "Error when executing the 'dot' program."
		
