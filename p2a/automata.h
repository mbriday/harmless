/** 
 * p2a
 *
 * p2a is copyright (c) IRCCyN 2005+
 * p2a est protege par la loi sur la propriete intellectuelle
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
#include "utils.h" //hash_length
#include "bdd/C_BDD.h"
#include <ostream> //ostream
#include <vector>
#include "systemState.h"

//class that encodes a transition condition (inst class id + external res state).
class transitionCondition
{
	const unsigned int m_nbBitsToCodeAnInstructionClass;
	const unsigned int m_nbExternalResources;
  PMUInt32 m_conditionValue ;
public:
	transitionCondition(const unsigned int nbBitsToCodeAnInstructionClass,
                      const unsigned int nbExternalResources);
	inline unsigned int const nbBitsRequired() {return m_nbBitsToCodeAnInstructionClass+m_nbExternalResources;};
	void addTransitionCondition(const unsigned int externalResources, instructionClass *inst);

	inline PMUInt32 getConditionValue() const {return m_conditionValue;};
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
	const unsigned int m_nbBitsToCodeAnInstructionClass;
	const unsigned int m_nbExternalResources;
	const unsigned int m_nbBitsToCodeAState;
	unsigned int m_nbBitsToCodeATransition;
	
	//nb bits to encode an notification in transition. 
	//Set to 0 at beginning, and get a value at the first call to addTransition
	unsigned int m_nbBitsRequiredNotification;	
	//nb bits to encode acondition in transition. 
	//Set to 0 at beginning, and get a value at the first call to addTransition
	unsigned int m_nbBitsRequiredCondition;	

	///init data structures before computation.	
	void computeInit();

	/** declares a bitfield. Each bit correspond to a state. If the state have been taken 
	 *  into account (i.e. it is either in the fifo or have been processed), the bit is set
	 *  to 1. Else the bit is 0. Warning: bit access! (use accessors)
	 */
	unsigned char *m_stateInProcess;
	bool isStateInProcess(const hash_length stateCode);
	void setStateInProcess(const hash_length stateCode);
	void initStateInProcessTab(const unsigned int nbMaxSystemStates);
	
	/** store the states that have to be processed due to
	 *  a breadth-first exploration graph (new states encountered are added to the fifo).
	 */
	std::vector<systemState *> m_statesToProcessFifo; //This is a Stack!
	void findStatesFromState(systemState *currentState);
	void findNextSystemState(systemState *currentStateWithRes, unsigned int resCase, instructionClass *inst);
	
    // ************************************************************************
	// BDD related parts.
    // ************************************************************************
	//in the BDD, a transition is coded as follow (high bits to low bits):
	// first  the target state id (require m_nbBitsToCodeAState bits(variables))
	// second the transition   id ,based on bits: 
	//    -> transition condition (inst class+external resources)
	//        -> external resource
	//        -> instruction class
	//    -> transition notification, 
	// last   the source state id
  C_BDD m_transitions ;
  PMUInt32 m_transitionArrayCapacity ;
  PMUInt64 * m_transitionArray ;
	//count transition, for periodic cleaning of useless bdds.
	unsigned int m_nbTransition;
	//add a transition in the automata.
	void addTransition(const hash_length fromStateId, 
					   const hash_length toStateId,
					   transitionCondition &condition,
					   transitionNotification &notification);
	
	
	public:
	//create an automata with the first state.
    automata(pipeline *pipe);

	//compute the initial automata (not minimized)
	void computeAutomata();

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

#endif
