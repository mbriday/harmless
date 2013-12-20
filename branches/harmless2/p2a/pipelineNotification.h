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
#ifndef __AUTOMATA_ACTION_H__
#define __AUTOMATA_ACTION_H__
#include "utils.h" //hash_length
#include "bdd/C_BDD.h"
class pipeline;


//this class define notifications that the automata should inform the simulator.
//here are examples:
//add notification fetch  when instruction enters in stage F //mandatory for simulation
//add notification nbInst when instruction exits stage R     //mandatory for simulation
//add notification act1 when instruction A enters in stage R
// this class generate the code from data.
// ******************************
// NOTE: no pipeline stage nor instruction class should be defined after
// ******************************
class pipelineNotificationEncoder {
	//code size in bits (with instruction)
	unsigned int m_codeSize;
	//code size in bits (with any instruction)
	unsigned int m_codeSizeAny;
	//number of bits required to code the stage (value needed to generate the code).
	unsigned int m_nbBitsStage;
	//number of bits required to code an instruction class (value needed to generate the code).
	unsigned int m_nbBitsInst;

	hash_length getNotificationCode(const unsigned int instructionClassId, const unsigned int stageId, const bool enter);
	
	public:
	pipelineNotificationEncoder(pipeline *pipe);
	C_BDD getBdd(const unsigned int instructionClassId, const unsigned int stageId, const bool enter);
	inline unsigned int const getCodeSize() {return m_codeSize;};
};

//this class define notifications that the automata should inform the simulator.
//here are examples:
//add notification fetch  when instruction enters in stage F //mandatory for simulation
//add notification nbInst when instruction exits stage R     //mandatory for simulation
//add notification act1 when instruction A enters in stage R
// This class stores information related to notifications.
class pipelineNotificationData {
	std::string m_name;
	unsigned int m_classId;
	unsigned int m_stageId;
	bool m_enter;
	//internal code.
	C_BDD m_code;
	public:
	pipelineNotificationData(pipeline *pipeline, std::string name, const unsigned int classId, const unsigned int stageId, const bool enter);
	std::string name() {return m_name;};
	inline unsigned int const classId() {return m_classId;};
	inline unsigned int const stageId() {return m_stageId;};
	inline bool const enterInStage() {return m_enter;};
	inline C_BDD code() {return m_code;};
};

#endif
