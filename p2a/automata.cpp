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

#include <cassert> //assert
#include "automata.h"
#include "systemState.h"
#include "pipeline.h"
#include "instructionClass.h" //hashOfTransition
#include "pipelineNotification.h"
#include <iostream> //debug
#include <ostream> //ostream
#include <fstream> 
#include "strings/C_String.h"
#include "time/C_Timer.h"


extern bool verbose;

const char *A2A_OUTPUT_VERSION="3";

using namespace std;

transitionCondition::transitionCondition(const unsigned int nbBitsToCodeAnInstructionClass,
                                         const unsigned int nbExternalResources) :
m_nbBitsToCodeAnInstructionClass(nbBitsToCodeAnInstructionClass),
m_nbExternalResources(nbExternalResources)
{
	
}

void transitionCondition::addTransitionCondition(const unsigned int externalResources, instructionClass *inst)
{
	//inst class.
	unsigned int instId;
	if(inst) instId = inst->getIndex();
	else instId = 0;
	assert(instId < (1UL<<m_nbBitsToCodeAnInstructionClass));
  m_conditionValue = instId ;	
	//external resources.
	assert(externalResources < (1UL<<m_nbExternalResources));
  m_conditionValue |= externalResources << m_nbBitsToCodeAnInstructionClass ;
}

void transitionNotification::computeNotificationFromSystem(pipeline *pipe, C_BDD &systemNotification)
{
	unsigned int code = 0;
	const unsigned int nbAct = pipe->getNbPipelineNotificationData();
	for(unsigned int i=0; i < nbAct; i++)
	{
		C_BDD notificationUnderTest = pipe->getPipelineNotificationData(i)->code();
		C_BDD temp = systemNotification & notificationUnderTest;
		if(!(temp.isFalse())) //not false -> there is an intersection, current notification should be performed.
		{
			code |= (1<<i);
		}
	}
	assert(nbAct > 0); //at least one notification should be defined in config file.
  m_val = code ;
}

unsigned int const transitionNotification::nbBitsRequired(pipeline *pipe) 
{
	return pipe->getNbPipelineNotificationData();
}

//void transitionNotification::setFetch(unsigned int val)
//{
//	assert(val <= 1);
//	m_notification |= C_BDD::varCompareConst (0, 1, C_BDD::kEqual, val) ;		
//}

automata::automata(pipeline *pipe) : 
	m_pipeline(pipe),
	m_nbBitsToCodeAnInstructionClass(nbBitsToCodeValue(pipe->getNbInstructionClasses()+1)),
	m_nbExternalResources(pipe->getNbExternalResources()),
	m_nbBitsToCodeAState(systemState::getNbBitsForStateCode(pipe)),
	m_nbBitsRequiredNotification(0),
	m_nbBitsRequiredCondition(0)
{
	//get nb bits to code a transition.
	transitionNotification ta;
	transitionCondition tc(m_nbBitsToCodeAnInstructionClass, m_nbExternalResources);
	m_nbBitsToCodeATransition = ta.nbBitsRequired(m_pipeline) + tc.nbBitsRequired();

	m_nbTransition = 0;
  m_transitionArrayCapacity = 0 ;
  m_transitionArray = NULL ;
}

#pragma mark methods to access find states in process.

bool automata::isStateInProcess(const hash_length stateCode)
{
	const unsigned int index = stateCode >> 3;
	const unsigned int offset = stateCode & 0x7;
	const unsigned int mask = 1 << offset;
	return (m_stateInProcess[index] & mask);
}

void automata::setStateInProcess(const hash_length stateCode)
{
	const unsigned int index = stateCode >> 3;
	const unsigned int offset = stateCode & 0x7;
	const unsigned int mask = 1 << offset;
	m_stateInProcess[index] |= mask;
}

