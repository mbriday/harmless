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

#ifndef __PIPELINE_H__
#define __PIPELINE_H__
#include <string>
#include <vector>
#include <ostream> //ostream
#include "utilities/M_machine.h"

typedef unsigned int pipelineState;

class pipelineStageDescriptor;
class resourceDescriptor;
class instructionClass;
class pipelineNotificationData;
class pipelineNotificationEncoder;

class pipeline
{
	///Warning, pipeline stages must be set before instruction classes!!!! 
	//TODO: check this constraint in configuration file.

	///all pipeline stages.
	std::vector<pipelineStageDescriptor *> m_pipelineStageDescriptorVector;
	std::vector<resourceDescriptor *> m_internalResourceDescriptorVector;
	std::vector<resourceDescriptor *> m_externalResourceDescriptorVector;
	std::vector<instructionClass *> m_instructionClassVector;
	std::vector<pipelineNotificationData *> m_pipelineNotificationDataVector;
	
	//nb bits to encode a pipeline stage.
	unsigned int m_nbBits;
	
	const std::string m_name;

	//used by system state to encode pipeline notifications.
	pipelineNotificationEncoder *m_pae;

	public:	
	pipeline(const std::string name);
	~pipeline(void);
	///add a pipeline stage (and call the addResource for the pipeline stage).
	void addStage(pipelineStageDescriptor *ps);
	///add a ressource to the pipeline.
 	void addResourceDescriptor(resourceDescriptor *);
	/// add an notification to the pipeline.
 	void addNotification(pipelineNotificationData *);
	
	///add an instruction class.
	instructionClass *addInstructionClass(const std::string name);

	inline PMUInt const getNumberOfPipelineStages() {return m_pipelineStageDescriptorVector.size();};
 	inline PMUInt const getNbExternalResources() {return m_externalResourceDescriptorVector.size();};
	inline PMUInt const getNbInternalResources() {return m_internalResourceDescriptorVector.size();};
	inline PMUInt const getNbInstructionClasses() {return m_instructionClassVector.size();}; //without any stalls
	inline PMUInt const getNbInstructionClassesIncludeStall() {return m_instructionClassVector.size() + 1;};
	inline PMUInt const getNbPipelineNotificationData() {return m_pipelineNotificationDataVector.size();};

	//index should be less than getNbInstructionClassesIncludeStall.
	std::string getInstructionClassNameforIndex(const unsigned int index);
	
	std::string const debug();

//	std::vector<instructionClass *>::iterator getInstructionClassVectorIteratorBegin() {return m_instructionClassVector.begin();};
//	std::vector<instructionClass *>::iterator getInstructionClassVectorIteratorEnd() {return m_instructionClassVector.end();};

	//index should be less than getNbInstructionClassesIncludeStall.
	instructionClass *getInstructionClass(const unsigned int index);
	inline pipelineNotificationEncoder *getPipelineNotificationEncoder() {return m_pae;};
	pipelineNotificationData *getPipelineNotificationData(const unsigned int index);

	pipelineStageDescriptor *const getPipelineStageDescriptor(const unsigned int index);

	std::vector<resourceDescriptor *> const getInternalResourceDescriptorVector() {return m_internalResourceDescriptorVector;};
	std::vector<resourceDescriptor *> const getExternalResourceDescriptorVector() {return m_externalResourceDescriptorVector;};
	std::string getExtResourceNameForIndex(const PMUInt index);
	
	inline unsigned int const getNbOfBitsToCodeAState() {return m_nbBits;};
	std::string getStringForCode(const PMUInt code);

	void save(std::ostream &output);
};

#endif

