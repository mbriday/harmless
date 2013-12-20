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
#include <cassert> //assert

extern bool verbose;
//#define DEBUG_LOAD_CONFIG 

using namespace std;

instructionDescription::instructionDescription() {
	m_mnemo = "";
	m_chunks = 0;
	m_idClass = 0;
	m_isBranch = 0;
	m_isUnCond = 0;
	m_isCall = 0;
	m_isIndirect = 0;
	m_target = 0;
}

void instructionDescription::showId() {
	cout << "Instruction description is: " << endl;
	cout << "\tMnemo     : " << m_mnemo << endl;
	cout << "\tChunks    : " << m_chunks << endl;
	cout << "\tIdClass   : " << m_idClass << endl;
	cout << "\tIsBranch  : " << m_isBranch << endl;
	cout << "\tIsUnCond    : " << m_isUnCond << endl;
	cout << "\tIsCall    : " << m_isCall << endl;
	cout << "\tIsIndirect: " << m_isIndirect << endl;
	cout << "\tTarget    : " << m_target << endl;
}
