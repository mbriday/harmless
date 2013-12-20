/** 
 * p2a
 *
 * p2a is copyright (c) IRCCyN 2005+
 * p2a est protege par la loi sur la propriete intellectuelle
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 * $Id$
 */

#include "systemConfiguration.h"
#include <iostream>
#include <vector>
#include "resource.h"
#include "instructionClass.h"
#include "pipeline.h"
#include "pipelineStage.h"
#include "pipelineNotification.h"
//#include "dataDependencyInstructionClass.h"
#include <cassert> //assert

extern bool verbose;
//#define DEBUG_LOAD_CONFIG 

using namespace std;

systemConfiguration::~systemConfiguration()
{
	//call the destructor for each elements in vectors (except string).
	if(m_pipeline) macroMyDelete (m_pipeline);
	const unsigned int sizeRes = m_resourceDescriptorVector.size();
	for(unsigned int i=0; i<sizeRes; ++i) macroMyDelete (m_resourceDescriptorVector[i]);
	const unsigned int sizeInst = m_instructionClassVector.size();
	for(unsigned int i=0; i<sizeInst; ++i) macroMyDelete (m_instructionClassVector[i]);
	//do not remove pipline stage descriptor, because it is a resource descriptor
	//(and have already been deleted)
}


int systemConfiguration::getIndexInVector(vector<string> &vec, string str)
{
	bool found = false;
	unsigned int index = 0;
	unsigned int size = vec.size();
	while(!found && index < size)
	{
		found = (vec[index] == str);	
		if(!found) index++;
	}
	return index;
}

void systemConfiguration::processSymbolPipeline(ifstream &file)
{
	string command;
	file >> command;
	if(command == "addStage") 
	{
		if(m_NotificationDefined) 
			cerr << "internal error: no instruction class should be defined after a notification!" << endl;
		string name;
		file >> name;
		#ifdef DEBUG_LOAD_CONFIG
			cout << "add pipeline stage to " << name
			<< ": " << name << endl;
		#endif
		m_pipelineStageDescriptorNameVector.push_back(name);
		pipelineStageDescriptor *ps = NULL ;
    macroMyNew (ps, pipelineStageDescriptor(name));
		m_pipelineStageDescriptorVector.push_back(ps);
		m_pipeline->addStage(ps);
		ps->setPipeline(m_pipeline);
		//don't forget that a pipeline stage IS a resource!!!
		m_resourceDescriptorNameVector.push_back(name);
		m_resourceDescriptorVector.push_back(ps);
	} else if(command == "addResource")
	{

		//pipe1 addResource internal 1 IP 2 priority D F
		//pipe1 addResource external MF 0 priority
		//the number is not present for external as there is no number associated to the max allowed field.
		//
		//create resource
		string name, type;
		int nb=1;
		file >> type;
		bool external = (type == "external"); //else: internal
		if(external) file >> name;
		else file >> nb >> name; //maw allowed.
		resourceDescriptor *resDesc = NULL ;
    macroMyNew (resDesc, resourceDescriptor(name,nb, external));
		m_resourceDescriptorNameVector.push_back(name);
		m_resourceDescriptorVector.push_back(resDesc);
		//populate with priority.
		file >> nb >> type;
		SEGFAULTIF(type!="priority");
		for(int i = 0; i < nb; i++) 
		{
			string stage;
			file >> stage;
			int indexPS = getIndexInVector(m_pipelineStageDescriptorNameVector, stage);
			resDesc->addPriority(m_pipelineStageDescriptorVector[indexPS]);
		}
		m_pipeline->addResourceDescriptor(resDesc);
		#ifdef DEBUG_LOAD_CONFIG
			cout << type << " resourceDescriptor found : " << name << "," << nb << endl;
			const unsigned int max = resDesc->getNbPriorities();
			if(max > 0)
			{
				cout << "priorities: ";
				for(unsigned int i = 0; i < resDesc->getNbPriorities(); i++) 
					cout << resDesc->getPipelineStageDescriptorAtPriority(i)
						->toString() << " ";
				cout << endl;
			}

			cout << "add resourceDescriptor " << name
			<< " to " << m_pipelineName << endl;
		#endif
	} else if(command == "addInstructionClass")
	{
		if(m_NotificationDefined) 
			cerr << "internal error: no instruction class should be defined after a notification!" << endl;
		string name;
		file >> name;
		//create instruction class
		m_instructionClassNameVector.push_back(name);
		pipeline *pipe=m_pipeline;
		//create and add to the pipeline.
		instructionClass *ic = pipe->addInstructionClass(name);
		m_instructionClassVector.push_back(ic);
		#ifdef DEBUG_LOAD_CONFIG
			cout << "add instruction class " << name
			<< " to " << m_pipelineName << endl;
		#endif
	} 
//	else if(command == "addDataDependencyInstructionClass")
//	{
//		string name;
//		file >> name;
//		//create data dep instruction class name
//		m_DapaDependencyInstructionClassNameVector.push_back(name);
//		//create and add to the pipeline.
//		dataDependencyInstructionClass *ddc = new dataDependencyInstructionClass();
//		m_DapaDependencyInstructionClassVector.push_back(ddc);
//#ifdef DEBUG_LOAD_CONFIG
//		cout << "add data dependency instruction class " << name
//		<< " to " << m_pipelineName << endl;
//#endif
//	}
}

