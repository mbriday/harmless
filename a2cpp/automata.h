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
#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__

#include <string>
#include <map>
#include "bdd/C_BDD.h"

class automata
{
	const unsigned int m_nbBitsToCodeAState;
	const unsigned int m_nbBitsToCodeATransition;
	//store the nb of states. 0 at beginning. the value is calculated the first time its needed.
	unsigned int m_nbStates; 
	C_BDD m_transitions ;

	//states stores in the '.a2a' file format are not consecutive.
	//the map is used to get the 'a2cpp' state id from the '.a2a' state id.
	std::map<int,int> m_a2aToConsecutiveStatesMap;
	//the tabular is used to get the '.a2a' state id from the consecutive 'a2cpp' state id.
	int *m_consecutiveToa2aStatesTab;
	public:
	automata(const unsigned int nbBitsToCodeAState, const unsigned int nbBitsToCodeATransition);
	///automata loading part.
	///called exclusively by automataConfiguration during loading.
	void loadAutomataBDD(const char* BDDString);
	void test();

	unsigned int const getNbBitsToCodeATransition() {return m_nbBitsToCodeATransition;};
	unsigned int const getNbBitsToCodeAState() {return m_nbBitsToCodeAState;};
	//return the nb of source states. There is no states that is not a source, so it's the total nb of states.
	//this is calculated only once.
	unsigned int getNbStates();
	C_BDD bdd() {return m_transitions; };

	//return the BDD of the automata with the source state restriction.
	C_BDD automataWithSourceState(unsigned int sourceId);

	int getA2CPPStateIdFromA2A(const int a2aState);
	int getA2AStateFromA2CPP(const int a2cppState);
	
};
#endif