void automata::initStateInProcessTab(const unsigned int nbMaxSystemStates)
{
	const unsigned int maxTabSize = (nbMaxSystemStates >> 3) + 1;
	m_stateInProcess = NULL ;
  macroMyNewArray (m_stateInProcess, unsigned char, maxTabSize); //bit access.
	for(unsigned int i=0; i < maxTabSize; i++) m_stateInProcess[i] = 0;
}
#pragma mark debug

//void automata::debugFifoSize()
//{
//	const unsigned int step = 5000;
//	static unsigned int max = 0;
//	static unsigned int nextMaxPrint = step;
//	//debug max fifo length.
//	if(m_fifoSize > max)
//	{
//		max = m_fifoSize;
//		if(max > nextMaxPrint)
//		{
//			nextMaxPrint += step;
//			cerr << "*" << flush;
//		}
//		cout << "max " << dec << max << endl; 
//	}
//}
//
//void automata::debug()
//{
//	map<hash_length, automataState *>::iterator it = m_automataStateMap.begin();
//	while(it != m_automataStateMap.end()) 
//	{
//		cout << "state : " << (*it).first << endl;
//		it++;
//	}
//	
//}

#pragma mark compute Automata

void automata::computeInit()
{
	//Init tree with the root.
	systemState *rootSystemState = NULL ;
  macroMyNew (rootSystemState, systemState(m_pipeline));
	rootSystemState->checkHashCodeLength();

	const unsigned int nbMaxSystemStates = 1 << (rootSystemState->getNbBitsForStateCode());
	initStateInProcessTab(nbMaxSystemStates);

	//init with the root.
	m_statesToProcessFifo.push_back(rootSystemState);
	setStateInProcess(rootSystemState->getStateHashCode());
}

void automata::computeAutomata()
{
	computeInit();
	while(m_statesToProcessFifo.size() != 0)
	{
		//if(verbose) debugFifoSize();

		//must found an entry (m_statesToProcessFifo != 0)
		systemState * currentState = m_statesToProcessFifo.back(); //no more a fifo :-)
		m_statesToProcessFifo.pop_back();
		
		//process the state.
		//TODO: update name.
		findStatesFromState(currentState);
	} //fifo empty
}

void automata::findStatesFromState(systemState *currentState)
{
	const unsigned int nbRes =  m_pipeline->getNbExternalResources();
	const unsigned int nbCases = 1 << nbRes;
	//get the next system state. Must take into account all the external resource combinations.
	for(int resCase = nbCases-1; resCase >= 0 ; resCase--)
	{
		systemState *currentStateWithRes = NULL;
		//no copy constructor for index 0.
		if(resCase == 0) currentStateWithRes = currentState;
		else macroMyNew (currentStateWithRes, systemState(*currentState));
		
		currentStateWithRes->setExternalRessources(resCase);
		
		/* push all the instruction codes into the pipeline. */
		const unsigned int nbInstClass = m_pipeline->getNbInstructionClassesIncludeStall();
		for(unsigned int classId = 0; classId < nbInstClass; classId++)
		{
			findNextSystemState(currentStateWithRes, resCase, m_pipeline->getInstructionClass(classId));
		} //instructions.
		macroMyDelete (currentStateWithRes);
	}//external resources
}

void automata::findNextSystemState(systemState *currentStateWithRes, unsigned int resCase, instructionClass *inst)
{
	//notifications that are performed when going to the next state (alls the notifications)
	C_BDD systemNotification;
	/* compute the next system state from the current one when
	an instruction of class inst is pushed in the pipeline	*/
	systemState *next = currentStateWithRes->getNext(inst, systemNotification);
	SEGFAULTIF(currentStateWithRes==next);

	/* store the new automata state (if it does not exist)	*/
	hash_length hashOfNextState = next->getStateHashCode();
	hash_length hashOfCurrentState = currentStateWithRes->getStateHashCode();
	
	/* create (or update) the transition between the 2 automata states */
	/* the transition code is composed of the instruction class id (the one that is fetched)
	 * and the external resources state
	 */
	//transitionCondition.
	transitionCondition tc(m_nbBitsToCodeAnInstructionClass, m_nbExternalResources);	
	tc.addTransitionCondition(resCase, inst);
	//transtion notification.
	transitionNotification ta;
	ta.computeNotificationFromSystem(m_pipeline, systemNotification);
	//ta.setFetch(inst_move & 0x1); //an instruction may move in the first stage.
	addTransition(hashOfCurrentState, hashOfNextState, tc, ta);

	/* add the automata state to the fifo list of states to process. */
	if(!isStateInProcess(hashOfNextState))
	{
		//the automata/system state does not wait to be processed.
		m_statesToProcessFifo.push_back(next);
		setStateInProcess(hashOfNextState);
	} else {
		//the system state is already in the process list.
		macroMyDelete (next);
	}
}

