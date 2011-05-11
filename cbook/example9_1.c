#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int
main()
{
	size_t distance;
	typedef struct x{
		int a,b,c;
	} s_tr;

	distance = offsetof(s_tr, a);
	printf("Offset of x.a is %lu bytes\n", (unsigned long)distance);

	distance = offsetof(s_tr, b);
	printf("Offset of x.b is %lu bytes\n", (unsigned long)distance);

	distance = offsetof(s_tr, c);
	printf("Offset of x.c is %lu bytes\n", (unsigned long)distance);

	exit(EXIT_SUCCESS);
}
