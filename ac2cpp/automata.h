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
#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__

#include <string>
#include <map>
//#include "bdd/C_BDD.h"

class automata
{
	const unsigned int m_nbBitsToCodeAState;
	const unsigned int m_nbBitsToCodeATransition;
	//Information needed to load automata
	const unsigned int m_nbOfNotifications;
	const unsigned int m_nbOfExternalResources;
	//store the nb of states. 0 at beginning. the value is calculated the first time its needed.
	unsigned int m_nbStates; 
	//C_BDD m_transitions ;

	//states stores in the '.ac2ac' file format are not consecutive.
	//the map is used to get the 'ac2cpp' state id from the '.ac2ac' state id.
	//TODO: Maybe transform it in a vector.
	std::map<unsigned long int,unsigned long int> m_ac2acToConsecutiveStatesMap;
	public:
	automata(const unsigned int nbBitsToCodeAState, const unsigned int nbBitsToCodeATransition, unsigned int nbOfExternalResources, unsigned int nbOfNotifications);
	///automata loading part.
	///called exclusively by automataConfiguration during loading.
	void loadAutomata(const char* String);
	unsigned long int stringToBinary(const char* word, int begin, int size);
	void test();

	unsigned int const getNbBitsToCodeATransition() {return m_nbBitsToCodeATransition;};
	unsigned int const getNbBitsToCodeAState() {return m_nbBitsToCodeAState;};
	//return the nb of source states. There is no states that is not a source, so it's the total nb of states.
	//this is calculated only once.
	unsigned int getNbStates();
	//C_BDD bdd() {return m_transitions; };

	//return the BDD of the automata with the source state restriction.
	//C_BDD automataWithSourceState(unsigned int sourceId);

	long int getAC2CPPStateIdFromAC2AC(const int ac2acState);
	
};
#endif
