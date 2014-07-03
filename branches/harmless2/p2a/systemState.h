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
 
#ifndef __SYSTEMSTATE_H__
#define __SYSTEMSTATE_H__
#include <vector>
#include "resource.h"
#include <list>
#include <string> //debug
//#include <ext/hash_set>
#include <functional>
#include "pipelineStage.h"
#include "utils.h"
class pipeline;
class instructionClass;

//using namespace std;
//typedef hash_set<hash_length, hash<hash_length>, Equal_to<hash_length> > codeSet;
//typedef __gnu_cxx::hash_set<hash_length> codeSet;

class systemState
{
	//info. number of states calculated.
	static int s_nbStates;
	
	//pipeline stages (contains the instructions classes).
	pipelineStage *m_pipelineStageVector;
	resource *m_externalResourceVector;
	resource *m_internalResourceVector;
	
	static pipeline *s_pipeline;

	bool m_stateCodeCalculated, m_transitionCodeCalculated;
	hash_length m_stateCode;
	//bit field that store 
	//if state code is calculated (bit 0)
	//if transition code is calculated (bit 2)
	bool m_stateCodeComputed;

	resource *const getResourceFrom(resourceDescriptor *resDesc);
	void releaseResources(instructionClass *ic, pipelineStageDescriptor *psDesc);
	void getResources(instructionClass *ic, pipelineStageDescriptor *psDesc);

	bool const checkDependResource(instructionClass *ic, pipelineStageDescriptor *psDesc);

	public:
	~systemState();
	int static nbStates() {return s_nbStates;};
	enum HASH_CODE_TYPE {STATE, TRANSITION};
	systemState(const systemState &st);
	
	systemState(pipeline *pipe);
	
	void setExternalRessources(unsigned int mask);

	//calculate the next system state.
	systemState *getNext(instructionClass *, C_BDD &notification);
	//check that the hash_length type contains enough bits to encode the codes (compact/full).
	void const checkHashCodeLength();
	uint32_t const getNbBitsForStateCode();
	static uint32_t  getNbBitsForStateCode(pipeline *pipe);
	//get the hash code of the state. The hash code encodes the pipeline state and external ressources. The hash code is calculated only one time. The code is then stored.
	hash_length const getStateHashCode();
	unsigned int getNbBitsForTransitionCode();

	std::string static getStringFromCode(pipeline *pipe, hash_length code,HASH_CODE_TYPE type,bool p2aOutput=false,hash_length irrelevantMask=0);

	std::string const debug();
};

#endif
