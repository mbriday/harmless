
#ifndef __arm_dbg_IO_STUBS_H__
#define __arm_dbg_IO_STUBS_H__

#include <map>
#include <stdio.h> //FILE 

#include "types.h"
#include "action.h"

class ioStubOpen : public executeAction {
	std::map<int , FILE *> m_openedFiles;
public :
	ioStubOpen() : executeAction() {};
	virtual ~ioStubOpen() {};
    virtual bool trigger(arch *a);
	FILE *fileFor(int fd);
	std::string functionName() {return std::string("_open");};
};

class ioStubRead : public executeAction {
	ioStubOpen *m_iso;
public :
	ioStubRead(ioStubOpen *iso) : executeAction(), m_iso(iso) {};
	virtual ~ioStubRead() {};
    virtual bool trigger(arch *a);
	std::string functionName() {return std::string("_read");};
};

class ioStubWrite : public executeAction {
	ioStubOpen *m_iso;
public :
	ioStubWrite(ioStubOpen *iso) : executeAction(), m_iso(iso) {};
	virtual ~ioStubWrite() {};
    virtual bool trigger(arch *a);
	std::string functionName() {return std::string("_writeToFile");};
};

class ioStubPrintStdout : public executeAction {
	ioStubOpen *m_iso;
public :
	ioStubPrintStdout() : executeAction() {};
	virtual ~ioStubPrintStdout() {};
    virtual bool trigger(arch *a);
	std::string functionName() {return std::string("writechar");};
};
#endif