//BDD:
// from lowest var to highest:
// -> fromStateId: m_nbBitsToCodeAState
// -> transition : m_nbBitsToCodeATransition
//		-> notification    : notification.nbBitsRequired()
//		-> condition : condition.nbBitsRequired()
// -> toStateId : m_nbBitsToCodeAState
void automata::addTransition(const hash_length fromStateId, 
							 const hash_length toStateId,
							 transitionCondition &condition,
							 transitionNotification &notification)
{
	if(!m_nbBitsRequiredNotification) m_nbBitsRequiredNotification = notification.nbBitsRequired(m_pipeline);
	if(!m_nbBitsRequiredCondition) m_nbBitsRequiredCondition = condition.nbBitsRequired();
	//bits 0 to (m_nbBitsToCodeAState-1)
	assert(fromStateId < (1UL<<m_nbBitsToCodeAState));
	//bits m_nbBitsToCodeAState to (m_nbBitsToCodeAState+m_nbBitsToCodeATransition-1)
	//cout << "act : " << notification.nbBitsRequired() << endl;
	//cout << "cond: " << condition.nbBitsRequired() << endl;
	//cout << "full: " << m_nbBitsToCodeATransition << endl;
	assert(notification.nbBitsRequired(m_pipeline)+condition.nbBitsRequired() <= m_nbBitsToCodeATransition);
	//bits (m_nbBitsToCodeAState+m_nbBitsToCodeATransition) to (2*m_nbBitsToCodeAState+m_nbBitsToCodeATransition-1)
	assert(toStateId < (1UL<<m_nbBitsToCodeAState));
	//printf("target: "); printBDD(target); printf("\n");
	//printf("\tcond: ");   printBDD(cond);   printf("\n");
	//printf("\tsource: "); printBDD(source); printf("\n");
	//printf("\tfull transition: "); printBDD(transition); printf("\n");
//---
  if (m_nbTransition >= m_transitionArrayCapacity) {
    m_transitionArrayCapacity += 10000000 ;
    macroMyReallocPODArray (m_transitionArray, PMUInt64, m_transitionArrayCapacity) ;
  }
//---
  PMUInt32 notificationID = condition.getConditionValue () ;
  notificationID <<= m_nbBitsRequiredNotification ;
  notificationID |= notification.value () ;
  PMUInt64 t = toStateId ;
  t <<= m_nbBitsToCodeATransition ;
  t |= notificationID ;
  t <<= m_nbBitsToCodeAState ;
  t |= fromStateId ;
  m_transitionArray [m_nbTransition] = t ;
	m_nbTransition ++;
}

void automata::translateTransitionArrayIntoBDD (const bool inVerboseMode)
{
  if (inVerboseMode) {
    printf ("Translating transition array into BDD...") ; fflush (stdout) ;
  }
  C_Timer timer ;
  const PMUInt32 totalBits = m_nbBitsToCodeAState + m_nbBitsToCodeATransition + m_nbBitsToCodeAState ;
  m_transitions = C_BDD::buildBDDFromValueList (m_transitionArray, m_nbTransition, totalBits) ;
  if (inVerboseMode) {
    co << " done (" << timer << ")\n" ;
  }
//--- Delete transition array
  macroMyDeletePODArray (m_transitionArray) ;
  m_transitionArrayCapacity = 0 ;
  macroMyDeleteArray (m_stateInProcess) ;
}

