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

#ifndef __SYSTEMCONFIGURATION_H__
#define __SYSTEMCONFIGURATION_H__
#include <string>
#include <vector>
#include <fstream>
#include "utilities/M_machine.h"

class pipeline;
class resourceDescriptor;
class instructionClass;
class pipelineStageDescriptor;
class instructionClass;
class instructionClassPerPipelineStage;
//class dataDependencyInstructionClass;

/**
store the configuration of the pipeline (ressources, instruction classes, pipeline stages, ..)
*/
class systemConfiguration
{
	//this boolean is used to check that no instruction class nor pipeline stage is defined AFTER an notification.
	//it is set to true when the first notification is defined.
	bool m_NotificationDefined;
	//used for reading the file. store symbols.
	std::string m_pipelineName;
	std::vector<std::string> m_resourceDescriptorNameVector;
	std::vector<std::string> m_instructionClassNameVector;
	std::vector<std::string> m_pipelineStageDescriptorNameVector;
	std::vector<std::string> m_DapaDependencyInstructionClassNameVector;
	
	//store the whole configuration of the system.
	pipeline * m_pipeline;
	std::vector<resourceDescriptor *> m_resourceDescriptorVector;
	std::vector<instructionClass *> m_instructionClassVector;
	std::vector<pipelineStageDescriptor *> m_pipelineStageDescriptorVector;
//	std::vector<dataDependencyInstructionClass *> m_DapaDependencyInstructionClassVector;
	
	std::string m_modelName;
	
	int getIndexInVector(std::vector<std::string> &vec, std::string str);
	void processSymbol(std::string &symbol, std::ifstream &file);
	bool processCommand(const std::string command, std::ifstream &file);
	void processSymbolPipeline(std::ifstream &file);
	void processSymbolInstructionClass(int index, std::ifstream &file);
//	void processSymbolDapaDependencyInstructionClass(int index, std::ifstream &file);

	void processCommandAddNotification(std::ifstream &file);

	public:
	systemConfiguration() : m_NotificationDefined(false), m_pipeline(NULL) {};
	~systemConfiguration();
	
	///return true if file is ok.
	bool load(const std::string filename);

	PMUInt const getNumberOfResources() {return m_resourceDescriptorVector.size();};
	PMUInt const getNumberOfInstructionClasses() {return m_instructionClassVector.size();};
	PMUInt const getNumberOfPipelineStages() {return m_pipelineStageDescriptorVector.size();};

	unsigned int const getNumberOfExternalResources();
	
	std::string modelName() {return m_modelName;};
	//test:
	pipeline *getPipeline() {return m_pipeline;};
	std::vector<instructionClass *> &getInstructionVector() {return m_instructionClassVector;};
//	std::vector<dataDependencyInstructionClass *> &getDataDependencyInstructionVector() {return m_DapaDependencyInstructionClassVector;};

};
	
#endif
