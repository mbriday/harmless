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

#ifndef __UTILS_H__
#define __UTILS_H__
#include <string>
#include "bdd/C_BDD.h"
#include <assert.h>

enum BASE{
	DEC,
	HEX
};

///fonction that convert an int to a string.
std::string int2str(int val, BASE base=DEC);

#define MAX(A,B) ((A)>(B) ? (A) : (B))

///make a segfault -> usefull to debug as it generates a "core dump".
#ifdef NO_DEBUG
	#define SEGFAULTIF(cond)
#else
	#define SEGFAULTIF(cond) assert(!(cond));
#endif

//code for instruction movement in the pipeline.
//1 at bit 0 means that the first stage get a new instruction...
//the code must be associated with a transition.
//it models "instruction movements", and stalls are not considered!!
typedef unsigned int hash_inst_move; //TODO update

//hash code for transitions and states.
typedef unsigned int hash_length;

unsigned int nbBitsToCodeValue(unsigned int val);

void printBDD(C_BDD &bdd); //debug.

#endif

