/*
 *  fileHeaderGeneration.h
 *  ac2cpp
 *
 *  Created by Mikaël Briday on 02/12/08.
 *  Copyright 2008 IRCCyN. All rights reserved.
 *
 */
#ifndef __FILE_HEADER_GENERATION_H__
#define __FILE_HEADER_GENERATION_H__

#include <fstream>
#include <ostream>
#include <string>
#include <sstream>

class fileHeaderGeneration {
	std::ofstream file;
	std::string m_prefix;
	
	//text for private declarations
	std::ostringstream m_privateStr;
	//text for public declarations
	std::ostringstream m_publicStr;
	//text for declaration before the class declaration (includes, ..)
	std::ostringstream m_beforeStr;
	//text for declaration after the class declaration
	std::ostringstream m_afterStr;

	void generateFileHeaderClose();
	void generateFileHeaderPreamble();

	
public:
	fileHeaderGeneration(std::string name);
	~fileHeaderGeneration();

	std::ostream &publicStream()  {return m_publicStr;};
	std::ostream &privateStream() {return m_privateStr;};
	std::ostream &beforeStream()  {return m_beforeStr;};
	std::ostream &afterStream()   {return m_afterStr;};
};

#endif
