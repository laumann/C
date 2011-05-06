#include "exercise4_2.h"

/*
 * Takes a single character argument, and sends it to the program output with putchar
 *
 * It remembers the current line, and current column.
 *
 * The only values passed to this function are: 
 *
 *  - alphanumeric	(output and increment current column)
 *  - punctuation	(output and increment current column)
 *  - space		(output and increment current column)
 *  - newline		(output, increment current line and reset current column)
 */


/* These values are initialised once (to zero) and only accessible within this file */
static int line;
static int column;

void
output(char c)
{
	if (c == '\n') {
		line++;
		column = 0;
	}
	else {
		column++;
	}
	putchar(c);
}

int
current_line(void)
{
	return line;
}

int
current_column(void)
{
	return column;
}
