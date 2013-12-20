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
* $Date$
* $Rev$
* $Author$
* $URL$
* $Id$
*/
#include <cassert> //assert
#include "automata.h"
#include "strings/C_String.h"
//#include "bdd/C_BDD.h"
#include "utils.h"
#include <iostream>
using namespace std;

automata::automata(const unsigned int nbBitsToCodeAState, const unsigned int nbBitsToCodeATransition, const unsigned int nbOfExternalResources, const unsigned int nbOfNotifications) :
m_nbBitsToCodeAState(nbBitsToCodeAState), m_nbBitsToCodeATransition(nbBitsToCodeATransition), m_nbOfExternalResources(nbOfExternalResources), m_nbOfNotifications(nbOfNotifications)
{
	m_nbStates = 0; //will be calculated when needed (in 'getNbStates' func).
}

// My solution to read automata.
// Pour nbRE : récupérer m_externalResourcesStringVector.size(). Pour nbNotif : m_notificationsStringVector.size(). Pour nbInst : m_nbBitsToCodeATransition-nbRE-nbNotif.
void automata::loadAutomata(const char* line) {
	bool ok = true;
	unsigned long int inRE, notOut;
	int i = 0;
	//We read in-re-bit-pc-not-out|...
	while(ok) {
		inRE = stringToBinary(line, i, m_nbBitsToCodeAState+m_nbOfExternalResources);
		i += m_nbBitsToCodeAState+m_nbOfExternalResources;
		notOut = stringToBinary(line, i, m_nbBitsToCodeATransition-m_nbOfExternalResources+m_nbBitsToCodeAState);
		i += m_nbBitsToCodeATransition-m_nbOfExternalResources+m_nbBitsToCodeAState;
		m_ac2acToConsecutiveStatesMap[inRE] = notOut;
		//TODO: En décommentant la ligne suivante, le programme a un comportement exotique : nbBitsInst = 21
		//cerr << "[" << std::hex << inRE << "] " << notOut << line[i] << endl;
		ok = ok && line[i] != '.';
		i++;
	}
}

unsigned long int automata::stringToBinary(const char* word, int begin, int size) {
	unsigned long int res=0;
	for(int i=begin; i<begin+size; i++){
		res = res*2+word[i]-'0';
	}
	return res;
}

long int automata::getAC2CPPStateIdFromAC2AC(const int ac2acState) {
	map<unsigned long int, unsigned long int>::iterator it = m_ac2acToConsecutiveStatesMap.find(ac2acState);
	long int ret;
	if(it == m_ac2acToConsecutiveStatesMap.end()) {
		ret = -1;
	} else {
		//assert(it != m_ac2acToConsecutiveStatesMap.end());
		ret = (*it).second;
	}
	return ret;
}

unsigned int automata::getNbStates()
{
	if(m_nbStates) return m_nbStates;
	else {
		m_nbStates = (1 << m_nbBitsToCodeAState) - 1;
		return m_nbStates;
	}
}
