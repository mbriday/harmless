/* % suite fibo C
 * % inst: 500
 */


typedef struct Couple Couple;
struct Couple {
	unsigned long val1;
	unsigned long val2;
};

Couple fibo2 (unsigned long n);
unsigned long fibo(unsigned long n);

int main () {

	unsigned long res;
	while(1)
		res = fibo(10);
	
	return 0;
}


Couple fibo2(unsigned long n) {
	if (n == 0) {
		Couple ret = {1,0};
		return ret;
	}
	else
	{
		Couple f_k = fibo2(n/2);
		unsigned long f2_k = f_k.val2*f_k.val2;
		
		if (n%2 == 0) {
			Couple ret = {f2_k + f_k.val1*f_k.val1,f_k.val2*f_k.val1*2 + f2_k};
			return ret;
		}
		else 
		{
			Couple ret = {f_k.val2*f_k.val1*2 + f2_k, (f_k.val2 + f_k.val1)*(f_k.val2 + f_k.val1) + f2_k};
			return ret;
		}
	}
}

unsigned long fibo(unsigned long n) {
	Couple res = fibo2(n);
	return res.val2;
}
