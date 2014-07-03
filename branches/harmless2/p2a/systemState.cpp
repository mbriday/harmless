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
 #include <iostream> //cerr
 #include <cassert> //assert
 #include "systemState.h"
 #include "pipeline.h"
 #include "pipelineStage.h"
 #include "instructionClass.h"
 #include "pipelineNotification.h"
 #include "utils.h" //SEGFAULTIF
 using namespace std;

extern bool verbose;

int systemState::s_nbStates = 0;
pipeline *systemState::s_pipeline = NULL;
	
systemState::systemState(pipeline *pipe) : 

m_stateCode(0),
m_stateCodeComputed(false)
{
	if(!s_pipeline) s_pipeline = pipe; 
	s_nbStates++;
	//init with all external resources not taken;
	std::vector<resourceDescriptor *> eVec = pipe->getExternalResourceDescriptorVector();
	const uint32_t extSize = eVec.size();
	m_externalResourceVector = NULL ;
	if(extSize > 0)
		macroMyNewArray (m_externalResourceVector, resource, extSize);
	for(uint32_t i = 0; i < extSize; i++) 
	{	
		m_externalResourceVector[i].setResourceDescriptor(eVec[i]);
		m_externalResourceVector[i].setTaken(0);
	}
	
	//init with all internal resources not taken;
	std::vector<resourceDescriptor *> iVec = pipe->getInternalResourceDescriptorVector();
	const uint32_t intSize = iVec.size();
	m_internalResourceVector = NULL ;
	if(intSize > 0)
		macroMyNewArray (m_internalResourceVector, resource, intSize);
	for(uint32_t i = 0; i < intSize; i++) 
	{	
		m_internalResourceVector[i].setResourceDescriptor(iVec[i]);
		m_internalResourceVector[i].setTaken(0);
	}

	const uint32_t nbPS = s_pipeline->getNumberOfPipelineStages();
//	m_pipelineStageVector = new pipelineStage*[nbPS];
//	for(uint32_t i = 0; i < nbPS; i++) 
//		m_pipelineStageVector[i] = new pipelineStage(s_pipeline->getPipelineStageDescriptor(i));

	m_pipelineStageVector = NULL ;
	macroMyNewArray (m_pipelineStageVector, pipelineStage, nbPS);
	for(uint32_t i = 0; i < nbPS; i++) 
		m_pipelineStageVector[i].setPipelineStageDescriptor(s_pipeline->getPipelineStageDescriptor((uint32_t) i));
}

systemState::~systemState()
{
	macroMyDeleteArray (m_externalResourceVector);
	macroMyDeleteArray (m_internalResourceVector);
	macroMyDeleteArray (m_pipelineStageVector);

	//cout << "delete system state : " << getHashCode(STATE) << endl;
}
	
#pragma mark simulate

resource *const systemState::getResourceFrom(resourceDescriptor *resDesc)
{
	bool found = false;
	resource *result = NULL;
	uint32_t index = 0;
	if(resDesc->isExternal())
	{
		const uint32_t size = s_pipeline->getNbExternalResources();
		while(!found && (index < size))
		{
			result = &(m_externalResourceVector[index++]);
			found = (result->descriptor() == resDesc);
		}
	} else {
		const uint32_t size = s_pipeline->getNbInternalResources();
		while(!found && (index < size))
		{
			result = &(m_internalResourceVector[index++]);
			found = (result->descriptor() == resDesc);
		}		
	}
	SEGFAULTIF(!found);
	return result;
}

void systemState::getResources(instructionClass *ic, pipelineStageDescriptor *psDesc)
{
	//cout << ic->debug() << endl;
	std::vector<resourceDescriptorAccess> &vec = ic->getResourceDescriptorVector(psDesc->getIndex(),GET);
	const uint32_t size = vec.size();
	for(uint32_t resIndex = 0;resIndex<size; resIndex++)
	{
		resourceDescriptorAccess rda = vec[resIndex];
		//get the resource object
		resource *res = getResourceFrom(rda.resDescriptor);
		//get the resource.
		res->take(rda.nbAccess);
	}
}


