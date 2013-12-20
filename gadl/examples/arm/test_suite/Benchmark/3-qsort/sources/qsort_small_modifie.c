#include <stdlib.h>
#include <stdio.h>
#include <string.h>
  
#define UNLIMIT

struct myStringStruct {
  char qstring[128];
};

/* QEMU specific code */

volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;

void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 *UART0DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}

/* end QEMU specific code */


#include "input_small.txt"


int compare(const void *elem1, const void *elem2)
{
  int result;
  
  result = strcmp((*((struct myStringStruct *)elem1)).qstring, (*((struct myStringStruct *)elem2)).qstring);

  return (result < 0) ? 1 : ((result == 0) ? 0 : -1);
}


int main(int argc, char *argv[]) {
 
  unsigned int i;
  struct myStringStruct *tmp;
    
  for(i=0;i<100;i++) {
  	tmp = input_small;
    qsort(tmp,cpt,sizeof(struct myStringStruct),compare);
  } 
     
  print_uart0("q\n"); // Needed to stop QEMU
    
  return 0;
}
