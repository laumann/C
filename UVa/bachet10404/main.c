#include <stdio.h>
#include <stdlib.h>

void get_numbers(char *, int *, int);
void skip_ahead_until_space(char **);

/**
 * Bachet's game algorithm (UVa problem 10404)
 * TODO: Rewrite to dynamically allocate opts (using calloc)
 *       and get rid of get_numbers
 */

int
main(int argc, char **argv)
{
	long n;		/* number of stones */
	int m;		/* number of following arguments */
	int i,j;	/* iteration variables */

	char 	buf[BUFSIZ];
	int 	opts[BUFSIZ],
		*game;

	while(fgets(buf, sizeof(buf), stdin)) {
		sscanf(buf, "%ld %d", &n, &m);

		/* Get the options */
		get_numbers(buf, opts, m);

		/* init */
		game = (int*)calloc(n, sizeof(int));
		for (i=0; i<m; i++)
			game[opts[i]-1] = 1;
		/*
		 * At each cell, look at a[i-k] for k in opts. 
		 * game[i] = 1 <=> game[opts[0]] && ... && game[opts[m-1]] = 0
		 */
		for (i=0; i<n; i++) {
			for (j=0; j<m; j++) {
				if (game[i] || i-opts[j] < 0)	/* Already true, go on */
					continue;
				/* test */
				if (!game[i-opts[j]]) {
					game[i] = 1;
					break;
				}
			}
		}
		printf("%s\n", game[n-1] ? "Stan wins" : "Ollie wins");
		free(game);
	}
	exit(0);
}

void
get_numbers(char *input, int *opts, int m)
{
	skip_ahead_until_space(&input);
	input++;
	skip_ahead_until_space(&input);
	input++;

	int i;
	for (i=0; i<m; i++) {
		sscanf(input, "%d", &opts[i]);
		input++;
		skip_ahead_until_space(&input);
	}
}

void skip_ahead_until_space(char **buf)
{
	while (**buf != ' ')
		(*buf)++;
}
