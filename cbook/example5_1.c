#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char** argv)
{
	int x, *p;

	p = &x;		/* init pointer */
	*p = 0;		/* set x to zero */

	printf(" x is %d\n", x);
	printf("*p is %d\n", *p);

	*p += 1;	/* Increment what p points to */
	printf(" x is %d\n", x);

	(*p)++;		/* Increment again */
	printf(" x is %d\n", x);

	exit(EXIT_SUCCESS);
}
