
#ifndef __HADL_STRING__
#define __HADL_STRING__

#include "hadl-custom.h"

template<class T>
void HADL_String_convert(char* buffer, T value, int base, char* numberPrefix, char* numberSuffix);

template<class T>
void HADL_String_convertList(char* buffer, T value, char* itemPrefix, char* itemSeparator, int base, char* numberPrefix, char* numberSuffix);

#include "hadl-string.cpp"

#endif

