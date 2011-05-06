#include <stdio.h>
#include <stdlib.h>

#define SIZE	8
#define A	65

int
main(int argc, char** argv)
{
	/*int board[SIZE][SIZE]; Unused!*/
	int i,j;

	for (i=1; i<=SIZE; i++) {
		for (j=0; j<SIZE; j++) {
			printf("[%d%c]", i, (A+j) );
		}
		printf("\n");
	}
}
