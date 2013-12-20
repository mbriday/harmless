/* % simple C test
 * % inst: 100
 */ 
int a = 0;

int main()
{
	int i;
	while(1)
	{
		for(i = 0; i < 100; i++)
			a ^= i;
	}
	return 0;
}