void systemConfiguration::processSymbolInstructionClass(int index, ifstream &file)
{
	string symbol = m_instructionClassNameVector[index];
	string  command;
	file >> command;
	if((command == "dependResource")  ||
	   (command == "getResource")     ||
	   (command == "releaseResource"))
	{
		string res, ps;
		unsigned int nbAccess;
		file >> nbAccess >> res >> ps; //TODO nbAccess
		int indexR = getIndexInVector(m_resourceDescriptorNameVector, res);
		int indexPS = getIndexInVector(m_pipelineStageDescriptorNameVector, ps);
		#ifdef DEBUG_LOAD_CONFIG
			cout << "instruction " << symbol;
			if(command == "dependResource") cout << " depends on ";
			else if(command == "getResource") cout << " gets ";
			else if(command == "releaseResource") cout << " release ";
			cout << "resource " << res << " at stage " << ps << endl;
		#endif
    resourceAccessType type = DEPEND ;
		if(command == "dependResource") type = DEPEND;
		else if(command == "getResource") type = GET;
		else if(command == "releaseResource") type = RELEASE;
		else cerr << "unknown command : " << command << endl;
		m_instructionClassVector[index]->resourceAccess(type,
							m_resourceDescriptorVector[indexR],
							m_pipelineStageDescriptorVector[indexPS], nbAccess);

	} else 	if((command == "require")  ||
			   (command == "lock")     ||
			   (command == "unlock"))	   
	{
		string dataStr;
		file >> dataStr;
		assert(dataStr == "data");
		string ps;
		file >> ps;
		#ifdef DEBUG_LOAD_CONFIG
			cout << "instruction " << symbol << " " << command << " a data in stage " << ps << endl;
		#endif
    } else if(command == "stay")
	{
		string ps;
		unsigned int val;
		file >> ps >> val;
		int indexPS = getIndexInVector(m_pipelineStageDescriptorNameVector, ps);
		m_pipelineStageDescriptorVector[indexPS]->stageMayBeLockedAtLeast(val);
		assert(val>1);
		m_instructionClassVector[index]->instructionHaveExtraCyclesInStage(m_pipelineStageDescriptorVector[indexPS], val-1);
		
		//m_instructionClassVector[index]->StayInStage(m_pipelineStageDescriptorVector[indexPS], val);
		#ifdef DEBUG_LOAD_CONFIG
			cout << "instruction " << symbol << " stays in stage " << ps << " for " << val << " cycles " << endl;
		#endif
	} else cerr << "unknown command : " << command << endl;
}

//void systemConfiguration::processSymbolDapaDependencyInstructionClass(int index, ifstream &file)
//{
//	string symbol = m_DapaDependencyInstructionClassNameVector[index];
//	string  command;
//	string ps;
//	file >> command >> ps;
//	const int indexPS = getIndexInVector(m_pipelineStageDescriptorNameVector, ps);
//	if(command == "required") {
//		m_DapaDependencyInstructionClassVector[index]->requiredStageVector.push_back(indexPS);
//        #ifdef DEBUG_LOAD_CONFIG
//			cout << "data dep instruction class " << symbol << " requires "
//			     << "data dep access at stage " << ps << endl;
//		#endif
//	} else if(command == "lock") {
//		m_DapaDependencyInstructionClassVector[index]->lockStageVector.push_back(indexPS);
//		#ifdef DEBUG_LOAD_CONFIG
//			cout << "data dep instruction class " << symbol << " locks "
//			     << "data dep access at stage " << ps << endl;
//		#endif
//		
//	} else if(command == "unlock") {
//		m_DapaDependencyInstructionClassVector[index]->unlockStageVector.push_back(indexPS);
//		#ifdef DEBUG_LOAD_CONFIG
//			cout << "data dep instruction class " << symbol << " unlocks "
//			     << "data dep access at stage " << ps << endl;
//		#endif
//	} else {
//		cerr << "unrecognized command for data dependency instruction class: " << symbol << endl;
//	}
//}


