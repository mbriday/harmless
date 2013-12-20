#include "pipelineNotification.h"
#include "pipeline.h"
#include <cassert> //assert
#include <string>
using namespace std;

pipelineNotificationEncoder::pipelineNotificationEncoder(pipeline *pipe)
{
	//Stall (id=0) is replaced to 'any instruction'
	const PMUInt nbInst =  pipe->getNbInstructionClassesIncludeStall();
	const PMUInt nbStage = pipe->getNumberOfPipelineStages();
	m_nbBitsInst  = nbBitsToCodeValue((PMUInt32) nbInst);
	m_nbBitsStage = nbBitsToCodeValue((PMUInt32) nbStage);

	m_codeSize = m_nbBitsStage+m_nbBitsInst+1;
	m_codeSizeAny = m_nbBitsStage+1;


	assert(m_codeSize < (sizeof(hash_length)<<3));
}

C_BDD pipelineNotificationEncoder::getBdd(const unsigned int instructionClassId, const unsigned int stageId, const bool enter)
{
	hash_length code = getNotificationCode(instructionClassId, stageId, enter);
	unsigned int size = m_codeSize;
	if(instructionClassId == 0) size = m_codeSizeAny; //id 0 <=> any instruction.
	C_BDD bdd = C_BDD::varCompareConst (0, size, C_BDD::kEqual, code);
	return bdd;
}

hash_length pipelineNotificationEncoder::getNotificationCode(const unsigned int instructionClassId, const unsigned int stageId, const bool enter)
{
	hash_length code = 0;
	//encoding
	//   CCC - E - SSSS
	//    |    |     |----- stage
	//    |    |---------- enter (1) or exit (0).
	//    |-------------- class id (0 <=> any)

	assert(stageId < (1UL<<m_nbBitsStage));
	assert(instructionClassId < (1UL<<m_nbBitsInst));

	code = stageId;
	code |= (enter << m_nbBitsStage);
	code |= (instructionClassId << (m_nbBitsStage+1));
	
	return code;
}

pipelineNotificationData::pipelineNotificationData(pipeline *pipe, string inName, const unsigned int inClassId, const unsigned int inStageId, const bool enter) :
		m_name(inName),m_classId(inClassId), m_stageId(inStageId), m_enter(enter) 
{
	pipelineNotificationEncoder pa(pipe);
	m_code = pa.getBdd(inClassId, inStageId, enter);
}
