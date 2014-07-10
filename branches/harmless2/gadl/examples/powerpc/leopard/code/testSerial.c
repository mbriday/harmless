/* % Test Virtual Serial line 
 * % inst: 100
 */
typedef unsigned int uint32_t ; //no defined in my version.

#define CSRSL (*(volatile uint32_t *)(1000))
#define DR    (*(volatile uint32_t *)(1004))

char putChar(char c)
{
	while(CSRSL & 0x2); //wait for busy flag
	DR = c;
	return c;
}

void printString(char *str)
{
	char *_str = str;
	while(*_str) putChar(*_str++);
}

int main()
{
	CSRSL=0x1; //enable
	printString("Ceci est un test!");
	CSRSL=0;
	printString("Ceci est un test!");
}