void automata::printInternalConstants()
{
	cout << "system stats" << endl;
	cout << "\tnb bits to code an inst class   : " << m_nbBitsToCodeAnInstructionClass << endl;
	cout << "\tnb bits to code an external res : " << m_nbExternalResources << endl;
	cout << "automata stats" << endl;
	cout << "\tnb bits to code a state         : " << m_nbBitsToCodeAState << endl;
	cout << "\tnb bits to code an notification       : " << m_nbBitsToCodeATransition << endl;
}

void automata::printInternalStats()
{
	cout << "automata generation stats" << endl;
	PMUInt64 nbTransitions = m_transitions.valueCount64(m_nbBitsToCodeATransition+m_nbBitsToCodeAState*2);
	const unsigned int nbNodes = m_transitions.getBDDnodesCount();
  cout << "\tnumber of transitions  : " << nbTransitions << endl;
    // All (reachable) states. Expressed here as "all states source of a transition"
  C_BDD states = m_transitions.existsOnBitsAfterNumber(m_nbBitsToCodeAState);
	PMUInt64 nbStates = states.valueCount64(m_nbBitsToCodeAState);
  cout << "\tnumber of states: " << dec << nbStates << endl;
	cout << "\tBDD encoding : " << dec << nbNodes << " nodes (" << nbNodes * C_BDD::getBDDnodeSize () << " bytes)" << endl;
}

#pragma mark export

