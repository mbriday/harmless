#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UNLIMIT
#define MAXARRAY 60000  /*7.6 Mb this number, if too large, will cause a seg. fault!! */

struct myStringStruct {
  char qstring[128];
};

int compare(const void *elem1, const void *elem2)
{
  int result;
  
  result = strcmp((*((struct myStringStruct *)elem1)).qstring, (*((struct myStringStruct *)elem2)).qstring);

  return (result < 0) ? 1 : ((result == 0) ? 0 : -1);
}


int
main() {
  struct myStringStruct array[MAXARRAY];
  FILE *fp;
  int i,count=0;
  
//  if (argc<2) {
//    fprintf(stderr,"Usage: qsort_small <file>\n");
//    exit(-1);
//  }
//  else 
  {
    fp = fopen("./qsort/input_small.dat","r");
    
    while((count < MAXARRAY) && (fscanf(fp, "%s", array[count].qstring) != EOF)) {
	 count++;
    }
  }
  printf("\nSorting %d elements.\n\n",count);
  qsort(array,count,sizeof(struct myStringStruct),compare);
  
  for(i=0;i<count;i++)
    printf("%s\n", array[i].qstring);
  return 0;
}
