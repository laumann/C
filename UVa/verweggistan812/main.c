#include <stdio.h>
#include <stdlib.h>
/**
 * Observations: each pile can be viewed individually - meaning maximum can be found
 * on a pile-for-pile basis.
 * Maintain a hash of "number of pruls to get max profit"
 * 	Example: 1
 *		 6 12 3 10 7 16 5
 * Algorithm: For each pile create a "profit" table (10-value):
 *	[ -2 7 0 3 -6 5 ]
 * then add up
 *	[ -2 5 5 8 2 7 ],	whilst keeping track of max (=8)
 * then for all i where pile[i] = max, step thru hash, remove that key and add key+i+1 to hash.
 * 
 * if hash is empty, just add i+1	=> { 4 }
 *
 *
 * Another example:
 *	2
 *	5 7 3 11 9 10
 *	9 1 2 3 4 10 16 10 4 16
 *
 *	=> [ 3 7 -1 1 0]	(1)
 *	=> [ 3 10 9 10 10]	max = 10
 *	=> { 2 4 5 } U+ {}
 *	and 	totalMax += max (= 10)
 *
 *	=> [ 9 8 7 6 0 -6 0 6 -6 ]
 *	=> [ 9 17 24 30 30 24 24 30 24 ]	max = 30
 *	=> { 4 5 8 } U+ { 2 4 5 } = { 6 8 9 7 (9) 10 (10) 12 13 } = { 6 7 8 9 10 12 13 }
 *	and 	totalMax += max (= 40)
 *
 *	print totalMax and SORTED numbers in hash (all or the 10 first)
 *
 */

/* Use struct in which you can ALSO record the size... */
struct list {
	int size, *array;
};

int cmp(const void *a, const void *b)
{
	return *(int*)a-*(int*)b;
}

int
main(int argc, char **argv)
{
	int 	w, b, h, i, j, k, _,
		*pile,
		totalMax, max, maxCount;
	
	struct list *res;

	_ = scanf("%d\n", &w);
	for (;;) {
		totalMax = 0;
		res = (struct list*)malloc(sizeof(struct list));
		res->size = 0;
		res->array = NULL;

		for (i=0; i<w; i++) {			/* Get w lines */
			_ = scanf("%d", &b);		/* lines start with b */
			pile = (int*)calloc(b+1, sizeof(int));

			for (j=1; j<=b; j++) {		/* Get the rest of the numbers */
				_ = scanf(" %d", pile+j);
				*(pile+j) = 10 - *(pile+j);
			}
			max = maxCount = 0;
			for (j=1; j<=b; j++) {
				*(pile+j) = *(pile+j-1) + *(pile+j);
				if (max < *(pile+j)) {	/* New max found - set */
					max = *(pile+j);
					maxCount = 1;
				}
				else if (max == *(pile+j))
					maxCount++;
			}

/*			printf("max: %d, maxCount: %d, res->size: %d.\n", max, maxCount, res->size);*/
			if (res->size && maxCount) { /* Merge two lists */
				int *newArray = (int*)calloc(res->size*maxCount+2, sizeof(int));

				for (h=j=0; h<res->size; h++) {
					for (k=0; k<=b; k++)
						if (pile[k] == max) {
							int 	candidate = res->array[h] + k,
								s = 0,
								add = 1;
							for ( ; s<j; s++)
								if (newArray[s] == candidate) {
									add = 0;
									break;
								}
							if (add)	/* Accepted? */
								newArray[j++] = candidate;
						}
				}
				free(res->array);
				res->array = newArray;
				res->size = j;
			}
			else if (maxCount) { /* Anything to add (to empty list?) */
				int *newArray = (int*)calloc(maxCount+2, sizeof(int));
				for (k=j=0; k<=b; k++)
					if (*(pile+k) == max)
						*(newArray+ j++) = k;
				res->size = j;
				res->array = newArray;
			}
			else if (!max && !maxCount && !res->size) { /* Zero should be in the set... */
				res->array = (int*)calloc(2,sizeof(int));
				res->size = 1;
			}
			totalMax += max;
		}
		printf("Workyards %d\n", w);
		printf("Maximum profit is %d.\n", totalMax);
		printf("Number of pruls to buy:");
		
		/* Sort res and print all OR 10 smallest solutions */
		if (res->size > 1)
			qsort(res->array, res->size, sizeof(int), &cmp);
		
		int N = (res->size < 10) ? res->size : 10;
		for (k=0; k<N; k++)
			printf(" %d", *(res->array+k));
		printf("\n");

		free(pile);
		free(res->array);
		free(res);
		_ = scanf("%d\n", &w);

		/* Display a blank line between test cases. */
		if (w) printf("\n");
		else break;
	}
	exit(0);
}
