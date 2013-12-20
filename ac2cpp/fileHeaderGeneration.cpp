/*
 *  fileHeaderGeneration.cpp
 *  ac2cpp
 *
 *  Created by Mikaël Briday on 02/12/08.
 *  Copyright 2008 IRCCyN. All rights reserved.
 *
 */

#include "fileHeaderGeneration.h"
#include <iostream>
using namespace std;

extern bool verbose;

fileHeaderGeneration::fileHeaderGeneration(string prefix)
: m_prefix(prefix)
{
	if(verbose) cout << "generate header file \"" << m_prefix << ".h\""  << endl;
}


fileHeaderGeneration::~fileHeaderGeneration()
{
	string name = m_prefix+".h";
	file.open(name.c_str(), ofstream::out);
	generateFileHeaderPreamble();
	file << m_beforeStr.str() << endl;
	file << "class " << m_prefix << "{" << endl;
	file << "public:" << endl;
	file << m_publicStr.str();
	file << "private:" << endl;
	file << m_privateStr.str();
	file << "};" << endl;	
	file << m_afterStr.str();
	generateFileHeaderClose();
	file.close();
}

void fileHeaderGeneration::generateFileHeaderClose()
{
	file << "#endif" << endl;
}

void fileHeaderGeneration::generateFileHeaderPreamble()
{
	file << "/** automata simulation" << endl;
	file << "automatically generated using ac2cpp." << endl;
	file << "DO NOT MODIFY DIRECTLY, IT CAN BE OVERWRITTEN." << endl;
	file << " */" << endl << endl; 
	
	const string def = "__" + m_prefix + "_H__";
	file << "#ifndef " << def << endl << "#define " << def << endl << endl;
	file << "//#define PIPELINE_DEBUG" << endl;
	file << endl;
	
	file << "class " << m_prefix << ";" << endl;	
}


