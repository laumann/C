#include <stdio.h>
#include <stdlib.h>

#define CAPITALIZE	32

int
main(int argc, char** argv)
{
	char *alphabet = "abcdefghijklmnopqrstuvwxyz";

	for ( ; *alphabet; alphabet++)
		printf("'%c' has value: %d, capitalized: '%c'\n", *alphabet, (int) *alphabet, ((*alphabet)-CAPITALIZE));
	exit(EXIT_SUCCESS);
}
