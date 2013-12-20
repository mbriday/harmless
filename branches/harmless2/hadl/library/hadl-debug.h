
#ifndef __HADL_DEBUG__
#define __HADL_DEBUG__

#include "hadl-custom.h"
#include <stdio.h>

#if HADL_DEBUG
#define HADL_Debug_printMessage(data) printf("%s\n", data)
#define HADL_Debug_printTime(message, data) \
   if(sizeof(data) == sizeof(short)) \
      printf("%s%hu\n", message, (short)data); \
   else \
      printf("%s%lu\n", message, (long)data);
#else
#define HADL_Debug_printMessage(data)
#define HADL_Debug_printTime(message, data)
#endif

#if HADL_ASM_DUMP
#define HADL_Debug_asmDump(data) printf("(ASM) %s\n", data)
#else
#define HADL_Debug_asmDump(data)
#endif

#endif