//edges are xx:yy(zz), ...
//which is:
// xx: external resource
// yy: instruction class
// zz: notification.
void automata::exportGraphViz(ostream &output)
{
	const unsigned int maskClassId = (1<<m_nbBitsToCodeAnInstructionClass)-1;
	//printBDD(m_transitions);
	//C_BDD targets = m_transitions.bddByRightShifting(m_nbBitsToCodeAState+m_nbBitsToCodeATransition);
	C_BDD sources = m_transitions.existsOnBitsAfterNumber(m_nbBitsToCodeAState);
    output << "# made with p2a. IRCCyN" << endl;
    output << "digraph g {" << endl;
	//states
	//all states are source states => give all source states.
	TC_UniqueArray <PMUInt64> sourceArray;
	sources.buildValue64Array (sourceArray, m_nbBitsToCodeAState);
	int circleType = 0; //0 <>not init, 1 double circle, 2 circle
	for (PMSInt32 i=0 ; i<sourceArray.count () ; i++) {
		PMUInt64 stateId = sourceArray(i COMMA_HERE);
		if(circleType != 2 && stateId != 0) 
		{
			output << "node [shape=circle];" << endl; 
			circleType = 2;
		}
		if(circleType != 1 && stateId == 0) {
			output << "node [shape=doublecircle];" << endl;
			circleType = 1;
		}
		output << "\"" << hex << stateId << "\";" << endl;
	}
	//transitions.
	for (PMSInt32 i=0 ; i<sourceArray.count () ; i++) {
		PMUInt64 sourceId = sourceArray(i COMMA_HERE);
		C_BDD currentSource = C_BDD::varCompareConst (0, m_nbBitsToCodeAState, C_BDD::kEqual, sourceId) ;
		C_BDD automataFromCurrentSources = m_transitions & currentSource;

		C_BDD currentTargets = automataFromCurrentSources.bddByRightShifting(m_nbBitsToCodeAState+m_nbBitsToCodeATransition);
		TC_UniqueArray <PMUInt64> currentTargetsArray;
		currentTargets.buildValue64Array(currentTargetsArray, m_nbBitsToCodeAState);
		
		for (PMSInt32 j=0 ; j<currentTargetsArray.count () ; j++) {
			PMUInt64 targetId = currentTargetsArray(j COMMA_HERE);
			output << "\"" << hex << sourceId << "\" -> \"" << hex << targetId << "\"";
			C_BDD currentTarget = C_BDD::varCompareConst (m_nbBitsToCodeAState+m_nbBitsToCodeATransition, m_nbBitsToCodeAState, C_BDD::kEqual, targetId) ;

			C_BDD currentTransition = automataFromCurrentSources & currentTarget;
			currentTransition = currentTransition.bddByRightShifting(m_nbBitsToCodeAState);
			currentTransition = currentTransition.existsOnBitsAfterNumber(m_nbBitsToCodeATransition);

				
			//transition id
			//condition(notification), condition2(notification2), ....
			output << "[ label = \"";
			TC_UniqueArray <PMUInt64> conditionTransitionArray;
			C_BDD conditions = currentTransition.bddByRightShifting(m_nbBitsRequiredNotification);
			conditions.buildValue64Array(conditionTransitionArray, m_nbBitsRequiredCondition);
			PMSInt32 nbCondition = conditionTransitionArray.count();
			for (PMSInt32 k=0 ; k<nbCondition ; k++) {
				PMUInt32 conditionId = (PMUInt32) conditionTransitionArray(k COMMA_HERE);
				//condition id is built with classId (low bits) and 
				// external resources access.
				const PMUInt32 classId = conditionId & maskClassId;
				const PMUInt32 allExtRes = conditionId >> m_nbBitsToCodeAnInstructionClass;
				for(int extResId = m_nbExternalResources-1; extResId>=0; extResId--)
					output << ((allExtRes >> extResId) & 0x1);
				output << ":" << m_pipeline->getInstructionClassNameforIndex(classId) << "(";
				C_BDD currentTransitionCondition = C_BDD::varCompareConst (m_nbBitsRequiredNotification, m_nbBitsRequiredCondition, C_BDD::kEqual, conditionId) ;
				C_BDD currentTransitionNotification = currentTransition & currentTransitionCondition ;
				currentTransitionNotification = currentTransitionNotification.existsOnBitsAfterNumber(m_nbBitsRequiredNotification);
				TC_UniqueArray <C_String> act;
				currentTransitionNotification.buildCompressedBigEndianStringValueArray (act COMMA_HERE) ;
				
				for (PMSInt32 l=0 ; l<act.count () ; l++) {
					if(l) output << " | ";	
					output << act(l COMMA_HERE).cString (HERE);
				}
				
				output << ")";
				if(k+1 < nbCondition) output << ", "; //got one after.
			}
			output << "\" ] ;" << endl;
		}
	}
	


	PMUInt64 nbStates = sources.valueCount64(m_nbBitsToCodeAState);
	PMUInt64 nbTransitions = m_transitions.valueCount64(m_nbBitsToCodeATransition+m_nbBitsToCodeAState*2);
	const unsigned int nbNodes = m_transitions.getBDDnodesCount();
	output << "}" << endl;
    output << "# number of states : " << dec << nbStates << endl;
    output << "# number of transitions  : " << dec << nbTransitions << endl;
    output << "# BDD encoding : " << nbNodes << " nodes (" << nbNodes * C_BDD::getBDDnodeSize () << " bytes)" << endl;	
}


void automata::save(ostream &output, string modelName)
{
	//version
	output << "version " << A2A_OUTPUT_VERSION << endl; 
	output << "model " << modelName << endl;
//	//superscalaire depth..always 1 in p2a
	output << "depth 1" << endl; 
//	//pipeline configuration.
	m_pipeline->save(output); //pipe, external res, instruction classes, notifications
	//automata
	output << m_nbBitsToCodeAState << " bits for a state" << endl;
	output << m_nbBitsToCodeATransition << " bits for a condition" << endl;
	const C_String predicate = m_transitions.queryStringValue (HERE);
	output << predicate.cString (HERE) << endl;
}

