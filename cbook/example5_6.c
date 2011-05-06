#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN	100

int
main(int argc, char** argv)
{
	char in_line[LINELEN], *cp;
	int c;

	cp = in_line;
	while ((c = getc(stdin)) != EOF) {
		if (cp == &in_line[LINELEN-1] || c == '\n') {
			/* Insert end of line marker */
			*cp = 0;
			if (strcmp(in_line, "stop") == 0)
				exit(EXIT_SUCCESS);
			else
				printf("line was %d characters long\n", (int)(cp-in_line));
			cp = in_line;
		}
		else {
			*cp++ = c;	/*Precedence => *cp++ == *(cp++)*/
		}
	}
	exit(EXIT_SUCCESS);
}
