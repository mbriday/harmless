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
#include <stack>
class pipeline;
class instruction;

//using namespace std;
//typedef hash_set<hash_length, hash<hash_length>, Equal_to<hash_length> > codeSet;
//typedef __gnu_cxx::hash_set<hash_length> codeSet;

class systemState
{
	//info. number of states calculated.
	static int s_nbStates;
	
	//pipeline stages (contains the instructions).
	resource *m_externalResourceVector;
	resource *m_internalResourceVector;
	pipelineStage *m_pipelineStageVector;
	unsigned int m_pc;
	std::stack<unsigned int> m_pcStack;
	
	static pipeline *s_pipeline;

	bool m_stateCodeCalculated, m_transitionCodeCalculated;
	hash_length m_stateCode;
	//bit field that store 
	//if state code is calculated (bit 0)
	//if transition code is calculated (bit 2)
	bool m_stateCodeComputed;

	resource *const getResourceFrom(resourceDescriptor *resDesc);
	void releaseResources(instruction *inst, pipelineStageDescriptor *psDesc);
	void getResources(instruction *inst, pipelineStageDescriptor *psDesc);

	bool const checkDependResource(instruction *inst, pipelineStageDescriptor *psDesc);

	public:
	unsigned int getPC(){return m_pc;};
	void setPC(unsigned int pc){m_pc = pc;};
	void popPCStack();
	unsigned int topPCStack();
	void pushPCStack(unsigned int pc);
	std::stack<unsigned int> getPCStack(){return m_pcStack;};
	bool isPCStackEmpty(){return m_pcStack.empty();};
	int getPCStackSize(){return m_pcStack.size();};
	~systemState();
	int static nbStates() {return s_nbStates;};
	enum HASH_CODE_TYPE {STATE, TRANSITION};
	systemState(const systemState &st);
	
	systemState(pipeline *pipe);
	
	void setExternalRessources(unsigned int mask);

	//calculate the next system state.
	systemState *getNext(instruction *inst, C_BDD &notification, unsigned int previousPC, unsigned int nextPC);
	//check that the hash_length type contains enough bits to encode the codes (compact/full).
	void const checkHashCodeLength();
	PMUInt const getNbBitsForStateCode();
	static PMUInt  getNbBitsForStateCode(pipeline *pipe);
	//get the hash code of the state. The hash code encodes the pipeline state and external ressources. The hash code is calculated only one time. The code is then stored.
	hash_length const getStateHashCode();
	unsigned int getNbBitsForTransitionCode();

	std::string static getStringFromCode(pipeline *pipe, hash_length code,HASH_CODE_TYPE type,bool p2acOutput=false,hash_length irrelevantMask=0);

	std::string const debug();
	int compare(systemState *s);
	std::string pipelinePrint();
};

#endif
