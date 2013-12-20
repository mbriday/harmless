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


#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__
#include <string>
#include <vector>

class resourceDescriptor;
class pipelineStageDescriptor;
class instructionDescription;

/** DO NOT change values. They are used in "instruction class" class by numbers!! */
enum resourceAccessType {DEPEND=0, RELEASE=1, GET=2};

/** The resource access is used by instruction classes. An instruction can depend, 
 * get or release an instruction
 *  more than just one time in the pipeline stage. So we have to store how many times the 
 * resource is used by the instruction in the pipeline stage.
 */
struct resourceDescriptorAccess {
	resourceDescriptor *resDescriptor;
	unsigned int nbAccess;
	resourceDescriptorAccess(resourceDescriptor *res, const unsigned int nb) : resDescriptor(res), nbAccess(nb) {};
	bool operator==(const resourceDescriptorAccess &rda) const 
	{return (rda.resDescriptor == resDescriptor) && (rda.nbAccess == nbAccess);}
};

struct extraCycleStageStruct
{
	pipelineStageDescriptor *psDesc;
	int nbExtraCycle;
};

/** model of an instruction class. 
 * It stores the ressources that are given/depended/get 
 * and the dependancies. 
 */
class instruction
{
private:
	/**
	 *the first vector contains the resources which the instruction DEPEND (and the associated 
	 *pipeline stage. The second vector is RELEASE, and the last is GET (as in the resourceAccessType enum).
	 */
	//std::vector<resPS> m_resourceDescriptorVector[3];
	
	/** contains type*nbPipelineStages vectors. type may be either DEPEND, RELEASE and GET. 
	 *  Each vector contains the ressources that are accessed with the 'type' at the 
	 *  'pipline stage' considered
	 */
	std::vector<resourceDescriptorAccess> *m_resourceDescriptorVectorTab;
	
	//number of pipeline stages (->number of vector = 3* m_nbStages);
	const unsigned int m_nbStages;
	
	const std::string m_name;

	//index of the instruction class (must be equal to the index in the vector of the pipeline object).
	const unsigned int m_psId;
	unsigned int m_pc;
	std::string m_mnemo;
	///set stages where the instruction have to wait more than one cycle.
	std::vector<extraCycleStageStruct *> m_nbExtraCyclesVector;

	inline unsigned int const getVectorId(const resourceAccessType type, const unsigned int psIndex)
				{ return m_nbStages*(int)type+psIndex;};
	
public:
	///add a resource the instruction depends on/gets/give.
	void resourceAccess(const resourceAccessType type, resourceDescriptor *, pipelineStageDescriptor *, const unsigned int nbAccess);

	instruction(const std::string m_name, pipeline *, unsigned int id);
	~instruction();
	
	std::vector<resourceDescriptorAccess> &getResourceDescriptorVector(
					const unsigned int pipelineStageDescriptorIndex, 
					const resourceAccessType type);

	std::string const debug();
	inline std::string const name() {return m_name;};
	
	inline unsigned int const getIndex() {return m_psId;};
	void instructionHaveExtraCyclesInStage(pipelineStageDescriptor *psDesc, const unsigned int nbCycle);
	unsigned int getNbExtraCyclesFor(pipelineStageDescriptor *psDesc);
	unsigned int getPC(){return m_pc;};
	void setPC(unsigned int pc){m_pc = pc;};
	std::string getMnemo(){return m_mnemo;};
	void setMnemo(std::string mnemo){m_mnemo = mnemo;};
};

#endif

