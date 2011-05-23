#include <stdio.h>
#include <stdlib.h>

#include "heapsort.h"
#include "heap.h"

#define MAX		6
#define ARRAYSIZE(x)	(sizeof(x)/sizeof(x[0]))

void print_array(int[], int);

int
main()
{	/* TEST MAIN FUNCTION - TODO: REMOVE! */
	int fig6_2[] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
	fprintf(stdout, "sizeof(fig6_2) = %d\n", sizeof(fig6_2)/sizeof(fig6_2[0]));

	int sz = ARRAYSIZE(fig6_2);
	print_array(fig6_2, sz);
	max_heapify(fig6_2, 1, sz);
	print_array(fig6_2, sz);


	int fig6_3[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	
	sz = ARRAYSIZE(fig6_3);
	print_array(fig6_3, sz);
	build_max_heap(fig6_3, sz);
	print_array(fig6_3, sz);

	heapsort(fig6_3, sz);
	print_array(fig6_3, sz);

	exit(0);
}

void
print_array(int *ints, int sz)
{
	printf("Size: %d [ ", sz);
	for (; sz ; ints++, sz--)
		printf("%d ", *ints);
	printf("]\n");
}

void
build_max_heap(int elms[], int sz)
{
	int i = ((sz>>1)-1);
	for ( ; i >= 0 ; i--)
		max_heapify(elms, i, sz);
}

/*
 * Modifies the array in place.
 */
void
max_heapify(int *elms, int i, int sz)
{
/*	fprintf(stdout, "max-heapify...A[%d]=%d, %d.\n", i, *(elms+i), sz);*/
	int 	l = LEFT(i),
		r = RIGHT(i),
		largest;

	if (l < sz && *(elms+l) > *(elms+i))
		largest = l;
	else
		largest = i;
	if (r < sz && *(elms+r) > *(elms+largest))
		largest = r;
	if (largest != i) {
/*		fprintf(stdout, "Swapping\tA[%d]=%d\tA[%d]=%d\n", i, *(elms+i), largest, *(elms+largest));*/
		int tmp = *(elms+i);
		*(elms+i) = *(elms+largest);
		*(elms+largest) = tmp;
/*		fprintf(stdout, "Swapped.\tA[%d]=%d\tA[%d]=%d\n", i, *(elms+i), largest, *(elms+largest));*/
		max_heapify(elms, largest,sz);
	}
}
