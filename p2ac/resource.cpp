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

#include "resource.h"
#include <iostream> 
#include "utils.h" //SEGFAULTIF.

resourceDescriptor::resourceDescriptor(const std::string name, const int nbMaxValue, const bool external)
:  m_maxAllowed(nbMaxValue),
m_name(name),
m_external(external)
{
	//std::cerr << "add the resourceDescriptor " << m_name << "(id:" << m_id << ")" << std::endl;
}
 std::string const resourceDescriptor::debug()
{
	std::string result = m_name+"("+int2str(m_maxAllowed)+")";
	return result;
}

resourceDescriptor::~resourceDescriptor()
{
	//std::cerr << "delete the resourceDescriptor : " << m_name << std::endl;
}

pipelineStageDescriptor *resourceDescriptor::getPipelineStageDescriptorAtPriority(unsigned int index) const
{
	SEGFAULTIF(index >= m_priorityVector.size())
	return m_priorityVector[index];
}
