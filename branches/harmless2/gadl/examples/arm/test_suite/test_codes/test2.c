/* % square root with doubles
 * % inst: 10000
 */

#include <math.h>


int main () {
	while(1)
	{
		double a=10000.0;
		unsigned int i = 0;
		while(a != 1.0) {
			a = sqrt(a);
			i=i+1;
		}
	}
}


