#include <stdio.h>
#include <stdlib.h>

void get_numbers(char *, int *, int);
void skip_ahead_until_space(char **);

int
main(int argc, char **argv)
{
	long n;		/* number of stones */
	int m;		/* number of following arguments */
	int i;

	char 	buf[BUFSIZ];
	int 	opts[BUFSIZ],
		game[BUFSIZ];

	while(fgets(buf, sizeof(buf), stdin)) {
		printf("Input line: %s", buf);
		sscanf(buf, "%ld %d", &n, &m);

		/* Get the options */
		
		printf("n=%ld m=%d ", n, m);

		get_numbers(buf, opts, m);

		printf("opts=[ ");
		for (i=0 ; i<m ; i++)
			printf("%d ", opts[i]);
		printf("]\n");
	}

	/*
	 * Algorithm: Take 
	 */

	exit(0);
}

void
get_numbers(char *input, int *opts, int m)
{
	skip_ahead_until_space(&input);
	input++;
	skip_ahead_until_space(&input);
	input++;

/*	fprintf(stderr, "input: %s", input); */

	int i;
	for (i=0; i<m; i++) {
		sscanf(input, "%d", &opts[i]);
		input++;
		skip_ahead_until_space(&input);
/*		fprintf(stderr, "  %d: %s", i, input);*/
	}
}

void skip_ahead_until_space(char **buf)
{
	while (**buf != ' ')
		(*buf)++;
}
