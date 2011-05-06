#include <stdio.h>
#include <stdlib.h>

#define ARSZ	10

int
main()
{
	int ar[ARSZ], i;

	for (i=0; i < ARSZ; i++) {
		ar[i] = i;
		i[ar]++;
		printf("ar[%d] = %d\n", i, i[ar]);
	}

	printf("15[ar] = %d\n", 15[ar]);
	exit(EXIT_SUCCESS);
}
