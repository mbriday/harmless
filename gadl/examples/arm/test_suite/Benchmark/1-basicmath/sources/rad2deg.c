/* +++Date last modified: 05-Jul-1997 */

/*
**  RAD2DEG.C - Functions to convert between radians and degrees
*/

#include <math.h>
#include "snipmath.h"

#undef rad2deg                /* These are macros defined in PI.H */
#undef deg2rad

double rad2deg(double rad)
{
      return (180.0 * rad / (PI));
}

double deg2rad(double deg)
{
      return (PI * deg / 180.0);
}
