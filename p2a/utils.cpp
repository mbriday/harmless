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


#include "utils.h"
#include <stdio.h>
#include "strings/C_String.h" //printBDD

using namespace std;


std::string int2str(int val, BASE _base)
{
	char c_str[64];
	switch(_base)
	{
		case DEC:
			sprintf(c_str, "%d", val);
			break;
		case HEX:
			sprintf(c_str, "%x", val);
			break;
	}			
	return string(c_str);
}

unsigned int nbBitsToCodeValue(unsigned int val)
{
	unsigned int result = 0;
	val--;
	while(val)
	{
		val >>=1;
		result++;
	}
	return result;
}

void printBDD(C_BDD &bdd)
{
	TC_UniqueArray <C_String> s ;
	//bdd.buildCompressedLittleEndianStringValueArray (s COMMA_HERE) ;
	bdd.buildCompressedBigEndianStringValueArray (s COMMA_HERE) ;
	for (int32_t i=0 ; i<s.count () ; i++) {
		if(i) printf(" | ");	
		printf ("'%s'", s (i COMMA_HERE).cString (HERE)) ;
	}
}