void systemConfiguration::processSymbol(string &symbol, ifstream &file)
{
	//cout << "get symbol:" << symbol << endl;
	unsigned int index;
	if(m_pipelineName == symbol)
	{
		//get a pipeline symbol at index.
		processSymbolPipeline(file);
	}
	else if((index = getIndexInVector(m_instructionClassNameVector, symbol)) != m_instructionClassNameVector.size())
	{
		//get an instruction symbol at index
		processSymbolInstructionClass(index,file);
	}
}


bool systemConfiguration::load(const string filename)
{
	bool loadOk = true;
	if(verbose) cerr << "load configuration from file: " << filename << endl;
	ifstream file;
	file.open(filename.c_str(), ifstream::in);
	if(!file) 
	{	
		cerr << "open file error :" << filename << " in read mode" << endl;
		return false;
	}
	//first, the revision number.
	int version;
	string command;
	file >> command;
	if(command == "version")
	{
		file >> version;
	}else {
		cerr << "no version specified" << endl; 
		version = -1; //set an error
		loadOk = false;
	}

	switch(version)
	{
	case 8:
		//version 1..7: -> no more taken into account (p2aV1)
		file >> command;
		if(command != "model") cerr << "a model name should be given!" << endl;
		file >> m_modelName;
			
		file >> command;
		while(!(file.eof()))
		{
			if(!processCommand(command,file))
				processSymbol(command, file);
			file >> command;
		}
		//cout << "pipeline" << endl << m_pipeline->debug();
		break;
	default: 
		cerr << "configuration version not supported:" << version << endl;
		loadOk = false;
	}
	file.close();
	return loadOk;
}

bool systemConfiguration::processCommand(const string command, ifstream &file)
{
	bool result = true;
	if(command.compare(0,2,"//") == 0)
	{
		string comment;
		getline(file, comment);
		#ifdef DEBUG_LOAD_CONFIG
			cout << "comment: " << command << comment << endl;
		#endif
	}
	else if(command == "pipeline") 
	{
		string name;
		file >> name;
		#ifdef DEBUG_LOAD_CONFIG
			cout << "pipeline found : " << name << endl;
		#endif
		m_pipelineName = name;
		m_pipeline = NULL ;
    macroMyNew (m_pipeline, pipeline(name));
	}
	else if(command == "notification") processCommandAddNotification(file);
	else result = false;
	return result;
}

void systemConfiguration::processCommandAddNotification(std::ifstream &file)
{
	m_NotificationDefined = true;
	string name;
	file >> name;
	string code;
	int classIndex = -1;
	bool enter = false; //enters = true , exits = false;
	file >> code;
	assert(code == "when");
	file >> code;
	assert(code == "instruction");
	file >> code;
	if(code == "enters") enter = true;
	else if(code == "exits") enter = false;
	else { //specific to an instruction.
		classIndex = getIndexInVector(m_instructionClassNameVector, code);
		assert((unsigned int)classIndex != m_instructionClassNameVector.size());
		file >> code;
		if(code == "enters") enter = true;
		else if(code == "exits") enter = false;
	}
	if(enter) { //this is 'enters in'
		file >> code;
		assert(code == "in");
	}
	file >> code;
	assert(code == "stage");
	string stageName;
	file >> stageName;
	unsigned int indexPS = getIndexInVector(m_pipelineStageDescriptorNameVector, stageName);
	assert(indexPS != m_pipelineStageDescriptorNameVector.size());
	//classIndex+1 because 0 is reserved to 'any'
	pipelineNotificationData *pad = NULL ;
  macroMyNew (pad, pipelineNotificationData(m_pipeline, name, classIndex+1, indexPS, enter));
	m_pipeline->addNotification(pad);
	#ifdef DEBUG_LOAD_CONFIG
		cout << "new notification found : " << name;
		if(classIndex >= 0) cout << ", related to instruction " << m_instructionClassNameVector[classIndex] ;
		if(enter) cout << " when getting in";
		else cout << " when getting out of";
		cout << " stage " << m_pipelineStageDescriptorNameVector[indexPS] << endl;
	#endif	
}

unsigned int const systemConfiguration::getNumberOfExternalResources()
{
	unsigned int nbExt = 0;
	unsigned int size = m_resourceDescriptorVector.size();
	for(unsigned int i=0; i< size; i++)
		if(m_resourceDescriptorVector[i]->isExternal()) nbExt++;
	return nbExt;
}
