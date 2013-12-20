
#include <stdio.h>
#include <stdlib.h>
#include "hadl-array.h"

static void HADL_Srec_error(const char* message, int line, int column, char* buffer)
{
   printf("ERROR (%d:%d) - %s\n", line, column, message);
   printf("  Current line: %s\n", buffer);
   exit(1);
}

static int HADL_Srec_asciiToHex(char c, int line, int column, char* buffer)
{
   if(c < '0')
      HADL_Srec_error("Invalid s-record file: expecting hex digit", line, column, buffer);
   else if(c <= '9')
      return c - '0';
   else if(c < 'A')
      HADL_Srec_error("Invalid s-record file: expecting hex digit", line, column, buffer);
   else if(c <= 'F')
      return c - 'A' + 10;
   else
      HADL_Srec_error("Invalid s-record file: expecting hex digit", line, column, buffer);
}

int HADL_Srec_getChar(FILE* file, int checkEof, int line, int* column, char* buffer)
{
   if(checkEof && feof(file))
      HADL_Srec_error("Invalid s-record file: truncated record", line, *column, buffer);
   else {
      char c = fgetc(file);
      buffer[*column] = c;
      ++ *column;
      buffer[*column] = 0;
      return c;
   }
}

void HADL_Srec_readArrayFromFile(FILE* file, HADL_Array_t* array, int wordSize, int bigendian, HADL_Time_t time) 
{
   int line = 0;
   char buffer[256];

   while(1)
   {
      char start, type, any;
      unsigned size, address;
      int addrSize;
      HADL_Data_t byte, data;
      int i,j;
      int column = 0;

      /* Each line starts with 'S' -------------------------------------------- */

      ++line;
      buffer[0] = 0;

      /* Search start of line or end of file */
      do
      {
         if(feof(file))
            return;
         start = HADL_Srec_getChar(file, 0, line, &column, buffer);
      }while((start == '\0') || (start == '\r') || (start == '\n'));

      if(feof(file))
         return;

      if(start != 'S')
         HADL_Srec_error("Invalid s-record file: expecting 'S'", line, column, buffer);

      /* Next byte : type ----------------------------------------------------- */

      type = HADL_Srec_getChar(file, 1, line, &column, buffer);

      if((type < '0') || (type > '9'))
         HADL_Srec_error("Invalid s-record file: unsupported record type", line, column, buffer);

      /* Special records : move to next line or end of file */
      if((type == '0') || (type > '3'))
      {
         do
         {
            if(feof(file))
               return;
            any = HADL_Srec_getChar(file, 0, line, &column, buffer);
         }while((any != '\0') && (any != '\r') && (any != '\n'));

         continue;
      }
      
      /* Data record : get address size */
      switch(type)
      {
         case '1': addrSize = 4; break;
         case '2': addrSize = 6; break;
         case '3': addrSize = 8;
      }
      
      /* Next two bytes : size */
      size = HADL_Srec_asciiToHex(HADL_Srec_getChar(file, 1, line, &column, buffer), line, column, buffer) << 4;
      size += HADL_Srec_asciiToHex(HADL_Srec_getChar(file, 1, line, &column, buffer), line, column, buffer);

      size -= addrSize/2 + 1;            /* Size of data, without address and checksum */
      size /= wordSize;                  /* Size in words */
      
      /* Next 4-8 bytes : address */
      address = 0;
      for(i=0;i<addrSize;i++)
      {
         address <<= 4;
         address += HADL_Srec_asciiToHex(HADL_Srec_getChar(file, 1, line, &column, buffer), line, column, buffer);
      }

      /* Next bytes : data */
      address /= wordSize;
      for(i=0;i<size;i++)
      {
         data = 0;
         for(j=0;j<wordSize;j++)
         {
            byte = HADL_Srec_asciiToHex(HADL_Srec_getChar(file, 1, line, &column, buffer), line, column, buffer) << 4;
            byte |= HADL_Srec_asciiToHex(HADL_Srec_getChar(file, 1, line, &column, buffer), line, column, buffer);
            
            if(bigendian)
            {
               data <<= 8;
               data |= byte;
            }
            else
               data |= byte << (j*8);
         }

         HADL_Array_setValue(array, address, data, &time);
         ++address;
      }
      
      /* Next bytes : checksum */
      HADL_Srec_asciiToHex(HADL_Srec_getChar(file, 1, line, &column, buffer), line, column, buffer);
      HADL_Srec_asciiToHex(HADL_Srec_getChar(file, 1, line, &column, buffer), line, column, buffer);
   }
}