void automata::exportGraphViz(std::string filename)
{
	string extensionString = ".dot";
	if(!filename.empty())
	{
		//add the .dot extension if not present.
		if(filename.size()>=4)
		{
			if(filename.substr(filename.size()-4,filename.size()) != extensionString) 
				filename.append(extensionString);	
		} else filename.append(extensionString);
		
		ofstream file;
		file.open(filename.c_str(), ofstream::out);
		if(!file)
			cerr << "open file error :" << filename << " in write mode" << endl;
		else {
			if(verbose) cerr << "export GraphViz to " << filename << endl;
			exportGraphViz(file);
			file.close();
		}
	} else 
	{
		//no file specified. use stdout.
		exportGraphViz(cout);
	}
}

void automata::save(std::string filename, string modelName)
{
	string extensionString = ".a2a";
	if(!filename.empty())
	{
		//add the .a2a extension if not present.
		if(filename.size()>=4)
		{
			if(filename.substr(filename.size()-4,filename.size()) != extensionString) 
				filename.append(extensionString);	
		} else filename.append(extensionString);
		ofstream file;
		file.open(filename.c_str(), ofstream::out);
		if(!file)
			cerr << "open file error :" << filename << " in write mode" << endl;
		else {
			if(verbose) cerr << "export to " << filename << endl;
			//save(file, ddClassVector, modelName);
			save(file, modelName);
			file.close();
		}
	} else 
	{
		//no file specified. use stdout.
		//save(cout, ddClassVector, modelName);
		save(cout, modelName);
	}
}

//---------------------------------------------------------------------------*
//                                                                           *
//  A U T O M A T A    M I N I M I Z A T I O N                               *
//                                                                           *
//---------------------------------------------------------------------------*

//#define MINIMIZATION_DEBUG_MESSAGES

