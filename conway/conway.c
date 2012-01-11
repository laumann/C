#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>

#define COLS	25
#define ROWS	80
#define TIMEOUT 1000

int nrows = ROWS;
int ncols = COLS;

int interval = TIMEOUT;

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
			sum = neighbor_sum(current,i,j);

			new[i][j] = (current[i][j]) ?
				((sum == 2 || sum == 3) ? 1 : 0) :
				((sum == 3) ? 1 : 0);
		}
	}
}

const char conway_usage[] = "Usage: ./conway [options]\n\n"
	" Conway's Game of Life.\n\n"
	"Common options:\n"
	" -h, --help              Print help information and exit.\n"
	" -t, --timeout <msecs>   Set the timeout interval between updates.\n"
	" -f, --file <file>       Set in input file.\n";

void
handle_cmd_args(int *argc, char ***argv)
{
	while (*argc > 0) {
		const char *cmd = (*argv)[0];
		
		if (!strcmp(cmd, "--help") || !strcmp(cmd, "-h")) {
			printf("%s", conway_usage);
			exit(0);
		}
		else if (!strcmp(cmd, "--timeout") || !strcmp(cmd, "-t")) {
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

void
updatescr(WINDOW *win, int **ary, int rows, int cols)
{
	int i,j;
	wclear(win);
	for (i=0; i < rows; i++)
		for (j=0; j < cols; j++)
			if (ary[i][j])
				mvwaddch(win, j, i, ACS_BOARD);
	wrefresh(win);
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
	/* ary0[1][1] = 1; */
	/* ary0[1][2] = 1; */
	/* ary0[2][1] = 1; */

	/* ary0[4][4] = 1; */
	/* ary0[3][4] = 1; */
	/* ary0[4][3] = 1; */

	ary0[39][15] = 1;
	ary0[40][15] = 1;
	ary0[41][15] = 1;
	ary0[39][16] = 1;
	ary0[39][17] = 1;
	ary0[41][16] = 1;
	ary0[41][17] = 1;

	int rmax, cmax;

	/* ncurses! */
	initscr();
	cbreak();
	timeout(interval);
	keypad(stdscr, TRUE);

	int **current, **next;
	int aoeu = 0;

	getmaxyx(stdscr, rmax, cmax);
	mvprintw(rmax-2, 0, "This screen has %d rows and %d columns.\n", rmax, cmax);
	getch();

	updatescr(stdscr, ary0, nrows, ncols);
	/* print_ary(ary0, nrows, ncols); */
	/* printf("\n"); */

	/* An infinite loop? I don't have time for that! */
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

		updatescr(stdscr, next, nrows, ncols);

		/* print_ary(next, nrows, ncols); */
		/* printf("\n"); */

		usleep(interval);
	}
	endwin();
	return 0;
}
