#include <stdio.h>

int main()
{
	char buf[512];
	FILE *fp;
    fp = fopen("./test.txt","r");
	if(fp)
	{
		printf("file descriptor : %d\n", fp->_file);
		while(fscanf(fp, "%s", buf) > 0)
		{
			printf("token read '%s' \n", buf);
		} 
		printf("no more data\n");
	} else printf("file not found.\n");
	while(1);
}
