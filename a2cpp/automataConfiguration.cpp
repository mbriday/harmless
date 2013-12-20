/** 
 * a2cpp
 *
 * a2cpp is copyright (c) IRCCyN 2005+
 * a2cpp est protege par la loi sur la propriete intellectuelle
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * $Date: 2006-02-28 15:40:26 +0100 (Tue, 28 Feb 2006) $
 * $Rev: 7 $
 * $Author: mik $
 * $URL: https://a2cpp.rts-software.org/svn/automataConfiguration.cpp $
 * $Id: automataConfiguration.cpp 7 2006-02-28 14:40:26Z mik $
 */
//#define DEBUG_AUTOMATA_CONFIG

#include "automataConfiguration.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "utils.h" //SEGFAULTIF, nbBitsToCodeValue
#include <cassert> //assert
using namespace std;

automataConfiguration::automataConfiguration() :
m_automata(NULL), m_nbBitsToCodeOneState(0)
{
}

void automataConfiguration::readPipeline(istream &file)
{
	checkKey("pipeline",file);
	file >> m_pipelineName;
	checkKey("with",file);
	int nbPipelineStages;
	file >> nbPipelineStages;
	checkKey("stages",file);
	string temp;
	for(int i = 0; i < nbPipelineStages; i++)
	{
		file >> temp;
		m_pipelineStringVector.push_back(temp);
	}
	#ifdef DEBUG_AUTOMATA_CONFIG
		cout << "pipeline: ";
		for(int i = 0; i < nbPipelineStages; i++)
			cout << m_pipelineStringVector[i];
		cout << endl;
	#endif
}

void automataConfiguration::readNotifications(istream &file)
{
	int nbNotifications;
	file >> nbNotifications;
	checkKey("notifications",file);
	string temp;
	for(int i = 0; i < nbNotifications; i++)
	{
		file >> temp;
		m_notificationsStringVector.push_back(temp);
	}
	#ifdef DEBUG_AUTOMATA_CONFIG
		cout << "notifications: ";
		for(int i = 0; i < nbNotifications; i++) 
		{
			if(i!=0) cout << ", ";
			cout << m_notificationsStringVector[i];
		}
		cout << endl;
	#endif
}

void automataConfiguration::readExternalResources(istream &file)
{
	int nbExternalResources;
	file >> nbExternalResources;
	checkKey("external",file);
	checkKey("resources",file);
	string temp;
	for(int i = 0; i < nbExternalResources; i++)
	{
		file >> temp;
		m_externalResourcesStringVector.push_back(temp);
	}
	#ifdef DEBUG_AUTOMATA_CONFIG
		cout << "external resources: ";
		for(int i = 0; i < nbExternalResources; i++) 
		{
			if(i!=0) cout << ", ";
			cout << m_externalResourcesStringVector[i];
		}
		cout << endl;
	#endif
}

void automataConfiguration::readInstructionClasses(istream &file)
{
	int nbInstructionClasses;
	file >> nbInstructionClasses;
	checkKey("instruction",file);
	checkKey("classes",file);
	string temp;
	//no instruction -> id is 0.
	m_instructionClassesStringMap["-"] = 0;
	for(int i = 0; i < nbInstructionClasses; i++)
	{
		file >> temp;
		m_instructionClassesStringMap[temp] = i+1;
	}
	#ifdef DEBUG_AUTOMATA_CONFIG
		cout << "instruction classes: ";
	std::map<std::string, unsigned int>::iterator it = m_instructionClassesStringMap.begin();
	std::map<std::string, unsigned int>::const_iterator itEnd = m_instructionClassesStringMap.end();
	bool start = true;
	while(it != itEnd)
	{
		if(!start) cout << ", ";
		start = false;

		string str = (*it).first;
		unsigned int val = (*it).second;

		cout << str << "(" << val << ")" ;
		
		it++;
	}
	cout << endl;
	#endif
}

void automataConfiguration::readAutomata(istream &file)
{
	int nbBitsToCodeAState = 0;
	int nbBitsToCodeATransition = 0;
	file >> nbBitsToCodeAState;
	checkKey("bits", file);
	checkKey("for", file);
	checkKey("a", file);
	checkKey("state", file);
	file >> nbBitsToCodeATransition;
	checkKey("bits", file);
	checkKey("for", file);
	checkKey("a", file);
	checkKey("condition", file);
	m_automata = new automata(nbBitsToCodeAState, nbBitsToCodeATransition);
	string line;
	file >> line;
	m_automata->loadAutomataBDD(line.c_str());
}

void automataConfiguration::checkKey(string key, istream &file)
{
	string textRead;
	file >> textRead;
	if(textRead != key) cerr << "error when parsing file, got \'" << textRead << "\', but \'" << key << "\' was required" << endl;
	assert(textRead == key);
}


bool automataConfiguration::load(const string filename)
{
	bool loadOk = false;
	bool isAFile = false;
	bool openOk = true;
	ifstream file;
	istream *inStream = &cin;
	if(!filename.empty())
	{
		isAFile  = true;
		file.open(filename.c_str(), ifstream::in);
		if(!file) 
		{	
			cerr << "open file error :" << filename << " in read mode" << endl;
			openOk = false;
		} else inStream = (istream *)&file;
	}
	if(openOk)
	{
		int version;
		checkKey("version",*inStream);
		(*inStream) >> version;
		if(version != A2A_FILE_VERSION) cerr << "version not supported : " << version << endl;
		else
		{
			#ifdef DEBUG_AUTOMATA_CONFIG
				cout << "version ok" << endl;
			#endif
			checkKey("model",*inStream);
			(*inStream) >> m_modelName;
			int depth;
			checkKey("depth",*inStream);
			(*inStream) >> depth;
			if(depth != 1) cerr << "a2cpp can only use simple pipeline! Depth found is " << depth << endl;
			else
			{
				readPipeline(*inStream);
				readExternalResources(*inStream);
				readInstructionClasses(*inStream);
				readNotifications(*inStream);
				readAutomata(*inStream);
				loadOk = true;
			} //depth
		} //version
		if(isAFile) file.close();
	}	//open file error
	return loadOk;
}

//unsigned int automataConfiguration::nbBitsToCodeOneStage()
//{
//	if(!m_nbBitsToCodeOneState)
//	{
//		//cout << "nb inst classes : " << m_instructionClassesStringMap.size();
//		// the nop instruciton is already added. ('-')
//		m_nbBitsToCodeOneState = nbBitsToCodeValue(m_instructionClassesStringMap.size());
//		//cout << ", " << m_nbBitsToCodeOneState << endl;
//	}
//	return m_nbBitsToCodeOneState;
//}
