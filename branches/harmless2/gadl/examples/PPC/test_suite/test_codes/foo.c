/* % C file test
 * % inst: 100
 */


unsigned int a=0;
unsigned int b=42;

int bar(int i)
{
	return i+1;
}

int foo(int i)
{
	return bar(i+1);
}

int main(void)
{
	int i=0;

	while(1)
	{
		i=i+2;
		i=foo(i);
		a ++;
		b++;
	}
}

