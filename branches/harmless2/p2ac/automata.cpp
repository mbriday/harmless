/** 
 * p2ac
 *
 * p2ac is copyright (c) IRCCyN 2005+
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
#include "instruction.h" //hashOfTransition
#include "pipelineNotification.h"
#include "instructionDescription.h"
#include "programDescription.h"
#include <iostream> //debug
#include <ostream> //ostream
#include <fstream> 
#include <math.h> 
#include "strings/C_String.h"
#include "time/C_Timer.h"
#define BR_MASK 1
#define DEBUG_MODE

extern bool verbose;

const char *AC2AC_OUTPUT_VERSION="3";

using namespace std;

//Constructor giving the size of the condition.
transitionCondition::transitionCondition(const unsigned int nbExternalResources) : m_nbExternalResources(nbExternalResources){ }

//Fill a transition condition with external resources.
void transitionCondition::addTransitionCondition(const unsigned int externalResources) {
	//external resources.
	assert(externalResources < (1UL<<m_nbExternalResources));
	m_conditionValue = externalResources;
}

//Constructor giving the size of the label
transitionLabel::transitionLabel(const unsigned int nbBitsToCodeAnInstruction) :
m_nbBitsToCodeAnInstruction(nbBitsToCodeAnInstruction){ }

//Fill a transition instruction with an instruction.
void transitionLabel::addTransitionLabel(const unsigned int inst) {
	//inst
	assert(inst < (1UL<<m_nbBitsToCodeAnInstruction));
	m_labelValue = inst;
}

//Computation of notifications
void transitionNotification::computeNotificationFromSystem(pipeline *pipe, C_BDD &systemNotification) {
	unsigned int code = 0;
	const unsigned int nbAct = pipe->getNbPipelineNotificationData();
	for(unsigned int i=0; i < nbAct; i++) {
		C_BDD notificationUnderTest = pipe->getPipelineNotificationData(i)->code();
		C_BDD temp = systemNotification & notificationUnderTest;
		if(!(temp.isFalse())) {
			//not false -> there is an intersection, current notification should be performed.
			code |= (1<<i);
		}
	}
	assert(nbAct > 0); //at least one notification should be defined in config file.
	m_val = code ;
}

//Get the number of bits to code notifications.
unsigned int const transitionNotification::nbBitsRequired(pipeline *pipe){
	return pipe->getNbPipelineNotificationData();
}

//void transitionNotification::setFetch(unsigned int val)
//{
//	assert(val <= 1);
//	m_notification |= C_BDD::varCompareConst (0, 1, C_BDD::kEqual, val) ;		
//}

//Constructor of an empty automata.
automata::automata(pipeline *pipe) : 
	m_pipeline(pipe),
	//TODO: Find a better way to give the nbBits of instruction and state
	m_nbBitsToCodeAnInstruction(32),//nbBitsToCodeValue(pipe->getNbInstruction()+1)),
	m_nbExternalResources(pipe->getNbExternalResources()),
	//TODO: I wonder if it is necessary to use pipe. At first, state is encoded on 32, and basta!
	m_nbBitsToCodeAState(pipe->getNbOfBitsToCodeAState()),//systemState::getNbBitsForStateCode(pipe)),
	m_nbBitsRequiredNotification(0),
	m_nbBitsRequiredCondition(0),
	m_nbBitsRequiredLabel(0)
{
	//get nb bits to code a transition.
	transitionNotification ta;
	transitionCondition tc(m_nbExternalResources);
	transitionLabel tl(m_nbBitsToCodeAnInstruction);
	m_nbBitsToCodeATransition = ta.nbBitsRequired(m_pipeline) + tl.nbBitsRequired() + tc.nbBitsRequired();

	m_nbTransition = 0;
	m_transitionArrayCapacity = 0 ;
	m_transitionArray = NULL ;
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

//Initialisation of the automata
void automata::computeInit(unsigned int start) {
	//Init tree with the root.
	systemState *rootSystemState = NULL ;
	macroMyNew(rootSystemState, systemState(m_pipeline));
	rootSystemState->checkHashCodeLength();

	//NbBitsForStateCode is higher in the compiled simulation.
	const unsigned int nbMaxSystemStates = 1 << (rootSystemState->getNbBitsForStateCode());

	//init with the root.
	rootSystemState->setPC(start);
	m_statesToProcessFifo.push_back(rootSystemState);
	m_stateVector.push_back(rootSystemState);
	
	#ifdef DEBUG_MODE
		ofstream monFlux("debug.dot");
		if(monFlux) {
			monFlux << "digraph g {" << endl;
			monFlux << "node [shape=doublecircle];" << endl;
			monFlux << "\"" << rootSystemState->pipelinePrint() << start << "\";" << endl;
			monFlux << "node [shape=ellipse];" << endl;
		} else {
			cerr << "Erreur d'ouverture du fichier debug.dot" << endl;
		}
	#endif
}

//Construction of the automata according to a program
void automata::computeAutomata(programDescription *program) {
	unsigned int start;
	start = program->getStart();
	computeInit(start);
	//Débogage pour la pile
	m_PCStackSizeMax = 0;
	while(m_statesToProcessFifo.size() != 0) { //fifo empty
		//if(verbose) debugFifoSize();
		systemState * currentState = m_statesToProcessFifo.back(); //no more a fifo :-)
		m_statesToProcessFifo.pop_back();
		//process the state.
		findStatesFromState(currentState, program);
	}
	#ifdef DEBUG_MODE
		ofstream monFlux("debug.dot",ios::app);
		monFlux << "}" << endl;
		cerr << "Nombre d'états : " << m_stateVector.size() << endl;
		cerr << "Taille maximale de la pile : " << m_PCStackSizeMax << endl;
	#endif
}

//Compute successors of a state
void automata::findStatesFromState(systemState *currentState, programDescription *program){
	const unsigned int nbRes =  m_pipeline->getNbExternalResources();
	const unsigned int nbCases = 1 << nbRes;
	unsigned int pc = currentState->getPC();
	unsigned int nextPC;
	instructionDescription *instd = (program->getInstructionDescriptionMap())[pc];
	//get the next system state. Must take into account all the external resource combinations.
	//TODO: Find a better exit condition.
	if(instd) {
		for(int resCase = nbCases-1; resCase >= 0; resCase--) {
			systemState *currentStateWithRes = NULL;
			macroMyNew (currentStateWithRes, systemState(*currentState));
			currentStateWithRes->setExternalRessources(resCase);
			//push the current instruction code into the pipeline.
			findNextSystemState(currentStateWithRes, resCase, instd, pc);
			macroMyDelete (currentStateWithRes);
		} //external resources
	}
}

//For an instruction and a case of external resources, compute the successor of a state.
void automata::findNextSystemState(systemState *currentStateWithRes, unsigned int resCase, instructionDescription *instd, unsigned int previousPC) {
	//notifications that are performed when going to the next state (alls the notifications)
	C_BDD systemNotification;
	unsigned int pc;
	//Translate instructionDescription in instruction
	instruction *inst = m_pipeline->getInstruction(instd);
	inst->setPC(previousPC);
	pc = previousPC + (m_nbBitsToCodeAnInstruction/8)*instd->getChunks();
	if(instd->getIsBranch()) {
		//instruction is a branch
		if(instd->getIsUnCond() || resCase & BR_MASK) {
			//instruction is an unconditional branch or a conditional but branch is taken
			if(instd->getIsIndirect()) {
				//An indirect branch is necessary a return instruction
				if(currentStateWithRes->isPCStackEmpty()) {
					cerr << "PC Stack empty, but must return!!" << endl;
				} else {
					pc = currentStateWithRes->topPCStack() + (m_nbBitsToCodeAnInstruction/8)*instd->getChunks();
				}
			} else {
				pc = instd->getTarget();
			}
		}
	}
	/* compute the next system state from the current one when
	an instruction is pushed in the pipeline */
	systemState *next = currentStateWithRes->getNext(inst, systemNotification, previousPC, pc);
	SEGFAULTIF(currentStateWithRes==next);
	//Arbitrarly, the first resource is the branching resource.
	if(instd->getIsBranch()) {
		//Instruction is a branch
		if(instd->getIsUnCond() || resCase & BR_MASK) {
			//instruction is an unconditional branch or a conditional but branch is taken
			if(next->getPC() != currentStateWithRes->getPC()) {
				//Instruction is entered in the pipeline
				if(instd->getIsCall()){
					//instruction is branch and link.
					next->pushPCStack(previousPC);
					//Test sur la taille de la pile
					m_PCStackSizeMax = next->getPCStackSize() > m_PCStackSizeMax ? next->getPCStackSize() : m_PCStackSizeMax;
				} else if(instd->getIsIndirect()) {
					//instruction is a return.
					next->popPCStack();
				}
			}
		}
	}
	int indexCurrent = findOrAddState(currentStateWithRes);
	int indexNext = findOrAddState(next);
	/* create (or update) the transition between the 2 automata states */
	/* the transition code is composed of the instruction id (the one that is fetched)
	 * and the external resources state */
	//transitionCondition.
	transitionCondition tc(m_nbExternalResources);	
	tc.addTransitionCondition(resCase);
	//transition label.
	transitionLabel tl(m_nbBitsToCodeAnInstruction);
	tl.addTransitionLabel(inst->getPC());
	//transtion notification.
	transitionNotification ta;
	ta.computeNotificationFromSystem(m_pipeline, systemNotification);
	//ta.setFetch(inst_move & 0x1); //an instruction may move in the first stage.
	#ifdef DEBUG_MODE
		//cerr << indexCurrent << " -> " << inst->getMnemo() << " -> " << indexNext << endl;
		ofstream monFlux("debug.dot",ios::app);
		if(monFlux) {
			if(indexNext == -1) {
				monFlux << "\"" << next->pipelinePrint() << next->getPC() << "\";" << endl;
			}
			monFlux << "\"" << currentStateWithRes->pipelinePrint() << currentStateWithRes->getPC() << "\" -> \"" << next->pipelinePrint() << next->getPC() << "\" [label = \"" << toBin(resCase,m_nbExternalResources) << ":" << inst->getPC() << "(" << toBin(ta.value(),ta.nbBitsRequired(m_pipeline)) << ")\"];" << endl;
		} else {
			cerr << "Erreur : impossible d'ouvrir le fichier debug.dot" << endl;
		}
	#endif
	if(indexNext == -1) {
		addTransition(indexCurrent, m_stateVector.size()-1, tc, tl, ta);
	} else {
		addTransition(indexCurrent, indexNext, tc, tl, ta);
	}
	/* add the automata state to the fifo list of states to process. */
	if(indexNext == -1) {
		//the automata/system state does not wait to be processed.
		m_statesToProcessFifo.push_back(next);
	} else {
		//the system state is already in the process list.
		macroMyDelete (next);
	}
}

