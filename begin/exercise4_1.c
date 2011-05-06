#include <stdio.h>
#include <stdlib.h>

/* Function prototype */
int abs_val(int);

int
main(int argc, char** argv)
{
	int ch_in;
	printf("Please write a number: ");
	while ((scanf("%d", &ch_in)) != EOF) {
		printf("abs(%d) = %d\n",ch_in, abs_val(ch_in));
		printf("Please write a number: ");
	}
	exit(EXIT_SUCCESS);
}

int
abs_val(int a)
{
	return (a < 0) ? -a : a;
}
