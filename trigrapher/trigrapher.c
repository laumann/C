#include <stdio.h>
#include <stdlib.h>
/*
 * The Trigrapher program - take a C source file (.c) and output the same program,
 * substituting all trigraphs.
 * 
 * Here's the table:
 *   #	??=
 *   [	??(
 *   ]	??)
 *   {	??<
 *   }	??>
 *   \	??/
 *   |	??!
 *   ~	??-
 *   ^	??'
 *
 * All other characters shall remain untouched.
 */

int
main(int argc, char** argv)
{
	if (argc == 1) {
		/* We try to read from stdin */
		int ch_in;
		while ( (ch_in = getchar()) != EOF) {
			switch(ch_in) {
			default: printf("%c", ch_in); break;
			case '#': printf("??="); break;
			case '[': printf("??("); break;
			case ']': printf("??)"); break;
			case '{': printf("??<"); break;
			case '}': printf("??>"); break;
			case '\\': printf("??/"); break;
			case '|': printf("??!"); break;
			case '~': printf("??-"); break;
			case '^': printf("??'"); break;
			}
		}
	}
	else {
		/* Get name of file to convert */
	}
	exit(EXIT_SUCCESS);
}
