#include "sinecosine.h"
#include <stdio.h>
#include <stdlib.h>

#define ZERO	0.0
#define ONE	1.0
#define HALF	(1.0/2.0)
#define THIRD	(1.0/3.0)
#define FOURTH	(1.0/4.0)

int
main(int argc, char** argv)
{
	long double numbers[] = { ZERO, ONE, HALF, THIRD, FOURTH };	
	int i = 0;

	for ( ; i < 5; i++)
		printf("sin(%Lf) = %Lf\n", numbers[i], sinus(numbers[i]));
	
	printf("\n");
	i = 0;
	for ( ; i < 5; i++)
		printf("cos(%Lf) = %Lf\n", numbers[i], cosinus(numbers[i]));
	
	printf("\ncos(1.41421356) = %Lf\n", cosinus(1.41421356));
	printf("cos(1.57079633) = %Lf\n", cosinus(1.57079633));
	
	exit(EXIT_SUCCESS);
}
