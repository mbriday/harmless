/** 
* a2cppV2
*
* a2cppV2 is copyright (c) IRCCyN 2005+
* a2cppV2 est protege par la loi sur la propriete intellectuelle
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

#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include "fileHeaderGeneration.h"
class automataConfiguration;

class codeGenerator
{
	///ofstreams of cpp output source files.
	std::ofstream m_cpp;
	///prefix of generated files (m_prefix+".cpp"  and m_prefix+".h")
	std::string m_prefix;
	///nb of tabulation to print;
	unsigned int m_nbTab;
	std::string tab();
	///store the automata configuration (pipelines, resources, ...)
	automataConfiguration *m_configuration;
	
	void generateFilePreamble();

	void notificationMasks(fileHeaderGeneration &outputH);
	void externalResourcesOffsets(fileHeaderGeneration &outputH);
	void initHeader(fileHeaderGeneration &outputH);

	void initCPPFile(std::string filename);
	void closeCPPFile();

	void function_execOneState(fileHeaderGeneration &outputH);
	void function_init(fileHeaderGeneration &outputH);
	void tabular_nextState(fileHeaderGeneration &outputH);
	
	
	public:	
	codeGenerator(automataConfiguration *configuration);
	void generateWithPrefix(std::string prefix, fileHeaderGeneration &fileHeader);

};

#endif
