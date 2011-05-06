#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING	50
#define MAXLEN		80

void print_ary(const char **p_array);
void sort_ary(const char **p_array);
char *next_string(void);

int
main(int argc, char** argv)
{
	char **p_array;
	int nstrings;	/* Number of strings read */

	p_array = (char **)malloc(sizeof(char *[MAXSTRING+1]));

	if (!p_array) {
		printf("Out of memory!\n");
		exit(EXIT_FAILURE);
	}

	nstrings = 0;
	while (nstrings < MAXSTRING &&
			(*(p_array + nstrings) = next_string()) != 0)
		nstrings++;

	*(p_array + nstrings) = 0;	/* == p_array[nstrings] = 0*/

	sort_ary(p_array);
	print_ary(p_array);

	exit(EXIT_SUCCESS);
}

void print_ary(const char **p_array) {
	while (*p_array)
		printf("%s\n", *p_array++);
}

void sort_ary(const char **p_array) {
	const char **lo_p, **hi_p, *tmp;

	for (lo_p = p_array; *lo_p != 0 && *(lo_p+1) != 0; lo_p++) {
		for (hi_p = lo_p+1; *hi_p != 0; hi_p++) {
			if (strcmp(*hi_p, *lo_p) >= 0)
				continue;
			tmp = *hi_p;
			*hi_p = *lo_p;
			*lo_p = tmp;
		}
	}
}

char *next_string(void) {
	char *cp, *dest;
	int c;

	dest = (char *)malloc(MAXLEN);
	if (dest) {
		cp = dest;
		while ((c = getchar()) != '\n' && c != EOF) {
			if (cp-dest < MAXLEN-1)
				*cp++ = c;
		}
		*cp = 0;
		if (c == EOF && cp == dest)
			return 0;
	}
	return dest;
}
