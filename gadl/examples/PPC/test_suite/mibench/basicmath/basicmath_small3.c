#include "snipmath.h"
#include <math.h>
#include <stdio.h>
/* The //printf's may be removed to isolate just the math calculations */

int main(void)
{
  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
  double  a3 = 1.0, b3 = -3.5, c3 = 22.0, d3 = -31.0;
  double  a4 = 1.0, b4 = -13.7, c4 = 1.0, d4 = -35.0;
  double  x[3];
  double X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;
  long n = 0;

  //printf("********* ANGLE CONVERSION ***********\n");
  /* convert some rads to degrees */
  for (X = 0.0; X <= 360.0; X += 1.0)
  {
    printf("%3.0f degrees = %.12f radians\n", X, deg2rad(X));
    puts("");
  }
  for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 180))
  {
    printf("%.12f radians = %3.0f degrees\n", X, rad2deg(X));
  }
  
  
  return 0;
}
