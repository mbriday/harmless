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
#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__

class pipeline;
class programDescription;
class instructionDescription;
#include "utils.h" //hash_length
#include "bdd/C_BDD.h"
#include <ostream> //ostream
#include <vector>
#include "systemState.h"

//class that encodes a transition condition (external res state).
class transitionCondition{
	private:
		const unsigned int m_nbExternalResources;
		PMUInt32 m_conditionValue ;
	public:
		transitionCondition(const unsigned int nbExternalResources);
		inline unsigned int const nbBitsRequired() {return m_nbExternalResources;};
		void addTransitionCondition(const unsigned int externalResources);

		inline PMUInt32 getConditionValue() const {return m_conditionValue;};
};

//Class that encodes a label transition (an instruction).
class transitionLabel {
	private:
		const unsigned int m_nbBitsToCodeAnInstruction;
		PMUInt32 m_labelValue;
	public:
		transitionLabel(const unsigned int nbBitsToCodeAnInstruction);
		inline unsigned int const nbBitsRequired() {return m_nbBitsToCodeAnInstruction;};
		void addTransitionLabel(const unsigned int inst);
		inline PMUInt32 getLabelValue() const {return m_labelValue;};
};

//class that encodes a transition notification (only fetch at this date).
//note that transition notification code IS NOT the same as pipeline notifications.
//pipeline notifications encodes an notification defined in the config file (with instId, stageId, enter)
//whereas a transition notification give the information that notifications 'x' located at bit 'x'
//should be performed.
class transitionNotification
{
	PMUInt32 m_val ;
public:
	//the C_BDD in parameter encodes all the notifications (pipeline ones) 
	//that are performed to go to the next state.
	void computeNotificationFromSystem(pipeline *m_pipeline, C_BDD &systemNotification);
	//void setFetch(unsigned int val);
	inline unsigned int const nbBitsRequired(pipeline *pipe);
	//should ONLY be called by automata class.
	inline PMUInt32 value () const {return m_val;}
};

//TODO: split this big class into 
// automata generator
// and automata internal data structure.
class automata
{
	pipeline *m_pipeline;
	const unsigned int m_nbBitsToCodeAnInstruction;
	const unsigned int m_nbExternalResources;
	const unsigned int m_nbBitsToCodeAState;
	unsigned int m_nbBitsToCodeATransition;
	//Débogage pour la pile
	unsigned int m_PCStackSizeMax;
	
	//nb bits to encode an notification in transition. 
	//Set to 0 at beginning, and get a value at the first call to addTransition
	unsigned int m_nbBitsRequiredNotification;	
	//nb bits to encode acondition in transition. 
	//Set to 0 at beginning, and get a value at the first call to addTransition
	unsigned int m_nbBitsRequiredCondition;	
	unsigned int m_nbBitsRequiredLabel;	

	///init data structures before computation.	
	void computeInit(unsigned int);

	/** store the states that have to be processed due to
	 *  a breadth-first exploration graph (new states encountered are added to the fifo).
	 */
	std::vector<systemState *> m_statesToProcessFifo; //This is a Stack!
	void findStatesFromState(systemState *currentState, programDescription *program);
	void findNextSystemState(systemState *currentStateWithRes, unsigned int resCase, instructionDescription *instd, unsigned int previousPC);
	
	// ************************************************************************
	// BDD related parts.
	// ************************************************************************
	//in the BDD, a transition is coded as follow (high bits to low bits):
	// first  the target state id (require m_nbBitsToCodeAState bits(variables))
	// second the transition   id ,based on bits: 
	//    -> transition condition (inst+external resources)
	//        -> external resource
	//        -> instruction
	//    -> transition notification, 
	// last   the source state id
	C_BDD m_transitions ;
	PMUInt32 m_transitionArrayCapacity ;
	__uint128_t * m_transitionArray ;
	//count transition, for periodic cleaning of useless bdds.
	unsigned int m_nbTransition;
	//add a transition in the automata.
	void addTransition(const unsigned int fromStateId, const unsigned int toStateId, transitionCondition &condition, transitionLabel &label, transitionNotification &notification);
	
	//We classify states in a vector
	std::vector<systemState *> m_stateVector;
	unsigned int m_nbStates;
	int findOrAddState(systemState *s);

	/*typedef struct trans {
		unsigned fromStateId : m_nbBitsToCodeAState;
		unsigned label : m_nbBitsRequiredLabel;
		unsigned condition : m_nbBitsRequiredCondition;
		unsigned notification : m_nbBitsRequiredNotification;
		unsigned toStateId : m_nbBitsToCodeAState; 
	};*/

	public:
	//create an automata with the first state.
	automata(pipeline *pipe);

	//compute the initial automata (not minimized)
	void computeAutomata(programDescription *program);

	void translateTransitionArrayIntoBDD (const bool inVerboseMode) ;

	inline unsigned int transitionCount () const { return m_nbTransition ; }


	void exportGraphViz(std::string filename);
	void exportGraphViz(std::ostream &output);
	void save(std::string filename, std::string modelName);
	void save(std::ostream &output, std::string modelName);

	//print internal stats on BDDs 
	void printInternalStats();
	void printInternalConstants();
	
	void minimize(const bool inVerboseMode);	
};

static std::string toBin(__uint128_t u, unsigned int size);
static std::string toHexa(unsigned int u, unsigned int size);

#endif
