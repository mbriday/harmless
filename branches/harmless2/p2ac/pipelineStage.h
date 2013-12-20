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

#ifndef __PIPELINESTAGE_H__
#define __PIPELINESTAGE_H__

#include <vector>
#include <list>
#include <string>
#include "utils.h" //MAX
#include "resource.h"

class instruction;
class pipeline;

class pipelineStageDescriptor : public resourceDescriptor
{		
	pipeline *m_pipeline;
	//index of the pipeline stage (must be equal to the index in the vector of the pipeline object).
	unsigned int m_psId;
	//get the max number of cycle the stage may be locked.
	//This information is required to determine how many bits are required to code a state.
	//This is the exact value => at least 1 cycle.
	unsigned int m_maxLockedCycle;
	
	public:
	virtual ~pipelineStageDescriptor();
	pipelineStageDescriptor(const std::string id);

	void setPipeline(pipeline *pipe);
	inline pipeline * const getPipeline() {return m_pipeline;};
	
	//called only one time when the spage is inserted in the pipeline structure.
	void setIndex(const unsigned int val) {m_psId = val;};
	unsigned int const getIndex() {return m_psId;};

	void stageMayBeLockedAtLeast(const unsigned int nbCycles) {
		m_maxLockedCycle = MAX(m_maxLockedCycle, nbCycles);
	};
	// remove 1 unit, because, each inst stays at least 1 cycle.
	unsigned int const getNbBitsToCodeStageExtraCycles() 
	{
		return nbBitsToCodeValue(m_maxLockedCycle);
	};
	unsigned int const getMaxNbCyclesLock() { return m_maxLockedCycle; };
};

class pipelineStage
{
	pipelineStageDescriptor *m_desc;
	///store the instruction.
	instruction * m_inst;
	unsigned int m_pc;
	//get the number of cycles the stage is locked.
	unsigned int m_nbExtracCycles;
	
	public:
	~pipelineStage();

	pipelineStage();
	inline void setPipelineStageDescriptor(pipelineStageDescriptor *desc) {m_desc = desc;};
	
	inline pipelineStageDescriptor * const descriptor() {return m_desc;};
	
	std::string const debug();
	
	void setInstruction(instruction *inst);
	inline instruction * const getInstruction() {return m_inst;};
	inline void removeInstruction() {m_inst = NULL;};
	
	unsigned int const getCode();
	unsigned int getPC() {return m_pc;};
	void setPC(unsigned int pc) {m_pc=pc;};
	///this method is used by systemState getNext to check is the stage is locked
	///because an instruction require more than 1 cycle to execute.
	void stayOneCycle();
	bool doesStageNeedExtraCycles();
	inline unsigned int const getNbExtraCycles() { return m_nbExtracCycles;};
	void setNbExtraCycles(const unsigned int nbCycles);

};
#endif

