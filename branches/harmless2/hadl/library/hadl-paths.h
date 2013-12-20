
#ifndef __HADL_PATHS__
#define __HADL_PATHS__

#include "hadl-custom.h"

template<class T>
int HADL_checkPath(T instr, int range[][3], int rangeSize, int mask, int value, void* parent, int pathTail, int pathSize, ...);

#include "hadl-paths.cpp"

#endif

