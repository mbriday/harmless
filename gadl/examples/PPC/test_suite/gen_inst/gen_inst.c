/*
 * GEN_INST : Creates a random file of the given size in the file given
 *
 * example : "gen_inst 1024 foo"
 * 	create a foo random file of 1 kib
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	FILE * raw_bin;
	int size=0;
	int i;
	srand(time(NULL));

	if(argc!=3)
	{
		fprintf(stderr, "usage: %s Size(bytes) output_file\n", argv[0]);
		exit(42);
	}

	size=atoi(argv[1]);

	raw_bin = fopen(argv[2], "w");

	for(i=0; i<size/4;i++)
	{
		uint32_t tmp;
		tmp = rand();

		fwrite(&tmp, sizeof(uint32_t), 1, raw_bin);
	}

	fclose(raw_bin);
}
