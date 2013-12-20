/** 
 * ac2cpp
 *
 * ac2cpp is copyright (c) IRCCyN 2005+
 * ac2cpp est protege par la loi sur la propriete intellectuelle
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * $Date: 2006-02-28 15:40:26 +0100 (Tue, 28 Feb 2006) $
 * $Rev: 7 $
 * $Author: mik $
 * $URL: https://ac2cpp.rts-software.org/svn/automataConfiguration.h $
 * $Id: automataConfiguration.h 7 2006-02-28 14:40:26Z mik $
 */

#ifndef __AUTOMATACONFIGURATION_H__
#define __AUTOMATACONFIGURATION_H__
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <istream>
#include "utils.h" //hash_length
#include <cassert> //assert
#include "automata.h"

#define AC2AC_FILE_VERSION 3

class automataConfiguration 
{
	std::string m_pipelineName;
	std::vector<std::string> m_pipelineStringVector;
	std::vector<std::string> m_externalResourcesStringVector;
	std::vector<std::string> m_notificationsStringVector;
	std::map<std::string, unsigned int> m_instructionStringMap; 
	
	automata *m_automata;
	
	void readPipeline(std::istream &file);
	void readExternalResources(std::istream &file);
	void readNotifications(std::istream &file);	
	void readInstruction(std::istream &file);
	void readAutomata(std::istream &file);
	
	unsigned int m_nbBitsToCodeOneState;
	std::string m_modelName;

	void checkKey(std::string key, std::istream &file);
	
	public:
	automataConfiguration();
	bool load(const std::string filename);
	std::string modelName() {return m_modelName;};
	
	std::vector<std::string> &getPipelineStringVector() {return m_pipelineStringVector;};
	std::vector<std::string> &getExternalResourcesStringVector() {return m_externalResourcesStringVector;};
	//including '-'
	unsigned int const getNbInstruction() {return m_instructionStringMap.size();};
	unsigned int const getNbExternalResources() {return m_externalResourcesStringVector.size();};
	unsigned int const getNbNotifications() {return m_notificationsStringVector.size();};
	std::string getNotificationString(const unsigned int index) {
		assert(index < getNbNotifications());
		return m_notificationsStringVector[index];
	}

	//std::vector<std::string> &getInstructionStringVector() {return m_instructionStringVector;};
	
//	std::vector<automataState *> &getAutomataStateVector() {return m_automataStateVector;};
//	std::vector<automataEdge *> &getAutomataEdgesVector() {return m_automataEdgesVector;};

	//return the number of bits required to code one pipeline stage, i.e. nb of bits to encode instruction.
	//unsigned int nbBitsToCodeOneStage();
	inline std::string getPipelineName() {return m_pipelineName;};
	inline automata *getAutomata() {return m_automata;};
	inline unsigned int getNbStagesInPipeline() const {return m_pipelineStringVector.size();};
};

#endif
