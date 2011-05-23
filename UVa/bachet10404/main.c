#include <stdio.h>
#include <stdlib.h>

/**
 * Bachet's game algorithm (UVa problem 10404)
 */
int
main(int argc, char **argv)
{
	long 	n,	/* number of stones */
		i;
	int 	m,	/* number of following arguments */
		_; 	/* ignored */

	int	*ms,	/* the m's (set of numbers allowable per game to remove) */
		*game,	/* the actual game */
		*k;	/* pointer to iterate through ms */

	while (fscanf(stdin, "%ld %d", &n, &m) != EOF) { 	/* Init */
		game 	= (int*)calloc(n+1, sizeof(int));
		ms 	= (int*)calloc(m+1, sizeof(int));

		for (i=0; i<m; i++)
			_ = scanf("%d", ms+i);

		*(game+1) = 1;
		*(ms+m) = 0;
		for (i=2; i<=n; i++)				/* Process */
			for (k = ms; *k ; k++)
				if (!(i-*k < 0) && !*(game+i-*k) && !*(game+i)) {
					*(game+i) = 1;
					break;
				}
		
		printf("%s wins\n", *(game+n) ? "Stan" : "Ollie");
		free(game);
		free(ms);
	}
	exit(0);
}
