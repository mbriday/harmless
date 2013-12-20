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

#ifndef __instructionDescription_H__
#define __instructionDescription_H__
#include <string>
#include <vector>
#include <fstream>
#include "utilities/M_machine.h"

class resourceDescriptor;

class instructionDescription {
	private:
	//used for reading the file. store symbols.
	std::string m_mnemo;
	unsigned int m_chunks;
	unsigned int m_idClass;
	unsigned int m_isBranch;
	unsigned int m_isUnCond;
	unsigned int m_isCall;
	unsigned int m_isIndirect;
	unsigned int m_target;

	public:
	instructionDescription();
	~instructionDescription();
	std::string getMnemo(){return m_mnemo;};
	void setMnemo(std::string mnemo) {m_mnemo = mnemo;};
	unsigned int getChunks() {return m_chunks;};
	void setChunks(unsigned int chunks) {m_chunks = chunks;};
	unsigned int getIdClass(){return m_idClass;};
	void setIdClass(unsigned int idClass){m_idClass = idClass;};
	unsigned int getIsBranch(){return m_isBranch;};
	void setIsBranch(unsigned int branch) {m_isBranch = branch;};
	unsigned int getIsUnCond(){return m_isUnCond;};
	void setIsUnCond(unsigned int unCond) {m_isUnCond = unCond;};
	unsigned int getIsCall(){return m_isCall;};
	void setIsCall(unsigned int call) {m_isCall = call;};
	unsigned int getIsIndirect(){return m_isIndirect;};
	void setIsIndirect(unsigned int indirect) {m_isIndirect = indirect;};
	unsigned int getTarget(){return m_target;};
	void setTarget(unsigned int target) {m_target = target;};
	void showId();
};
#endif