int automata::findOrAddState(systemState *s) {
	int ret = -1;
	int i = 0;
	while(i < m_stateVector.size() && ret == -1) {
		if(s->compare(m_stateVector[i])){
			ret = i;
		}
		i++;
	}
	if(ret == -1){
		m_stateVector.push_back(s);
	}
	return ret;
}

//BDD:
// from lowest var to highest:
// -> fromStateId: m_nbBitsToCodeAState
// -> transition : m_nbBitsToCodeATransition
//		-> notification    : notification.nbBitsRequired()
//		-> condition : condition.nbBitsRequired()
// -> toStateId : m_nbBitsToCodeAState
void automata::addTransition(const unsigned int fromStateId, const unsigned int toStateId, transitionCondition &condition, transitionLabel &label, transitionNotification &notification) {
	if(!m_nbBitsRequiredNotification) {
		m_nbBitsRequiredNotification = notification.nbBitsRequired(m_pipeline);
	}
	if(!m_nbBitsRequiredCondition) {
		m_nbBitsRequiredCondition = condition.nbBitsRequired();
	}
	if(!m_nbBitsRequiredLabel) {
		m_nbBitsRequiredLabel = label.nbBitsRequired();
	}
	//bits 0 to (m_nbBitsToCodeAState-1)
	assert(fromStateId < (1UL<<m_nbBitsToCodeAState));
	//bits m_nbBitsToCodeAState to (m_nbBitsToCodeAState+m_nbBitsToCodeATransition-1)
	//cout << "act : " << notification.nbBitsRequired() << endl;
	//cout << "cond: " << condition.nbBitsRequired() << endl;
	//cout << "full: " << m_nbBitsToCodeATransition << endl;
	assert(notification.nbBitsRequired(m_pipeline)+condition.nbBitsRequired()+label.nbBitsRequired() <= m_nbBitsToCodeATransition);
	//bits (m_nbBitsToCodeAState+m_nbBitsToCodeATransition) to (2*m_nbBitsToCodeAState+m_nbBitsToCodeATransition-1)
	assert(toStateId < (1UL<<m_nbBitsToCodeAState));
	//printf("target: "); printBDD(target); printf("\n");
	//printf("\tcond: ");   printBDD(cond);   printf("\n");
	//printf("\tsource: "); printBDD(source); printf("\n");
	//printf("\tfull transition: "); printBDD(transition); printf("\n");
//---
	if (m_nbTransition >= m_transitionArrayCapacity) {
		m_transitionArrayCapacity += 10000000 ;
		macroMyReallocPODArray (m_transitionArray, __uint128_t, m_transitionArrayCapacity) ;
	}
//---
	// The semantics is : to.re.bit.inst.notif.from
	PMUInt64 notificationID = condition.getConditionValue () ;
	notificationID <<= m_nbBitsRequiredLabel ;
	notificationID |= label.getLabelValue () ;
	notificationID <<= m_nbBitsRequiredNotification ;
	notificationID |= notification.value () ;
	__uint128_t t = toStateId ;
	t <<= m_nbBitsToCodeATransition ;
	t |= notificationID ;
	t <<= m_nbBitsToCodeAState ;
	t |= fromStateId ;
	m_transitionArray [m_nbTransition] = t ;
	m_nbTransition ++;
}

