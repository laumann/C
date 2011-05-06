#ifndef _EXERCISE_4_2_H
#define _EXERCISE_4_2_H

#include <stdio.h>
#include <stdlib.h>

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

void output(char);
int current_line(void);
int current_column(void);

#endif
