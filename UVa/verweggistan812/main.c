#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	/* Input format:
	 * w
	 * b n1 n2 .. nb (w lines of this format)
	 * input ends on w=0
	 */
	int w, b, i, j, D, *pile;

	D = scanf("%d\n", &w);
	for (;;) {
		for (i=0; i<w; i++) {			/* Get w lines */
			D = scanf("%d", &b);		/* lines start with b */
			pile = (int*)calloc(b, sizeof(int));
			for (j=0; j<b; j++)		/* Get the rest of the numbers */
				D = scanf(" %d", &pile[j]);
		}
		printf("Workyards %d\n", w);

		/**
		 * TODO: process
		 * For each test case, print the case number (1, 2, ...). Then print two
		 * lines, the first containing the maximum profit the merchant can achieve.
		 * The second line should specify the number of pruls the merchant has to buy
		 * to obtain this profit. If this number is not uniquely determined, print
		 * the possible values in increasing order. If there are more than ten
		 * possible values, print only the 10 smallest.
		 */

		printf("Maximum profit is #.\n");
		printf("Number of pruls to buy: # # #\n");

	/*	printf("[");
		for (i=0; i<b; i++)
			printf(" %d", pile[i]);
		printf(" ]\n\n");	*/

		free(pile);
		D = scanf("%d\n", &w);

		/* Display a blank line between test cases. */
		if (w) printf("\n");
		else break;
	}
	exit(0);
}