void automata::printInternalConstants() {
	cout << "system stats" << endl;
	cout << "\tnb bits to code an instruction  : " << m_nbBitsToCodeAnInstruction << endl;
	cout << "\tnb bits to code an external res : " << m_nbExternalResources << endl;
	cout << "automata stats" << endl;
	cout << "\tnb bits to code a state         : " << m_nbBitsToCodeAState << endl;
	cout << "\tnb bits to code a transition    : " << m_nbBitsToCodeATransition << endl;
}

void automata::printInternalStats() {
	cout << "automata generation stats" << endl;
	PMUInt64 nbTransitions = m_transitions.valueCount(m_nbBitsToCodeATransition+m_nbBitsToCodeAState*2);
	const unsigned int nbNodes = m_transitions.getBDDnodesCount();
	cout << "\tnumber of transitions  : " << nbTransitions << endl;
	// All (reachable) states. Expressed here as "all states source of a transition"
	C_BDD states = m_transitions.existsOnBitsAfterNumber(m_nbBitsToCodeAState);
	PMUInt64 nbStates = states.valueCount(m_nbBitsToCodeAState);
	cout << "\tnumber of states: " << dec << nbStates << endl;
	cout << "\tBDD encoding : " << dec << nbNodes << " nodes (" << nbNodes * C_BDD::getBDDnodeSize () << " bytes)" << endl;
}

