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

#include <iostream>
#include "utils.h" //SEGFAULTIF
#include <cassert> //assert
#include "pipeline.h"
#include "pipelineStage.h"
#include "instructionClass.h"
#include "pipelineNotification.h"
using namespace std;

#pragma mark configuration
pipeline::pipeline(const std::string name) : 
m_nbBits(0),
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

instructionClass *pipeline::addInstructionClass(const std::string name)
{
	assert(m_pae == NULL); //no pipeline notification encoder should be defined now.
	instructionClass *ic = NULL ;
  macroMyNew (ic, instructionClass(name, this, m_instructionClassVector.size()+1));
	const unsigned int size = m_pipelineStageDescriptorVector.size();
	for(unsigned int i=0; i<size; ++i)
	{
		pipelineStageDescriptor *psDesc=m_pipelineStageDescriptorVector[i];
		ic->resourceAccess(DEPEND,psDesc,psDesc,1);
		ic->resourceAccess(RELEASE,psDesc,psDesc,1);
		ic->resourceAccess(GET,psDesc,psDesc,1);
	}		
	m_instructionClassVector.push_back(ic);

	//recalculate nb bits to code a state.
	//nb cases = nb inst + 1 (no inst).
	//but encode from 0 to nbCases:
	const unsigned int nbIc = m_instructionClassVector.size();
	m_nbBits = 1;
	while(nbIc >> m_nbBits) m_nbBits++;
	return ic;
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
std::string pipeline::getInstructionClassNameforIndex(const unsigned int index)
{
	if(index == 0) return string("-");
	else
	{
		assert((index-1) < m_instructionClassVector.size());
		return m_instructionClassVector[index-1]->name();
	}
}

instructionClass *pipeline::getInstructionClass(const unsigned int index)
{
	if(index == 0) return NULL; //bubble
	else
	{
		assert((index-1) < m_instructionClassVector.size());
		return m_instructionClassVector[index-1];
	}
}

std::string pipeline::getExtResourceNameForIndex(const uint32_t index)
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

std::string pipeline::getStringForCode(const uint32_t code)
{
	if(code == 0) return "-";
	const unsigned int size = m_instructionClassVector.size();
	SEGFAULTIF(code>size);
	instructionClass *ic = m_instructionClassVector[code-1];
	return ic->name();
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
	//instruction classes
	const unsigned int maxIC = m_instructionClassVector.size();
	output << maxIC << " instruction classes";
	for(unsigned int i=0; i< maxIC; i++)
	{
		output << " " << m_instructionClassVector[i]->name();
	}
	output << endl;	
	//notifications
	const unsigned int maxNotification = m_pipelineNotificationDataVector.size();
	output << maxNotification << " notifications";
	for(unsigned int i=0; i< maxNotification; i++)
		output << " " << m_pipelineNotificationDataVector[i]->name();
	output << endl;	
}
