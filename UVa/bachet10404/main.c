#include <stdio.h>
#include <stdlib.h>

void get_numbers(char *, int *, int);
void skip_ahead_until_space(char **);

int
main(int argc, char **argv)
{
	long n;		/* number of stones */
	int m;		/* number of following arguments */
	int i,j;

	char 	buf[BUFSIZ];
	int 	opts[BUFSIZ],
		*game;

	while(fgets(buf, sizeof(buf), stdin)) {
		printf("Input line: %s", buf);
		sscanf(buf, "%ld %d", &n, &m);

		/* Get the options */
		
		printf("n=%ld m=%d ", n, m);

		get_numbers(buf, opts, m);

		/* Printing business - to be removed */
		printf("opts=[ ");
		for (i=0 ; i<m ; i++)
			printf("%d ", opts[i]);
		printf("]\n");

		/*
		 * Algorithm: Initialise game to 0 (false) and set
		 * the m start fields to true.
		 * 
		 * Then iterate game from 0..m-1 setting game[i] = 1
		 *   <=>
		 * game[opts[0]] && ... && game[opts[m-1]] = 0
		 */

		/* init */
		game = (int*)calloc(n, sizeof(int));
		for (i=0; i<m; i++)
			game[opts[i]-1] = 1;

		/*
		 * At each cell, look at a[i-k] for k in opts. 
		 */
		for (i=0; i<n; i++) {
			for (j=0; j<m; j++) {
				if (game[i])	/* Already true, go on */
					continue;
				/* Continue if current position isn't far enough ahead */
				if (i-(opts[j]-1) < 0)
					continue;
				/* TODO: Otherwise test */
			}
		}

		printf("\n");
		/* free */
		free(game);
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
