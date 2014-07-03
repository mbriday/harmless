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

#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include <string>
#include <vector>
#include "utils.h"

class pipeline;
class pipelineStageDescriptor;

class resourceDescriptor
{
private:
	///max number of time a resource can be used
	///at a given date
	const unsigned int m_maxAllowed;
	///name of the resource.
	std::string m_name;
	///if the resource is external.
	bool m_external;
	///priorities of access to the resource.
	std::vector<pipelineStageDescriptor *> m_priorityVector;
	
public:
	resourceDescriptor(const std::string name, const int nbMaxValue = 1, const bool external = false);
	virtual ~resourceDescriptor();
	///return the resource name
	inline std::string const toString() {return m_name;};
	///debug info.
	virtual std::string const debug();
	///return the maximum number of time a resource can be used
	///at a given date.
	inline unsigned int const maxAllowed() {return m_maxAllowed;};
	///check if the resource is used by more than one pipeline.
	inline bool const isExternal() {return m_external;};
	///during configuration, set access priority to the resource
	void addPriority(pipelineStageDescriptor *ps) {m_priorityVector.push_back(ps);};
	///nb of priorities to the resource (correspond to the nb of pipeline stage the resource can be taken)
	uint32_t const getNbPriorities() {return m_priorityVector.size();};
	///get pipeline stage descriptor at priority 'prio'
	pipelineStageDescriptor *getPipelineStageDescriptorAtPriority(unsigned int index) const;
};

class resource
{
	//static descriptor of the ressource.
	resourceDescriptor *m_desc;
	//dynamic: number of times the ressource is taken.
	unsigned int m_taken;

	public:
	resource() {};
	inline void setResourceDescriptor(resourceDescriptor *desc) {m_desc = desc;};
	///may only be called by external resources, or internal resources for init only (use take/give instead)
	inline void setTaken(unsigned int inTaken) {m_taken = inTaken;};
	inline unsigned int const taken() {return m_taken;};
	inline void take(const unsigned int nbTimes) {
		m_taken+=nbTimes; 
		SEGFAULTIF(m_taken>m_desc->maxAllowed())
		SEGFAULTIF(m_desc->isExternal())
	};
	inline void give(const unsigned int nbTimes) {
		m_taken -= nbTimes;
		SEGFAULTIF(m_taken>m_desc->maxAllowed())  //unsigned int..
		SEGFAULTIF(m_desc->isExternal())
	};
	inline bool const isAvailable(const unsigned int nbTimes) {return (m_taken+nbTimes) <= (m_desc->maxAllowed());};
	inline resourceDescriptor * const descriptor() {return m_desc;};
};

#endif

