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

#include "pipelineStage.h"
#include "instructionClass.h"
#include "utils.h" //SEGFAULTIF
#include "pipeline.h"
#include <iostream>
using namespace std;

pipelineStageDescriptor::pipelineStageDescriptor(string id) : 
	resourceDescriptor(id,1),
	m_pipeline(NULL),
	m_maxLockedCycle(1)
{
}

pipelineStageDescriptor::~pipelineStageDescriptor()
{
}

void pipelineStageDescriptor::setPipeline(pipeline *pipe)
{
	SEGFAULTIF(m_pipeline); //m_pipeline not NULL!!!
	m_pipeline = pipe;
}

#pragma mark debug

std::string const pipelineStage::debug()
{
	string result = m_desc->toString() + "(" + int2str(m_desc->getMaxNbCyclesLock()) + ")" + ": ";
	if(m_inst) result += m_inst->name();
	else result += "-";
	result += "(" + int2str(m_nbExtracCycles) + ")";
	return result;
}

pipelineStage::pipelineStage() 
 : m_desc(NULL), m_inst(NULL), m_nbExtracCycles(0)
{
}


pipelineStage::~pipelineStage()
{
}

unsigned int const pipelineStage::getCode()
{
	//add 1: 0 is for an empty pipeline stage.
	if(!m_inst) return 0;
	const unsigned int val = m_inst->getIndex();
	return val;
}

void pipelineStage::setInstruction(instructionClass *ic)
{
	//instructionClass may be NULL, for instance when the systemState use the copy constructor
	//with bubbles.
	m_inst = ic;
//	//check if instruction class have to wait more than 1 cycle.
//	if(ic)
//		m_nbExtracCycles = ic->getNbExtraCyclesFor(m_desc);
//	else 
//		m_nbExtracCycles = 0;
}

void pipelineStage::setNbExtraCycles(const unsigned int nbCycles)
{
	m_nbExtracCycles = nbCycles;
}


void pipelineStage::stayOneCycle()
{
	if(m_nbExtracCycles>0) m_nbExtracCycles--; 
}

bool pipelineStage::doesStageNeedExtraCycles() 
{
	return (m_nbExtracCycles==0);
}