#pragma mark export

//edges are xx:yy(zz), ...
//which is:
// xx: external resource
// yy: instruction class
// zz: notification.
void automata::exportGraphViz(ostream &output) {
	__uint128_t t;
	PMUInt64 notificationID;
	unsigned int fromStateId, toStateId, label, condition, notification;
	std::string dotCondition;
	output << "# made with p2ac. IRCCyN" << endl;
	output << "digraph g {" << endl;
	unsigned int nbStates = m_stateVector.size()-1;
	unsigned int nbTransitions = 0;
	output << "node [shape=doublecircle];" << endl;
	output << "\"" << 0 << "\";" << endl;
	output << "node [shape=circle];" << endl;
	//Print states
	for(int i=1;i<=nbStates;i++){
		output << "\"" << hex << i << "\";" << endl;
	}
	//For each state, we consider transition from.
	for(int i=0;i<=nbStates;i++){
		//For each state, we consider transition to.
		for(int j=0;j<=nbStates;j++) {
			dotCondition = "";
			//We read the transition list.
			for(int k=0;k<m_nbTransition;k++) {
				t = m_transitionArray[k];
				fromStateId = t & (PMUInt64)((1UL << m_nbBitsToCodeAState) - 1);
				if(fromStateId == i) {
					toStateId = (t >> (m_nbBitsToCodeATransition+m_nbBitsToCodeAState)) & (PMUInt64)((1UL << m_nbBitsToCodeAState) -1);
					if(toStateId == j) {
						notificationID = (t >> m_nbBitsToCodeAState) & (PMUInt64)((1UL << m_nbBitsToCodeATransition) - 1);
						condition = (notificationID >> (m_nbBitsRequiredNotification+m_nbBitsRequiredLabel)) & (PMUInt64)((1UL << m_nbBitsRequiredCondition) -1);
						if(dotCondition!="") {
							dotCondition += ",";
						}
						dotCondition += toBin(condition, m_nbBitsRequiredCondition);
						nbTransitions++;
					}
				}
			}
			if (dotCondition != "") {
				notification = notificationID & (PMUInt64)((1UL << m_nbBitsRequiredNotification) -1);
				label = (notificationID >> m_nbBitsRequiredNotification) & (PMUInt64)((1UL << (m_nbBitsRequiredLabel)) -1);
				//TODO: Avoid the 32/8
				output << "\"" << hex << i << "\" -> \"" << j << "\" [label = \"" << dotCondition << ":" << dec << label << "(" << toBin(notification, m_nbBitsRequiredNotification) << ")\"];" << endl;
			}
		}
	}
	output << "}";
	output << endl << "# number of states : " << dec << nbStates << endl;
	output << "# number of transitions  : " << dec << nbTransitions << endl;
}