void systemState::releaseResources(instructionClass *ic, pipelineStageDescriptor *psDesc)
{
	//cout << ic->debug() << endl;
	std::vector<resourceDescriptorAccess> &vec = ic->getResourceDescriptorVector(psDesc->getIndex(),RELEASE);
	const uint32_t size = vec.size();
	for(uint32_t resIndex = 0;resIndex<size; resIndex++)
	{
		resourceDescriptorAccess rda = vec[resIndex];
		//get the resource object
		resource *res = getResourceFrom(rda.resDescriptor);
		//release the resource.
		res->give(rda.nbAccess);
	}
}

bool const systemState::checkDependResource(instructionClass *ic, pipelineStageDescriptor *psDesc)
{
	bool ok = true;
	//cout << ic->debug() << endl;
	std::vector<resourceDescriptorAccess> &vec = ic->getResourceDescriptorVector(psDesc->getIndex(),DEPEND);
	const uint32_t size = vec.size();
	//for each resource that is necessary for the instruction class
	uint32_t resIndex = 0;
	while(ok && (resIndex < size))
	{
		resourceDescriptorAccess rda = vec[resIndex];
		//check that the resource is available.
		resource *res = getResourceFrom(rda.resDescriptor);
		ok = res->isAvailable(rda.nbAccess);
		//if the resource is not available, stop the loop.
		resIndex++;
	}
	return ok;
}

systemState::systemState(const systemState &st)
{
	m_stateCodeComputed = st.m_stateCodeComputed;
	m_stateCode = st.m_stateCode;
	//s_pipeline = st.s_pipeline; -> static.
	s_nbStates++;
	//external resources
	const uint32_t extSize = s_pipeline->getNbExternalResources();
	m_externalResourceVector = NULL ;
	if(extSize > 0) 
		macroMyNewArray (m_externalResourceVector, resource, extSize);
	for(uint32_t i = 0; i < extSize; i++) 
	{
		resource &res = st.m_externalResourceVector[i];
		m_externalResourceVector[i].setResourceDescriptor(res.descriptor());
		m_externalResourceVector[i].setTaken(res.taken());
	}
	//internal resources
	const uint32_t intSize = s_pipeline->getNbInternalResources();
	m_internalResourceVector = NULL ;
	if(intSize > 0) 
		macroMyNewArray (m_internalResourceVector, resource, intSize);
	for(uint32_t i = 0; i < intSize; i++) 
	{
		resource &res = st.m_internalResourceVector[i];		
		m_internalResourceVector[i].setResourceDescriptor(res.descriptor());
		m_internalResourceVector[i].setTaken(res.taken());
	}
	//pipeline stages
	const uint32_t nbPS = s_pipeline->getNumberOfPipelineStages();
	m_pipelineStageVector = NULL ;
	macroMyNewArray (m_pipelineStageVector, pipelineStage, nbPS);
	for(uint32_t i = 0; i < nbPS; i++) 
	{
		pipelineStage &ps=st.m_pipelineStageVector[i];
		m_pipelineStageVector[i].setPipelineStageDescriptor(ps.descriptor());
		m_pipelineStageVector[i].setInstruction(ps.getInstruction());
		m_pipelineStageVector[i].setNbExtraCycles(ps.getNbExtraCycles());
	}
}

void systemState::setExternalRessources(unsigned int mask)
{
	const uint32_t size = s_pipeline->getNbExternalResources();
	//cout << "avant setExternalRessources:" << debug() << flush;
	for(uint32_t i=0; i<size; ++i)
	{
		m_externalResourceVector[i].setTaken(mask & 0x1);
		mask >>= 1;
	}
	//cout << "apres setExternalRessources:" << debug() << flush;
	m_stateCodeComputed = false;
}


