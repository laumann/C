#include <stdio.h>
#include <stdlib.h>

int
main()
{
	int ar[20], *ip;

	for (ip = &ar[0]; ip < &ar[20]; ip++)
		*ip = 0;

	exit(EXIT_SUCCESS);
}
