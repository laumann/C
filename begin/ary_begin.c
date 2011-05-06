#include <stdio.h>
#include <stdlib.h>

#define ARY_SIZE 20

int
main(int argc, char** argv)
{
	int ch_array[ARY_SIZE];
	int c1, c2, stop = 0, lastchar = 0;
	
	/*
	 * Read characters into array.
	 * Stop if array full, or no more characters are available
	 */
	while (stop != 1) {
		ch_array[lastchar] = getchar();
		if(ch_array[lastchar] == '\n')
			stop = 1;
		else
			lastchar++;
		if (lastchar == ARY_SIZE)
			stop = 1;
	}
	--lastchar;

	/*
	 * Perform a bubble sort
	 */
	c1 = 0;
	while (c1 < lastchar) {
		c2 = c1+1;
		while (c2 <= lastchar) {
			if (ch_array[c2] < ch_array[c1]) {
				/* !Swap */
				int tmp = ch_array[c1];
				ch_array[c1] = ch_array[c2];
				ch_array[c2] = tmp;
			}
			++c2;
		}
		++c1;
	}
	
	printf("Array size: %d\n", lastchar+1);

	for (c1=0; c1 <= lastchar; ++c1) {
		printf("%c ", ch_array[c1]);
	}
	printf("\n");
	exit(EXIT_SUCCESS);
}
