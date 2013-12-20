#include "snipmath.h"
#include <math.h>
/* The printf's may be removed to isolate just the math calculations */

/* QEMU specific code */

volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;

void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 *UART0DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}

/* end QEMU specific code */

int main()
{
  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
  double  a3 = 1.0, b3 = -3.5, c3 = 22.0, d3 = -31.0;
  double  a4 = 1.0, b4 = -13.7, c4 = 1.0, d4 = -35.0;
  double  x[3];
  double X;
  int solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;
  long n = 0;
  
  double rad1, deg1, rad2, deg2;

  /* solve soem cubic functions */
  /************CUBIC FUNCTIONS ***********\n");
  /* should get 3 solutions: 2, 6 & 2.5   */
  SolveCubic(a1, b1, c1, d1, &solutions, x);  
   
   /* should get 1 solution: 2.5           */
  SolveCubic(a2, b2, c2, d2, &solutions, x);  
    
  SolveCubic(a3, b3, c3, d3, &solutions, x);
    
  SolveCubic(a4, b4, c4, d4, &solutions, x);
    
  
  /* Now solve some random equations */
  for(a1=1;a1<10;a1++) {
    for(b1=10;b1>0;b1--) {
      for(c1=5;c1<15;c1+=0.5) {
	for(d1=-1;d1>-11;d1--) {
	  SolveCubic(a1, b1, c1, d1, &solutions, x); 	  
			}
      }
    }
  }
    
  
  /********** INTEGER SQR ROOTS ************/
  /* perform some integer square roots */
	for (i = 0; i < 1001; ++i)
    {
      usqrt(i, &q);
    }


	usqrt(l, &q);
  


  /*"********* ANGLE CONVERSION ***********/
  /* convert some rads to degrees */
  // degree to radians*/
	for (deg1 = 0.0; deg1 <= 360.0; deg1 += 1.0)
	{
  		rad1=deg2rad(deg1);
  	}

	/*radians to degree*/
    
	for (rad2 = 0.0; rad2 <= 360.0; rad2 += 1.0)
	{
  		deg2 = rad2deg(rad2);
  	}

    
  print_uart0("q\n"); // Needed to stop QEMU
  return 0;
}   
