/* % first order time reponse to a step
 * % inst: 10000
 */

#include <math.h>


int main () {
	double K=5.0;
	double T=0.1; //100ms
	volatile double out = 0;
	double time;
	while(1)
	{
		for(time = 0.0; time < 20.0; time=time+0.005) //response for 20 s (98%), each 5 ms.
		{
			out = K*(1-exp(T*time));
		}
	}
}


