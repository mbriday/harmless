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

#include <iostream>
#include "utils.h" //SEGFAULTIF
#include <cassert> //assert
#include "pipeline.h"
#include "pipelineStage.h"
#include "instruction.h"
#include "instructionDescription.h"
#include "pipelineNotification.h"
using namespace std;

#pragma mark configuration
pipeline::pipeline(const std::string name) : 
//TODO: Find a better way to initialise the nbBits. It was initialised with 0, before. It allows to know the nb of bits needed to code an instruction.
m_nbBits(32),
m_name(name),
m_pae(NULL)
{}

pipeline::~pipeline() {
	macroMyDelete (m_pae) ;
}

void pipeline::addStage(pipelineStageDescriptor *ps)
{
	assert(m_pae == NULL); //no pipeline notification encoder should be defined now.
 	bool found = false;
	unsigned int i = 0;
	//check if stage is not already defined!
	const unsigned int size = m_pipelineStageDescriptorVector.size();
	while( (i<size) && !found)
		found = (ps == m_pipelineStageDescriptorVector[i++]);
	if(!found)
	{
		addResourceDescriptor(ps); //a pipeline stage is a resource!!
		m_pipelineStageDescriptorVector.push_back(ps);
		ps->setIndex(m_pipelineStageDescriptorVector.size() - 1);
	}
}

void pipeline::addResourceDescriptor(resourceDescriptor *res)
{
	if(res->isExternal())
	{
		m_externalResourceDescriptorVector.push_back(res);
	} else {
		m_internalResourceDescriptorVector.push_back(res);
	}
}

void pipeline::addNotification(pipelineNotificationData *pad)
{
	if(!m_pae)
		macroMyNew (m_pae, pipelineNotificationEncoder(this));
	m_pipelineNotificationDataVector.push_back(pad);
	//debug
	//cout << "notification " << pad->name() << " : ";
	//C_BDD code = pad->code();
	//printBDD(code);
	//cout << endl;
}

instruction *pipeline::addInstructionClass(const std::string name)
{
	assert(m_pae == NULL); //no pipeline notification encoder should be defined now.
	instruction *inst = NULL ;
	macroMyNew (inst, instruction(name, this, m_instructionVector.size()+1));
	const unsigned int size = m_pipelineStageDescriptorVector.size();
	for(unsigned int i=0; i<size; ++i)
	{
		pipelineStageDescriptor *psDesc=m_pipelineStageDescriptorVector[i];
		inst->resourceAccess(DEPEND,psDesc,psDesc,1);
		inst->resourceAccess(RELEASE,psDesc,psDesc,1);
		inst->resourceAccess(GET,psDesc,psDesc,1);
	}		
	m_instructionVector.push_back(inst);

	//recalculate nb bits to code a state.
	//nb cases = nb inst + 1 (no inst).
	//but encode from 0 to nbCases:
	const unsigned int nbInst = m_instructionVector.size();
	//while(nbInst >> m_nbBits) m_nbBits++;
	return inst;
}

#pragma mark debug
string const pipeline::debug()
{
	string result;
	const unsigned int size = m_pipelineStageDescriptorVector.size();
	for(unsigned int i=0; i < size; i++)
	{
		for(unsigned int j = 0; j<i;j++) result += '\t';
		result += m_pipelineStageDescriptorVector[i] -> toString() + '\n';
	}
	return result;
}

#pragma mark accessor
std::string pipeline::getInstructionNameforIndex(const unsigned int index)
{
	if(index == 0) return string("-");
	else
	{
		assert((index-1) < m_instructionVector.size());
		return m_instructionVector[index-1]->name();
	}
}

instruction *pipeline::getInstruction(instructionDescription *instd) {
	unsigned int index = instd->getIdClass();
	if(index == 0) {
		cerr << "Error: id class of " << instd->getMnemo() << " is null!" << endl;
		return NULL;
	} //bubble
	else {
		assert((index-1) < m_instructionVector.size());
		//We ask informations in the pipeline.
		instruction *inst = m_instructionVector[index-1];
		//We put inside informations from the analysed program. In fact, we don't use the mnemo in the inst.
		inst->setMnemo(instd->getMnemo());
		//inst->resourceAccess(DEPEND,instd->setResourcesRead(),ps,1);
		return inst;
	}
}

std::string pipeline::getExtResourceNameForIndex(const PMUInt index)
{
	SEGFAULTIF(index>m_externalResourceDescriptorVector.size());
	return m_externalResourceDescriptorVector[index]->toString();
}

pipelineNotificationData *pipeline::getPipelineNotificationData(const unsigned int index)
{
	assert(index<m_pipelineNotificationDataVector.size());
	return m_pipelineNotificationDataVector[index];
}


pipelineStageDescriptor *const pipeline::getPipelineStageDescriptor(const unsigned int index)
{
	SEGFAULTIF(index>getNumberOfPipelineStages());
	return m_pipelineStageDescriptorVector[index];
}

std::string pipeline::getStringForCode(const PMUInt code)
{
	if(code == 0) return "-";
	const unsigned int size = m_instructionVector.size();
	SEGFAULTIF(code>size);
	instruction *inst = m_instructionVector[code-1];
	return inst->name();
}

#pragma mark export
void pipeline::save(ostream &output)
{
	//pipeline name
	output << "pipeline " << m_name << " with";
	//pipeline stages architecture.
	const unsigned int maxPS = m_pipelineStageDescriptorVector.size();
	output << " " <<maxPS << " stages";
	for(unsigned int i=0; i< maxPS; i++)
	{
		output << " " << m_pipelineStageDescriptorVector[i]->toString();
	}
	output << endl;
	//external resources
	const unsigned int maxER = m_externalResourceDescriptorVector.size();
	output << maxER << " external resources";
	for(unsigned int i=0; i< maxER; i++)
	{
		output << " " << m_externalResourceDescriptorVector[i]->toString();
	}
	output << endl;	
	//instruction
	const unsigned int maxInst = m_instructionVector.size();
	output << maxInst << " instruction";
	for(unsigned int i=0; i< maxInst; i++)
	{
		output << " " << m_instructionVector[i]->name();
	}
	output << endl;	
	//notifications
	const unsigned int maxNotification = m_pipelineNotificationDataVector.size();
	output << maxNotification << " notifications";
	for(unsigned int i=0; i< maxNotification; i++)
		output << " " << m_pipelineNotificationDataVector[i]->name();
	output << endl;	
}
