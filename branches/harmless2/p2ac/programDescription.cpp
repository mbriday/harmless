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

#include <iostream>
#include <vector>
#include "resource.h"
#include "instructionDescription.h"
#include "programDescription.h"
#include <cassert> //assert

extern bool verbose;

using namespace std;

programDescription::programDescription() {
	m_start = 0;
	std::map<unsigned int, instructionDescription *> m_idMap();
}

bool programDescription::load(const string filename) {
	bool loadOk = true;
	unsigned int start, chunks,idClass, pc, branch, unCond, call, indirect, target;
	char a;
	std::string command;
	if(verbose) {
		cerr << "load description from file: " << filename << endl;
	}
	ifstream file;
	file.open(filename.c_str(), ifstream::in);
	if(!file) {
 		cerr << "open file error:" << filename << " in read mode" << endl;
		return false;
	}
	file >> command;
	//first, where is the start?
	if(command != "start") {
		cerr << "start problem" << endl;
	}
	a = file.get();
	file >> m_start;
	/*command = "";
	do {
		a = file.get();
		if(a!='\r' && a!='\n') {
			command += a;
		}
	} while(a!='\r' && a!='\n');
	m_start = hexaToBin(command); //In fact, all is in decimal.*/
	a = file.get();
	//Format of file : @pc@mnemo@chunks@idclass@branch?@(uncond?@call?(@target)@)
	while(file.get(a)) {
		file >> pc;
		/*command = "";
		do {
			a = file.get();
			if(a!='@') {
				command += a;
			}
		} while(a!='@' && !file.eof());
		pc = hexaToBin(command);*/
		instructionDescription *instd  = new instructionDescription();
		m_idMap.insert(std::pair<unsigned int, instructionDescription *>(pc, instd));
		file.get(a);
		command = "";
		do {
			file.get(a);
			if(a!='@') {
				command += a;
			}
		} while(a!='@' && !file.eof());
		m_idMap[pc]->setMnemo(command);
		file >> chunks;
		m_idMap[pc]->setChunks(chunks);
		file.get(a);
		file >> idClass;
		m_idMap[pc]->setIdClass(idClass);
		file.get(a);
		file >> branch;
		/*command = "";
		do {
			a = file.get();
			if(a!='@') {
				command += a;
			}
		} while(a!='@' && !file.eof());
		branch = hexaToBin(command);*/
		m_idMap[pc]->setIsBranch(branch);
		if (branch) {
			file.get(a);
			file >> unCond;
			m_idMap[pc]->setIsUnCond(unCond);
			file.get(a);
			//*
			//file >> call;
			//m_idMap[pc]->setIsCall(call);
			//file.get(a);//*/
			file >> indirect;
			m_idMap[pc]->setIsIndirect(indirect);
			if (!indirect) {
				file.get(a);
				file >> target;
				m_idMap[pc]->setTarget(target);
			}
		}
		file.get(a);
		file.get(a);
	}
	file.close();
	return loadOk;
}

void programDescription::showIdMap() {
	std::map<unsigned int, instructionDescription *>::iterator i = m_idMap.begin();
	((*i).second)->showId();
	++i;
	((*i).second)->showId();
}

//Useless
static unsigned int hexaToBin(std::string hexa) {
	int i;
	unsigned int bin = 0;
	for(i=0;i<hexa.size();i++) {
		if(hexa[i] >= '0' && hexa[i] <= '9') {
			bin = bin*16 + (hexa[i] - '0');
		} else if(hexa[i] >= 'a' && hexa[i] <= 'f') {
			bin = bin*16 + (hexa[i] - 'a' + 10);
		} else if(hexa[i] >= 'A' && hexa[i] <= 'F') {
			bin = bin*16 + (hexa[i] - 'A' + 10);
		} else {
			cerr << "Error : conversion hexadecimal to binary: " << hexa << endl;
		}
	}
	return bin;
}