//Be careful: A stall that enters in the pipeline is NEVER blocked.
//            should be taken into account when with the calculus of the number 
//            of instructions that enters in the pipeline.
systemState *systemState::getNext(instructionClass *nextInst, C_BDD &notification)
{
	systemState *next = NULL ;
  macroMyNew (next, systemState(*this)); //init with a 'retain'
	//hash_inst_move inst_move = 0; //deprecated. For debug now only.
	pipelineNotificationEncoder *pae = s_pipeline->getPipelineNotificationEncoder();
	const int32_t nbPipelineStage = (int32_t) s_pipeline->getNumberOfPipelineStages();
	
	//for each pipeline stage, from the end to the beginning
	for(int32_t psIndex = nbPipelineStage-1; psIndex>=-1; psIndex--)
	{
		pipelineStage *ps = NULL;
		if(psIndex>=0) ps = &(next->m_pipelineStageVector[psIndex]);

		const int32_t psNextIndex = psIndex+1;
		pipelineStage *psNext = NULL;
		if(psNextIndex < (int)nbPipelineStage) psNext = &(next->m_pipelineStageVector[psNextIndex]);

		instructionClass *ic;
		if(ps) ic = ps->getInstruction(); //may be NULL;
		else ic = nextInst;
		
		if(ic)
		{
			//check if the instruction can make a step
			//resources in the next stage can be taken?
			bool okResource = true;
			//should the instruction class stay in current stage more than one cycle?
			bool okNoExtraCycle = true;
			if(psNext) //there is a next stage.
			{
				okResource = next->checkDependResource(ic, psNext->descriptor());
				if(ps) {
					okNoExtraCycle = ps->doesStageNeedExtraCycles();
					ps->stayOneCycle();
				}
			}
			if(okResource && okNoExtraCycle)
			{
				//all is ok. The instruction can give back its ressources
				if(ps) next->releaseResources(ic, ps->descriptor());
				//set the instruction in the next stage...if there is a next stage.
				if(psNext)
				{
					//add the instruction in the next stage
					psNext->setInstruction(ic);
					psNext->setNbExtraCycles(ic->getNbExtraCyclesFor(psNext->descriptor())); //ic not NULL
					//get the resources required in the new pipeline stage.
					next->getResources(ic, psNext->descriptor());
					//the instruction can be executed in the stage.
					//compute the associated notification (enter in stage psNext)
					notification |= pae->getBdd(ic->getIndex(), (uint32_t) psNextIndex , true);
					
				}
				if(ps) 
				{
					//remove the instruction in that pipeline stage.
					ps->setInstruction(NULL);
					//compute the associated notification (leave stage ps)
					notification |= pae->getBdd(ic->getIndex(), (uint32_t) psIndex , false);
				}
				//the stage has an instruction that moves now.
				//inst_move |= 1 << psNextIndex;
			}
		}
	}
	//cout << "notification (" << inst_move << ") : "; printBDD(notification); cout << endl;
	next->m_stateCodeComputed = false;
	return next;
}

#pragma mark hash code

std::string systemState::getStringFromCode(pipeline *pipe, hash_length code,HASH_CODE_TYPE type, bool p2aOutput, hash_length irrelevantMask)
{
	string result;
	//bool start = true;
	
	if(type == TRANSITION)
	{
		//decode external ressources state.
		const uint32_t eRsize = pipe->getNbExternalResources();
		for(uint32_t i=0; i<eRsize; ++i)
		{
			bool taken = (code & 0x1);
			bool irrelevant = (irrelevantMask & 0x1);
			if(p2aOutput) result += " ";
			if(p2aOutput) 
			{
				if(irrelevant) result += "0";
				else if(taken) result += "1";
				else result += "2";
			} else {
				if(irrelevant) result += "X";
				else 
				{
					if(taken) result += "/";
					result += pipe->getExtResourceNameForIndex(i);
				}
			}
			code >>= 1;
			irrelevantMask >>=1;
		}
		//instruction fetched.
		string fetchedInst;
		if(p2aOutput) 
		{
			if(irrelevantMask) fetchedInst = "0";
			else fetchedInst = int2str(code);
		} else {
			if(irrelevantMask) fetchedInst = "X";
			else fetchedInst = pipe->getStringForCode(code);
			fetchedInst += ", ";
		}
		result = fetchedInst + result;
		
	} else //type = STATE
	{
		//decode pipeline state
		const uint32_t size = pipe->getNumberOfPipelineStages();
		const uint32_t nbBit = pipe->getNbOfBitsToCodeAState();
		const hash_length mask = (1 << nbBit) - 1;
		for(uint32_t i=0; i < size; i++)
		{
			//if(!start) result+= " ";
			//start = false;
			
			string currentStage;
			
			int psCode = (int)(code & mask); //can change from hash_length to int.
			int psCodeIrrelevantMask = (int)(irrelevantMask & mask);
			if(psCodeIrrelevantMask) currentStage = "X";
			else currentStage = pipe->getStringForCode(psCode);
			
			result = currentStage + result;
			code >>= nbBit;
			irrelevantMask >>= nbBit;
		}
	}
	return result;
}

