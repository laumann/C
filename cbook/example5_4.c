#include <stdio.h>
#include <stdlib.h>

#define ARSZ	10

int
main()
{
	float fa[ARSZ], *fp1, *fp2;

	fp1 = fp2 = fa;	/* Address of first elemnt */

	/*
		x[5] == *(x + 5) == *(&x[0] + 5)

		&x[5] == &(*(x + 5)) == x + 5

		=>

		&fa[ARSZ] == &( *(fa + ARSZ)) = fa + ARSZ
	*/

	for ( ; fp2 != fa + ARSZ; fp2++) 
		printf("Difference: %d\n", (int) (fp2-fp1));

	exit(EXIT_SUCCESS);
}
