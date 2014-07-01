/** 
* a2cpp
*
* a2cpp is copyright (c) IRCCyN 2005+
* a2cpp est protege par la loi sur la propriete intellectuelle
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
#include "bdd/C_BDD.h"
#include "utils.h"
#include <iostream>
using namespace std;

automata::automata(const unsigned int nbBitsToCodeAState, const unsigned int nbBitsToCodeATransition) :
m_nbBitsToCodeAState(nbBitsToCodeAState), m_nbBitsToCodeATransition(nbBitsToCodeATransition)
{
	m_nbStates = 0; //will be calculated when needed (in 'getNbStates' func).
	
}

void automata::loadAutomataBDD(const char* BDDString)
{
	C_String str = C_String(BDDString);
	m_transitions = C_BDD::BDDWithPredicateString(BDDString COMMA_HERE);

	const unsigned int nbStates = getNbStates();
	m_consecutiveToa2aStatesTab = new int[nbStates];

	C_BDD sources = m_transitions.existsOnBitsAfterNumber(m_nbBitsToCodeAState);
	TC_UniqueArray <uint64_t> sourceArray;
	sources.buildValue64Array(sourceArray, m_nbBitsToCodeAState);
	const int32_t nbSources = sourceArray.count();
	for (int32_t i=0 ; i<nbSources ; i++) {
		uint64_t a2aId = sourceArray(i COMMA_HERE);
		m_consecutiveToa2aStatesTab[i] = a2aId;
		m_a2aToConsecutiveStatesMap[a2aId] = i;
	}	
}

int automata::getA2CPPStateIdFromA2A(const int a2aState)
{
	map<int, int>::iterator it = m_a2aToConsecutiveStatesMap.find(a2aState);
	assert(it != m_a2aToConsecutiveStatesMap.end());
	return (*it).second;
}

int automata::getA2AStateFromA2CPP(const int a2cppState)
{
	assert(a2cppState < (int)getNbStates());
	return m_consecutiveToa2aStatesTab[a2cppState];
}

unsigned int automata::getNbStates()
{
	if(m_nbStates) return m_nbStates;
	else {
		C_BDD sources = m_transitions.existsOnBitsAfterNumber(m_nbBitsToCodeAState);
		TC_UniqueArray <uint64_t> sourceArray;
		sources.buildValue64Array(sourceArray, m_nbBitsToCodeAState);
		m_nbStates = (unsigned int)sourceArray.count();
		return m_nbStates;
	}
}
