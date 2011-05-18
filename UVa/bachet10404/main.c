#include <stdio.h>
#include <stdlib.h>

/**
 * Bachet's game algorithm (UVa problem 10404)
 */
int
main(int argc, char **argv)
{
	long 	n;	/* number of stones */
	int 	m;	/* number of following arguments */
	int 	i,j,D;	/* iteration variables */

	int 	*opts,
		*game;

	while (fscanf(stdin, "%ld %d", &n, &m) != EOF) { 	/* Init */
		game = (int*)calloc(n, sizeof(int));
		opts = (int*)calloc(m, sizeof(int));

		for (i=0; i<m; i++) {
			D = fscanf(stdin, "%d", &opts[i]);
			game[opts[i]-1] = 1;
		}

		for (i=0; i<n; i++)				/* Process */
			for (j=0; j<m; j++) {
				if (game[i] || i-opts[j] < 0)	/* Already true, go on */
					continue;
				if (!game[i-opts[j]]) {		/* test */
					game[i] = 1;
					break;
				}
			}
		
		printf("%s\n", game[n-1] ? "Stan wins" : "Ollie wins");
		free(game);
		free(opts);
	}
	exit(0);
}