//To print correctly number in binary
static std::string toBin(__uint128_t u, unsigned int size) {
	__uint128_t div = 1;
	div <<= (size - 1);
	std::string s = "";
	while(div > 0){
		if(u & div) {
			s += '1';
		} else {
			s += '0';
		}
		div >>= 1;
	}
	return s;
}

//To print correctly number in hexadecimal
static std::string toHexa(unsigned int u, unsigned int size) {
	int div, i;
	unsigned int v;
	int zero = 1;
	std::string s = "0x";
	div = (int)pow(16,size);
	v = u;
	for(i=0; i<= size; i++) {
		zero = zero && v/div == 0;
		if(v/div > 9) {
			s += v/div + 7 + '0';
		} else if(!zero || i == size -1) {
			s += v/div + '0';
		}
		v = v % div;
		div = div / 16;
	}
	return s;
}

void automata::save(ostream &output, string modelName)
{
	//version
	output << "version " << AC2AC_OUTPUT_VERSION << endl; 
	output << "model " << modelName << endl;
	//superscalaire depth..always 1 in p2ac
	output << "depth 1" << endl; 
	//pipeline configuration.
	m_pipeline->save(output); //pipe, external res, instruction, notifications
	//automata
	PMUInt64 notificationID;
	unsigned int fromStateId, toStateId, label, condition, notification;
	//States don't need more than trueNbBitsToCodeState bits.
	unsigned int trueNbBitsToCodeAState;
	trueNbBitsToCodeAState = nbBitsToCodeValue(m_stateVector.size());
	output << trueNbBitsToCodeAState << " bits for a state" << endl;
	output << m_nbBitsToCodeATransition << " bits for a condition" << endl;
	//const C_String predicate = m_transitions.queryStringValue (HERE);
	//output << predicate.cString (HERE) << endl;
	// We write : from-(condition-label-notif)-to
	__uint128_t t = m_transitionArray[0];
	for(int i=0;i<m_nbTransition;i++){
		t = m_transitionArray[i];
		fromStateId = t & (PMUInt64)((1UL << m_nbBitsToCodeAState) - 1);
		notificationID = (t >> m_nbBitsToCodeAState) & (PMUInt64)((1UL << m_nbBitsToCodeATransition) - 1);
		toStateId = (t >> (m_nbBitsToCodeAState+m_nbBitsToCodeATransition)) & (PMUInt64)((1UL << m_nbBitsToCodeAState) - 1);
		if (i!=0) {
			output << "|";
		}
		output << toBin(fromStateId, trueNbBitsToCodeAState) << toBin(notificationID, m_nbBitsToCodeATransition) << toBin(toStateId, trueNbBitsToCodeAState) ;
		//cerr << hex << fromStateId << "-" << notificationID << "-" << toStateId << endl ;
	}
	output << "." << endl; 
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
	} else {
		//no file specified. use stdout.
		exportGraphViz(cout);
	}
}

void automata::save(std::string filename, string modelName)
{
	string extensionString = ".ac2ac";
	if(!filename.empty())
	{
		//add the .ac2ac extension if not present.
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
    PMUInt16 * substitutionVector = NULL ;
    macroMyNewArray (substitutionVector, PMUInt16, 4 * n + t) ;
    for (PMUInt16 i=0 ; i<n ; i++) { // ss (n bits)
      substitutionVector [i] = i ;
    }
    for (PMUInt16 i=n ; i<(2 * n) ; i++) { // pp (n bits)
      substitutionVector [i] = i+2*n+t ;
    }
    for (PMUInt16 i=2*n ; i<(n * 2 + t) ; i++) { // tttt (p bits)
      substitutionVector [i] = i - n ;
    }
    for (PMUInt16 i=n*2+t ; i<(n * 3 + t) ; i++) {  // qq (n bits)
      substitutionVector [i] = i ;
    }
    for (PMUInt16 i=n*3+t ; i<(n * 4 + t) ; i++) {  // rr (n bits)
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

