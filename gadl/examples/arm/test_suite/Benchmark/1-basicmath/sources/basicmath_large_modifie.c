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

int main(void)
{
  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  x[3];
  double X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;
  long n = 0;
  double rad1, deg1, rad2, deg2;

  /* solve soem cubic functions */
  
  /********* CUBIC FUNCTIONS ***********/
  /* should get 3 solutions: 2, 6 & 2.5   */
  SolveCubic(a1, b1, c1, d1, &solutions, x);  
    
   a1 = 1.0; b1 = -4.5; c1 = 17.0; d1 = -30.0;
  /* should get 1 solution: 2.5           */
  SolveCubic(a1, b1, c1, d1, &solutions, x);  
 
  a1 = 1.0; b1 = -3.5; c1 = 22.0; d1 = -31.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
 
  a1 = 1.0; b1 = -13.7; c1 = 1.0; d1 = -35.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  
  a1 = 3.0; b1 = 12.34; c1 = 5.0; d1 = 12.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
 
  a1 = -8.0; b1 = -67.89; c1 = 6.0; d1 = -23.6;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
   
  a1 = 45.0; b1 = 8.67; c1 = 7.5; d1 = 34.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
    
  a1 = -12.0; b1 = -1.7; c1 = 5.3; d1 = 16.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  
  /* Now solve some random equations */
  for(a1=1;a1<10;a1+=1) {
    for(b1=10;b1>0;b1-=.25) {
      for(c1=5;c1<15;c1+=0.61) {
	   for(d1=-1;d1>-5;d1-=.451) {
		SolveCubic(a1, b1, c1, d1, &solutions, x);  
		   }
      }
    }
  }


  /********** INTEGER SQR ROOTS ***********/
  /* perform some integer square roots */
  for (i = 0; i < 100000; i+=2)
    {
      usqrt(i, &q);
	}
  
  for (l = 0x3fed0169L; l < 0x3fed4169L; l++)
    {
	 usqrt(l, &q);
    }


  /********** ANGLE CONVERSION ***********/
  /* convert some rads to degrees */
  /*degrees to radians*/
/*   for (X = 0.0; X <= 360.0; X += 1.0) */
  
  for (deg1 = 0.0; deg1 <= 360.0; deg1 += .001)
  {
  		rad1= deg2rad(deg1);
  		//printf("%3.0f degrees = %.12f radians\n", deg1, rad1);  
  };
  
/*   for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 180)) */

	/*radians to degrees*/
  for (rad2 = 0.0; rad2 <= (2 * PI + 1e-6); rad2 += (PI / 5760))
  {
  		deg2= rad2deg(rad2);  		
   	//printf("%.12f radians = %3.0f degrees\n", rad2, deg2);
   };
  
  
  print_uart0("q\n"); // Needed to stop QEMU
  return 0;
}
