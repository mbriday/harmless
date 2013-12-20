
#include <stdlib.h>
#include <stdio.h>
#include "hadl-fields.h"
//#include "hadl-array.h"

#define HADL_BASE_SIZE (HADL_ADDR_WIDTH / HADL_ADDR_SUBDIV + ((HADL_ADDR_WIDTH % HADL_ADDR_SUBDIV != 0)? 1 : 0))
#define HADL_SEG_SIZE (1<<HADL_ADDR_SUBDIV)

template<class T>
struct HADL_Cell_t {
   T value;
   HADL_Time_t time;
   int isDefined;
   HADL_Cell_t<T> *previous;
};

static HADL_Array_t* HADL_Array_new()
{
   int i;
   HADL_Array_t* result = (HADL_Array_t*)malloc(sizeof(HADL_Array_t));
   *result = (void**)malloc(HADL_BASE_SIZE * sizeof(void*));

   for(i=0;i<HADL_BASE_SIZE;i++)
      result[i] = NULL;

   return result;
}

template<class T>
static void HADL_Array_getPath(int *path, int *depth, HADL_Array_t *array, int index) {

   /*
    * Build the path to the given index.
    * Each path element is a child index in the tree representation of the array.
    * At the end of the loop, *depth gives the number of tree levels that must be traversed.
    */

   unsigned tmp = index;
   *depth = -1;

   do
   {
      ++*depth;
      path[*depth] = tmp % HADL_SEG_SIZE;
      tmp >>= HADL_ADDR_SUBDIV;
   }while(tmp != 0);
}

template<class T, class D>
static D HADL_Array_getValue(HADL_Array_t *array, int index, HADL_Time_t *time)
{
   int path[HADL_BASE_SIZE];
   int div;
   int i;
   void** ptr;
   HADL_Cell_t<T> *cell;
   
   HADL_Array_getPath<T>(path, &div, array, index);

   /*
    * Get a reference to the correct sub-tree and check if a sub-tree exists.
    * If not, return an undefined value.
    */
   ptr = array[div];

   if(ptr == NULL)
      return HADL_UNDEFINED;

   /*
    * Traverse the tree until we get to an actual cell.
    * If the sub-tree is found empty at some stage, return an undefined value.
    * In the end, ptr[path[0]] is the expected cell.
    */
   for(;div>0;div--)
   {
      ptr = (void**)ptr[path[div]];
      if(ptr == NULL)
         return HADL_UNDEFINED;
   }
   
   cell = &((HADL_Cell_t<T>*)ptr)[path[0]];

   /*
    * The cell found corresponds to the latest assignment.
    * Set current time accordingly and return cell value.
    */
   
   if(cell->isDefined) {
      if(*time < cell->time)
         *time = cell->time;
   }
   
   printf("(SCH) Read performed at time: %lu\n", (long)*time);

   return cell->value;
}

template<class T>
static void HADL_Array_setValue(HADL_Array_t *array, int index, T value, HADL_Time_t *time)
{
   int path[HADL_BASE_SIZE];
   int div;
   int j;
   void*** ptr;
   HADL_Cell_t<T> *cell, *newCell;
   
   HADL_Array_getPath<T>(path, &div, array, index);
   
   ptr = &array[div];

   /*
    * Traverse the tree until we get to an actual cell.
    * If the sub-tree is found empty at some stage, allocate a new set of empty children.
    */
   for(;div>0;div--)
   {
      if(*ptr == NULL)
      {
         *ptr = (void**)malloc(HADL_SEG_SIZE*sizeof(void*));
         for(j=0;j<HADL_SEG_SIZE;j++)
            (*ptr)[j] = NULL;
      }

      ptr = (void***)&((*ptr)[path[div]]);
   }
   
   /*
    * If the last child is found empty, allocate a new set of cells.
    */
   if(*ptr == NULL) {
      *ptr = (void**)malloc(HADL_SEG_SIZE*sizeof(HADL_Cell_t<T>));
      for(j=0;j<HADL_SEG_SIZE;j++) {
         cell = &((HADL_Cell_t<T>*)*ptr)[j];
         cell->value = HADL_UNDEFINED;
         cell->time = (HADL_Time_t)-1;
         cell->isDefined = 0;
         cell->previous = NULL;
      }
   }

   /*
    * Get the cell at the proper time.
    */
   cell = &((HADL_Cell_t<T>*)*ptr)[path[0]];
   if(cell->isDefined) {
      newCell = (HADL_Cell_t<T>*)malloc(sizeof(HADL_Cell_t<T>));
      *newCell = *cell;
      cell->previous = newCell;
      if(*time >= cell->time)
         cell->time = *time + 1;
      else {
         *time = cell->time;
         ++cell->time;
      }
   }
   else
      cell->time = *time + 1;
      
   printf("(SCH) Write performed at time: %lu | Data available at time: %lu\n", (long)*time, (long)cell->time);

   cell->value = value;
   cell->isDefined = 1;
}

template<class T, class D>
static void HADL_Array_setField(HADL_Array_t* array, int index, D value, int r[][3], int n, HADL_Time_t *time)
{
   T data = HADL_Array_getValue<T,T>(array, index, time);
   HADL_Field_setValue<T, D>(&data, value, r, n);
   HADL_Array_setValue<T>(array, index, data, time);
}

template<class T>
static void HADL_Array_printValue(T value) {
   char* fmt;
   if(sizeof(T) == sizeof(long))
      fmt = "%lx";
   else if(sizeof(T) == sizeof(int))
      fmt = "%x";
   else
      fmt = "%hx";
   printf(fmt, value);
}

template<class T>
static void HADL_Array_printSegment(void** segment, unsigned long base, int depth)
{
   int i;
   HADL_Cell_t<T> *cell;
   for(i=0;i<HADL_SEG_SIZE;i++)
   {
      int addr = (base << HADL_ADDR_SUBDIV)+i;
      cell = &((HADL_Cell_t<T>*)segment)[i];
      if(depth == 0) {
         if(cell->isDefined) {
            printf("%lx <%lu>: ", addr, (long)cell->time);
            HADL_Array_printValue<T>(cell->value);
            printf("\n");
         }
         else
            printf("%lx <\?\?>: ??\n", addr);
      }
      else if(segment[i] != NULL)
         HADL_Array_printSegment<T>((void**)segment[i], addr, depth-1);
   }
}

template<class T>
static void HADL_Array_print(HADL_Array_t* array)
{
   int i;

   printf("-----\n");
   for(i=0;i<HADL_BASE_SIZE;i++)
      if(array[i] != NULL)
         HADL_Array_printSegment<T>(array[i], 0, i);
}

