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

#ifndef __programDescription_H__
#define __programDescription_H__
#include <string>
#include <vector>
#include <fstream>
#include "utilities/M_machine.h"
#include <map>

class instructionDescription;

class programDescription {
	private:
		unsigned int m_start;
		std::map<unsigned int, instructionDescription *> m_idMap;
	
	public:
		programDescription();
		~programDescription();
		std::map<unsigned int, instructionDescription *> getInstructionDescriptionMap(){return m_idMap;};
		void addInstructionDescription(unsigned int pc, instructionDescription *id);
		unsigned int getStart(){return m_start;};
		
		void setStart(unsigned int start){m_start = start;};
		bool load(const std::string filename);
		void showIdMap();
};
	
static unsigned int hexaToBin(std::string);

#endif
