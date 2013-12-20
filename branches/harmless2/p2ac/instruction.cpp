/** 
 * p2ac
 *
 * p2ac is copyright (c) IRCCyN 2005+
 * p2ac est protege par la loi sur la propriete intellectuelle
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
#include "pipeline.h"
#include "pipelineStage.h"
#include "instruction.h"
#include "instructionDescription.h"
#include "resource.h"
#include "utils.h" //SEGFAULTIF
#include <iostream>

using namespace std;

instruction::instruction(const std::string inName, pipeline *pipe, const unsigned int id)
: m_nbStages(pipe->getNumberOfPipelineStages()), m_name(inName), m_psId(id)
{
	const unsigned int nbVec = m_nbStages*3;
	m_resourceDescriptorVectorTab = NULL ;
	macroMyNewArray (m_resourceDescriptorVectorTab, std::vector<resourceDescriptorAccess>, nbVec);
}

instruction::~instruction()
{
	macroMyDeleteArray (m_resourceDescriptorVectorTab);
	m_nbExtraCyclesVector.clear();
}

void instruction::resourceAccess(const resourceAccessType type, resourceDescriptor *res, pipelineStageDescriptor *ps, const unsigned int nbAccess)
{
	SEGFAULTIF(type>2);
	const unsigned int psIndex = ps->getIndex();
	std::vector<resourceDescriptorAccess> &vec = 
		m_resourceDescriptorVectorTab[getVectorId(type, psIndex)];
	//check for multiple allocation!!
	bool found = false;
	unsigned int i = 0;
	const unsigned int size = vec.size();
	resourceDescriptorAccess ra(res, nbAccess);
	while(!found && i<size) found = vec[i++] == ra;
	if(!found) 
	{
		resourceDescriptorAccess ra1(res, nbAccess);
		vec.push_back(ra1);
	}
}

std::vector<resourceDescriptorAccess> &instruction::getResourceDescriptorVector(
					const unsigned int pipelineStageDescriptorIndex, 
					const resourceAccessType type)
{
	SEGFAULTIF(type>2);
	SEGFAULTIF(pipelineStageDescriptorIndex>m_nbStages);
	return m_resourceDescriptorVectorTab[getVectorId(type, pipelineStageDescriptorIndex)];
}

std::string const instruction::debug()
{
	string result;
	for(int type=0; type < 3; type++)
	{
		switch( type ){
			case 0: result += "dep:"; break;
			case 1: result += "rel:"; break;
			case 2: result += "get:";
		}
		for(unsigned int psIndex=0; psIndex < m_nbStages; psIndex++)
		{
			std::vector<resourceDescriptorAccess> &vec = 
				m_resourceDescriptorVectorTab[getVectorId((resourceAccessType)type, psIndex)];
			result += "(ps" + int2str(psIndex) + ":";
			const unsigned int size = vec.size();
			bool start=true;
			for (unsigned int i = 0; i < size; i++) 
			{
				if(!start) result += ",";
				start=false;
				result += (vec[i].resDescriptor)->toString(); //TODO: nbAccess not in debug.
			}
			result+=")";
		}
		result += "\n";
	}
	return result;
}

void instruction::instructionHaveExtraCyclesInStage(pipelineStageDescriptor *psDesc, const unsigned int nbCycle)
{
	extraCycleStageStruct *siss = NULL ;
  macroMyNew (siss, extraCycleStageStruct());
	siss->psDesc = psDesc;
	siss->nbExtraCycle = nbCycle;
	//check for redundancy.
	const unsigned int size = m_nbExtraCyclesVector.size();
	bool found = false;
	for(unsigned int i=0; (i < size) && !found; i++)
		found = ((m_nbExtraCyclesVector[i])->psDesc == psDesc) || found;
	if(!found)	
		m_nbExtraCyclesVector.push_back(siss); //store.
	else 
		cerr << "error: instruction class is defined to stay in a stage more than one time" << endl;
}

unsigned int instruction::getNbExtraCyclesFor(pipelineStageDescriptor *psDesc)
{
	const unsigned int size = m_nbExtraCyclesVector.size();
	for(unsigned int i=0; i < size; i++)
		if((m_nbExtraCyclesVector[i])->psDesc == psDesc) return m_nbExtraCyclesVector[i]->nbExtraCycle;
	return 0; //not found => no extra cycles.
}
