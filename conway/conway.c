#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define COLS	20
#define ROWS	10
#define INTERVAL 1000

int nrows = ROWS;
int ncols = COLS;

int interval = INTERVAL;

/**
 * Free an array
 */
#define free_ary(ary,rows)			\
	do {					\
		int i = 0;			\
		for ( ; i < rows; i++)		\
			free(ary[i]);		\
		free(ary);			\
	} while(0);

#define print_ary(ary,rows,cols)				\
	do {							\
		int i,j;					\
		for (i=0; i<rows; i++) {			\
			for (j=0; j<cols; j++)			\
				printf(" %d", ary[i][j]);	\
			printf("\n");				\
		}						\
	} while(0);

/** 
 * Allocate and return a pointer to a 2D array with dimensions specified by 
 * cols and rows - array is _not_ initialised.
 */
int **
alloc_ary(int rows, int cols)
{
	int i;
	int **array = calloc(rows, sizeof(int*));
	for (i=0; i<rows; i++)
		array[i] = calloc(cols, sizeof(int));
	
	return array;
}

/* List the eight neigbors 
 *   NW N NE    
 *   W  c  E    c = center 
 *   SW S SE
 *
 *   AL  A  AR  A = Above
 *   L   C  R   B = Below
 *   BL  B  BR  C = Center, L = Left, R = Right
 *    
 *   =>   which is x and which is y? 
 *
 *   (x-1,y-1) (x-1,y) (x-1, y+1)
 *   (x,  y-1) (x , y) (x,   y+1)
 *   (x+1,y-1) (x+1,y) (x+1, y+1)
 *   
 */
#define AL(ary,x,y) ((x>0 && y>0) ? ary[x-1][y-1] : 0)
#define A(ary,x,y) ((x>0) ? ary[x-1][y] : 0)
#define AR(ary,x,y) ((x>0 && y < ncols-1) ? ary[x-1][y+1] : 0)

#define L(ary,x,y) ((y>0) ? ary[x][y-1] : 0)
#define R(ary,x,y) ((y<ncols-1) ? ary[x][y+1] : 0)

#define BL(ary,x,y) ((x<nrows-1 && y>0) ? ary[x+1][y-1] : 0)
#define B(ary,x,y) ((x<nrows-1) ? ary[x+1][y] : 0)
#define BR(ary,x,y) ((x<nrows-1 && y<ncols-1) ? ary[x+1][y+1] : 0)

#define neighbor_sum(ary,x,y)			\
	AL(current,i,j)				\
	+ A(current,i,j)			\
	+ AR(current,i,j)			\
	+ L(current,i,j)			\
	+ R(current,i,j)			\
	+ BL(current,i,j)			\
	+ B(current,i,j)			\
	+ BR(current,i,j)			\

void
conway_timeslice(int **current, int **new, int rows, int cols)
{
	int i, j, sum;
	for (i=0; i<rows; i++) {
		for (j=0; j<cols; j++) {
			new[i][j] = current[i][j]; /* copy! */

			sum = neighbor_sum(current,i,j);

			/* Rule 1 + 3: He dies (under- and overpopulation) */
			if (current[i][j] && (sum < 2 || sum > 3))
				new[i][j] = 0;
			else if (sum == 3) /* dead */
				new[i][j] = 1;
		}
	}
}

const char conway_usage[] = "Usage: ./conway [options]\n\n"
	" Conway's Game of Life.\n\n"
	"Common options:\n"
	" -h, --help              Print help information and exit.\n"
	" -i, --interval <msecs>  Set the update interval.\n"
	" -f, --file <file>       Set in input file.\n";

void
handle_cmd_args(int *argc, const char ***argv)
{
	while (*argc > 0) {
		const char *cmd = (*argv)[0];
		
		if (!strcmp(cmd, "--help") || !strcmp(cmd, "-h")) {
			printf("%s", conway_usage);
			exit(0);
		}
		else if (!strcmp(cmd, "--interval") || !strcmp(cmd, "-i")) {
			if (*argc < 2) {
				fprintf(stderr, "--interval requires an integer argument\n");
				exit(EXIT_FAILURE);
			}

			(*argc)--;
			(*argv)++;
			
			if (sscanf((*argv)[0], "%d", &interval) == EOF) {
				fprintf(stderr, "Error scanning integer value");
				exit(EXIT_FAILURE);
			}
			
			printf("interval = %d\n", interval);
		}

		(*argc)--;
		(*argv)++;
	}
}

/**
 * Conway's Game of Life.
 */
int main(int argc, char *argv[])
{
	argc--;
	argv++;
	handle_cmd_args(&argc, &argv);

	int **ary0 = alloc_ary(nrows, ncols);
	int **ary1 = alloc_ary(nrows, ncols);

	/* Build the beacon (period 2) 
	 * 0 0 0 0 0
	 * 0 1 1 0 0
	 * 0 1 0 0 0 
	 * 0 0 0 0 1
	 * 0 0 0 1 1
	 */
	ary0[1][1] = 1;
	ary0[1][2] = 1;
	ary0[2][1] = 1;

	ary0[4][4] = 1;
	ary0[3][4] = 1;
	ary0[4][3] = 1;

	int **current, **next;
	int aoeu = 0;

	print_ary(ary0, nrows, ncols);
	printf("\n");

	/* Now - run forever! Infinite loop? I don't have time for that! */
	for (;;) {
		if (aoeu) {
			current = ary1;
			next = ary0;
		} else {
			current = ary0;
			next = ary1;
		}

		conway_timeslice(current, next, nrows, ncols);
		aoeu = (aoeu) ? 0 : 1;

		print_ary(next, nrows, ncols);
		printf("\n");

		usleep(interval);
	}
	return 0;
}