//---------------------------------------------------------------------------*

 void automata::minimize (const bool inVerboseMode)
{    
    C_Timer minimizationTimer ;
    C_Timer preparationTimer ;
    if(inVerboseMode) {
      cerr << "Minimizing automata..." << endl ;
    }
    const unsigned n = m_nbBitsToCodeAState;
    const unsigned t = m_nbBitsToCodeATransition;

    C_BDD BR ;
    
    // All (reachable) states. Expressed here as "all states source of a transition"
    C_Timer timer ;
    const C_BDD Reach = m_transitions.existsOnBitsAfterNumber(n);
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Reach' computed in " << timer << "\n" ;
    #endif
    //C_BDD Trans = m_transitions.swap213(n,t,n).existsOnBitsAfterNumber(t);

    { // We open a block so that useless BDDs will be eliminated at the end of fixed-point computation
      timer.startTimer () ;
      const C_BDD Reach2 = Reach.bddByLeftShifting(2*n+t) ;
      #ifdef MINIMIZATION_DEBUG_MESSAGES
        co << "  'Reach2' computed in " << timer << "\n" ;
      #endif
      
      timer.startTimer () ;
      const C_BDD Reach3 = Reach & Reach.bddByLeftShifting(n);
      #ifdef MINIMIZATION_DEBUG_MESSAGES
        co << "  'Reach3' computed in " << timer << "\n" ;
      #endif

      timer.startTimer () ;
      const C_BDD T1 = m_transitions.swap132(n,n+t,n);
      #ifdef MINIMIZATION_DEBUG_MESSAGES
        co << "  'T1' computed in " << timer << "\n" ;
      #endif

      timer.startTimer () ;
      const C_BDD T2 = m_transitions.swap132(n+t,n,n).bddByLeftShifting(n);
      #ifdef MINIMIZATION_DEBUG_MESSAGES
        co << "  'T2' computed in " << timer << "\n" ;
      #endif

      // Initially, all states are equivalent
      timer.startTimer () ;
      BR = Reach & Reach.bddByLeftShifting(n) ;
      #ifdef MINIMIZATION_DEBUG_MESSAGES
        co << "  'BR' computed in " << timer << "\n" ;
      #endif

      C_BDD it; // Bisimulation relation

      if (inVerboseMode) {
        cerr << "  Preparation done in " << preparationTimer.timeString ().cString (HERE) << "." << endl ;
      }
      // Fixpoint
      PMUInt32 iteration = 0 ;
      while (!it.isEqualToBDD(BR))
      {
          iteration ++ ;
          C_Timer iterationTimer ;

          C_BDD::markAndSweepUnusedNodes();
          it = BR;
          
          C_BDD T = T2;
          timer.startTimer () ;
          T &= BR.bddByLeftShifting(2*n+t);
          #ifdef MINIMIZATION_DEBUG_MESSAGES
            co << "  Iteration " << cStringWithUnsigned (iteration) << ", step a done in " << timer << "\n" ;
          #endif

          timer.startTimer () ;
          T &= Reach2;
          #ifdef MINIMIZATION_DEBUG_MESSAGES
            co << "  Iteration " << cStringWithUnsigned (iteration) << ", step b done in " << timer << "\n" ;
          #endif

          timer.startTimer () ;
          T = T.existsOnBitsAfterNumber(3*n+t);
          #ifdef MINIMIZATION_DEBUG_MESSAGES
            co << "  Iteration " << cStringWithUnsigned (iteration) << ", step c done in " << timer << "\n" ;
          #endif

          C_BDD::markAndSweepUnusedNodes();

          timer.startTimer () ;
          T = T1.implies(T);
          #ifdef MINIMIZATION_DEBUG_MESSAGES
            co << "  Iteration " << cStringWithUnsigned (iteration) << ", step d done in " << timer << "\n" ;
          #endif

          timer.startTimer () ;
          BR = T.forallOnBitsAfterNumber(2*n);     
          #ifdef MINIMIZATION_DEBUG_MESSAGES
            co << "  Iteration " << cStringWithUnsigned (iteration) << ", step e done in " << timer << "\n" ;
          #endif

          timer.startTimer () ;
          BR &= Reach3;
          #ifdef MINIMIZATION_DEBUG_MESSAGES
            co << "  Iteration " << cStringWithUnsigned (iteration) << ", step f done in " << timer << "\n" ;
          #endif

          timer.startTimer () ;
          T = BR.swap21(n,n) ;
          #ifdef MINIMIZATION_DEBUG_MESSAGES
            co << "  Iteration " << cStringWithUnsigned (iteration) << ", step g done in " << timer << "\n" ;
          #endif

          timer.startTimer () ;
          BR &= T ;
          #ifdef MINIMIZATION_DEBUG_MESSAGES
            co << "  Iteration " << cStringWithUnsigned (iteration) << ", step h done in " << timer << "\n" ;
          #endif
          if (inVerboseMode) {
            cerr << "  Iteration " << iteration << " done in " << iterationTimer.timeString ().cString (HERE) << "." << endl ;
          }
      }
    } // End of block

    C_Timer reductionTimer ;
    C_BDD::markAndSweepUnusedNodes();
    // Now find the representants for each equivalence class

    // All pairs of states q, q' satisfying q <= q'
    timer.startTimer () ;
    C_BDD T = C_BDD::varCompareVar(0,n,C_BDD::kLowerOrEqual,n);
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step A' computed in " << timer << "\n" ;
    #endif

    // The minimal reachable states
    // q R q' => q <= q'
    timer.startTimer () ;
    C_BDD Min = BR.implies(T).forallOnBitsAfterNumber(n) & Reach;
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step B' computed in " << timer << "\n" ;
    #endif

    // Finally find the reduced set of transitions
    // ss pp tttt qq
    timer.startTimer () ;
    T = Min & m_transitions.bddByLeftShifting(n);
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step C' computed in " << timer << "\n" ;
    #endif
       

    // ss pp tttt qq rr
    timer.startTimer () ;
    T = T.existsOnBitsAfterNumber(3*n+t) & Min.bddByLeftShifting(3*n+t);
    Min.setToFalse () ; // This BDD is no longer used 
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step D' computed in " << timer << "\n" ;
    #endif

    // Find the equivalent states
    timer.startTimer () ;
    T &= BR; 
    T &= BR.bddByLeftShifting(2*n+t);
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step E' computed in " << timer << "\n" ;
    #endif

//--- Perform "exist" on pp bits
// ss pp tttt qq rr -> ss (pp) tttt qq rr
    timer.startTimer () ;
    T = T.existsOnBitRange (n, n) ; 
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step Fa' computed in " << timer << "\n" ;
    #endif

//--- Perform "exist" on qq bits
// ss (pp) tttt qq rr -> ss (pp) tttt (qq) rr
    timer.startTimer () ;
    T = T.existsOnBitRange (n+n+t, n) ; 
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step Fb' computed in " << timer << "\n" ;
    #endif

//--- Perform substitution
// ss (pp) tttt (qq) rr -> ss tttt rr (qq) (pp)
    PMUInt32 * substitutionVector = NULL ;
    macroMyNewArray (substitutionVector, PMUInt32, 4 * n + t) ;
    for (PMUInt32 i=0 ; i<n ; i++) { // ss (n bits)
      substitutionVector [i] = i ;
    }
    for (PMUInt32 i=n ; i<(2 * n) ; i++) { // pp (n bits)
      substitutionVector [i] = i+2*n+t ;
    }
    for (PMUInt32 i=2*n ; i<(n * 2 + t) ; i++) { // tttt (p bits)
      substitutionVector [i] = i - n ;
    }
    for (PMUInt32 i=n*2+t ; i<(n * 3 + t) ; i++) {  // qq (n bits)
      substitutionVector [i] = i ;
    }
    for (PMUInt32 i=n*3+t ; i<(n * 4 + t) ; i++) {  // rr (n bits)
      substitutionVector [i] = i - 2*n ;
    }
    timer.startTimer () ;
    T = T.substitution (substitutionVector, 4*n+t COMMA_HERE);
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step G' computed in " << timer << "\n" ;
    #endif
    macroMyDeleteArray (substitutionVector) ;

//--- Perform "exist" on "pp" and "qq" bits
// Removed by PM (december 2010)
    /* timer.startTimer () ;
    m_transitions = T.existsOnBitsAfterNumber(2*n+t);
    #ifdef MINIMIZATION_DEBUG_MESSAGES
      co << "  'Step H' computed in " << timer << "\n" ;
    #endif
     */
    m_transitions = T ;
     
    C_BDD::markAndSweepUnusedNodes();
    if (inVerboseMode) {
      cerr << "  Computation of reduced automata done in " << reductionTimer.timeString ().cString (HERE) << "." << endl ;
    }
    if (inVerboseMode) {
      cerr << "Minimisation done in " << minimizationTimer.timeString ().cString (HERE) << "." << endl;
    }

//--- Temporaire
// //  const C_String predicate = m_transitions.queryStringValue (HERE) ;
// //  printf ("Predicate String Value of reduced automata: '%s'\n", predicate.cString (HERE)) ;
// //  const C_BDD readBDD = C_BDD::BDDWithPredicateString (predicate COMMA_HERE) ;
//   cout << "Read automata stats:\n" ;
// //  const PMUInt64 nbTransitions = readBDD.valueCount(m_nbBitsToCodeATransition+m_nbBitsToCodeAState*2);
// //  const unsigned int nbNodes = readBDD.getBDDnodesCount();
//   const PMUInt64 nbTransitions = m_transitions.valueCount(m_nbBitsToCodeATransition+m_nbBitsToCodeAState*2);
//   const unsigned int nbNodes = m_transitions.getBDDnodesCount();
//   cout << "\tnumber of transitions  : " << nbTransitions << endl;
//     // All (reachable) states. Expressed here as "all states source of a transition"
//   C_BDD states = m_transitions.existsOnBitsAfterNumber(m_nbBitsToCodeAState);
//  	PMUInt64 nbStates = states.valueCount(m_nbBitsToCodeAState);
//   cout << "\tnumber of states: " << nbStates << endl;
//  	cout << "\tBDD encoding : " << nbNodes << " nodes" << endl;
//--- Fin de temporaire			
}

//---------------------------------------------------------------------------*

