
#include <string.h>
#include <stdio.h>

template<class T>
void HADL_String_convert(char* buffer, T value, int base, char* numberPrefix, char* numberSuffix)
{
   char* fmt;

   switch(base)
   {
      case 2: fmt = "%s%lb%s"; break;
      case 8: fmt = "%s%lo%s"; break;
      case 10: fmt = "%s%ld%s"; break;
      case 16: fmt = "%s%lx%s";
   }
   
   sprintf(buffer, fmt, numberPrefix, (long)value, numberSuffix);
}

template<class T>
void HADL_String_convertList(char* buffer, T value, char* itemPrefix, char* itemSeparator, int base, char* numberPrefix, char* numberSuffix)
{
   buffer[0] = 0;
   HADL_Data_t index = 0;
   int sep = 0;
   
   while(value)
   {
      while(!(value & 1))
      {
         value >>= 1;
         ++index;
      }

      if(sep)
         strcat(buffer, itemSeparator);
      else
         sep = 1;
         
      strcat(buffer, itemPrefix);
      buffer += strlen(buffer);
      HADL_String_convert(buffer, index, base, numberPrefix, numberSuffix);
   }
}

