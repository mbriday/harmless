/* % C file test with float computation
 * % inst: 1000
 */

#include <avr/io.h>

/* basic computation example */ 
int main()
{
	double a = 1.2345678;
	while(1)
	{
		if(a<1) a=a*2.56;
		else a = a/1.334;
	}
}

