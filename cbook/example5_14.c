#include <stdio.h>
#include <stdlib.h>

const char arr[] = "hello";
const char *cp  = arr;

int
main(int argc, char** argv)
{
	printf("sizeof(arr) = %lu\n", (unsigned long)sizeof(arr));
	printf("sizeof(*cp) = %lu\n", (unsigned long)sizeof(*cp));

	exit(EXIT_SUCCESS);
}