hash_length const systemState::getStateHashCode()
{
	hash_length code = 0;
    if(m_stateCodeComputed) code = m_stateCode;
	else
    {
        //encode pipeline state
        const uint32_t size = s_pipeline->getNumberOfPipelineStages();
        const uint32_t nbBit = s_pipeline->getNbOfBitsToCodeAState();
        for(uint32_t i=0; i < size; i++)
        {
			const uint32_t psCode = m_pipelineStageVector[i].getCode();
			code <<= nbBit;
            code |= psCode;
        }
		//new, it now encodes wait cycles in pipeline stages.
        for(uint32_t i=0; i < size; i++)
        {
			const uint32_t nb = m_pipelineStageVector[i].getNbExtraCycles();
			const uint32_t nbBits = (m_pipelineStageVector[i].descriptor())->getNbBitsToCodeStageExtraCycles();
			
			code <<= nbBits;
			assert(nb < (1U<<nbBits));
			assert(nb >= 0);
            code |= nb;
        }
		
		m_stateCodeComputed = true;
		m_stateCode = code;
    }
    return code;
}

uint32_t const systemState::getNbBitsForStateCode()
{
	return getNbBitsForStateCode(s_pipeline);
}

uint32_t systemState::getNbBitsForStateCode(pipeline *pipe)
{
	const unsigned int nbBit = pipe->getNbOfBitsToCodeAState();
	const unsigned int size = pipe->getNumberOfPipelineStages();
	unsigned int nbBitsRequired = nbBit*size; //one inst for each pipeline stage.
	
	unsigned int nbExtra = 0;
	for(unsigned int i=0; i < pipe->getNumberOfPipelineStages(); i++)
	{
		pipelineStageDescriptor *ps = pipe->getPipelineStageDescriptor(i);
		nbExtra += ps->getNbBitsToCodeStageExtraCycles();;
	}
	
	return nbBitsRequired+nbExtra;
}

unsigned int systemState::getNbBitsForTransitionCode()
{
	unsigned int nbBitsRequired = s_pipeline->getNbExternalResources(); //external ressource
	nbBitsRequired += s_pipeline->getNbOfBitsToCodeAState(); //inst code that is fetched.
	return nbBitsRequired;
}


void const systemState::checkHashCodeLength()
{
//	const unsigned int nbBitsRequiredCompact = getNbBitsForStateCode();
	const unsigned int nbBitsRequiredFull = getNbBitsForTransitionCode();

	if(nbBitsRequiredFull > (sizeof(hash_length)<<8))
	{
		//full code takes always more space  
		cerr << "error: Can not encode system state! It needs " 
			<< nbBitsRequiredFull << " bits but hash code is coded with " 
			<< sizeof(hash_length)<<8 << " bits" << endl;
		SEGFAULTIF(true);
	} 
	//else 
	//{
	//	if(verbose) cerr << "system state needs " << nbBitsRequiredCompact 
	//					 << " bits for encoding states"<<endl 
	//					 << "system state needs " << nbBitsRequiredFull 
	//					 << " bits for encoding transitions"<<endl;
	//}
}

#pragma mark debug
string const systemState::debug()
{
	string result;
	const unsigned int size = s_pipeline->getNumberOfPipelineStages();
	for(unsigned int i=0; i < size; i++)
	{
		result += m_pipelineStageVector[i].debug();
		result += '\n';
	}
	result += "exec:";
//	for(unsigned int i=0; i < size; i++) 
//	{
//		if(m_stageExecution[i]) 
//			result+='1';
//		else result+='0';
//	}
	result += '\n';
	result += "system state code is : 0x" + int2str(getStateHashCode(),HEX) + '\n';
	return result;
}
