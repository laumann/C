#include "exercise4_2.h"

/**
 * Test output (exercise4_2.c). In the same file as 'output' are two functions called
 * 'current_{line,column}', that returns the appropriate value. The actual values of
 * the current line and current column is only accesible in 'exercise4_2.c'
 */
int
main(int argc, char** argv)
{
	char* name = "Thomas\nBracht\nLaumann\nJespersen\n";

	for ( ; *name; name++) {
		output(*name);
		printf("\t%d,-%d\n", current_line(), current_column());
	}

	/* printf("\nGotcha! %d,-%d\n", line, column); */

	exit(EXIT_SUCCESS);
}
