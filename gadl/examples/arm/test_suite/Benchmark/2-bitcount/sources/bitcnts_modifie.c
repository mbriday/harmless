/* +++Date last modified: 05-Jul-1997 */

/*
**  BITCNTS.C - Test program for bit counting functions
**
**  public domain by Bob Stout & Auke Reitsma
*/

#include <stdlib.h>
#include "conio.h"
#include <limits.h>
#include "bitops.h"

#define FUNCS  7

/* QEMU specific code */

volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;

void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 *UART0DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}

/* end QEMU specific code */

static int CDECL bit_shifter(long int x);

int main(int argc, char *argv[])
{
  int i;
  long j, n, seed;
  int iterations;
  static int (* CDECL pBitCntFunc[FUNCS])(long) = {
    bit_count,
    bitcount,
    ntbl_bitcnt,
    ntbl_bitcount,
    /*            btbl_bitcnt, DOESNT WORK*/
    BW_btbl_bitcount,
    AR_btbl_bitcount,
    bit_shifter
  };
  static char *text[FUNCS] = {
    "Optimized 1 bit/loop counter",
    "Ratko's mystery algorithm",
    "Recursive bit count by nybbles",
    "Non-recursive bit count by nybbles",
    /*            "Recursive bit count by bytes",*/
    "Non-recursive bit count by bytes (BW)",
    "Non-recursive bit count by bytes (AR)",
    "Shift and count bits"
  };

  iterations=100000;
  
  for (i = 0; i < FUNCS; i++) {
    
    for (j = n = 0, seed = rand(); j < iterations; j++, seed += 13) {
		n += pBitCntFunc[i](seed);
    }
    
  }
  
  print_uart0("q\n"); // Needed to stop QEMU
  return 0;
}

static int CDECL bit_shifter(long int x)
{
  int i, n;
  
  for (i = n = 0; x && (i < (sizeof(long) * CHAR_BIT)); ++i, x >>= 1)
    n += (int)(x & 1L);
  return n;
}
