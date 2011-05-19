#ifndef _HEAP_H
#define _HEAP_H

#include <stdio.h>
#include <stdlib.h>

/* -1 indicates we're at the root */
#define PARENT(i)	(((i+1)>>1)-1)
#define LEFT(i)		(((i+1)<<1)-1)
#define RIGHT(i)	((i+1)<<1)

void max_heapify(int[], int, int);
void build_max_heap(int[], int);
void heapsort(int[], int);

#endif
