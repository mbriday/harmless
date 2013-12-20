
#include <stdarg.h>

struct FakeBehaviorStruct {
   int path;
   struct FakeBehaviorStruct* parent;
};

template<class T>
int HADL_checkPath(T instr, int range[][3], int rangeSize, int mask, int value, void* parent, int pathTail, int pathSize, ...)
{
   va_list path;
   int index, pathElement;
   struct FakeBehaviorStruct* ptr = (struct FakeBehaviorStruct*)parent;

   /* Check instruaction field if applicable */
   if(range != NULL && (HADL_Field_getValue<T,T>(instr, range, rangeSize, 0, 0, 0, 0) & mask != value))
      return 0;

   va_start(path, pathSize);
   for(index=0;index<pathSize;index++) {
      pathElement = va_arg(path, int);
      if(pathTail != pathElement)
         return 0;
      pathTail = ptr->path;
      ptr = ptr->parent;
   }
   va_end(path);
   return 1;
}

