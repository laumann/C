#include <stdio.h>
#include <stdlib.h>

#define ARY_SIZ	10

struct wp_char {
	char wp_cval;
	short wp_font;
	short wp_psize;
} ar[ARY_SIZ];

void infun(struct wp_char *);

int
main(int argc, char** argv)
{
	struct wp_char wp_tmp, *hi_indx, *lo_indx, *in_p;

	for (in_p = ar; in_p < ar + ARY_SIZ; in_p++) {
		infun(in_p);
		if (in_p->wp_cval == '\n')
			break;
	}

	/* Exchange sort (sorting by pointers) */
	if (in_p - ar > 1)
	for (lo_indx = ar; lo_indx <= in_p-2; lo_indx++) {
		for (hi_indx = lo_indx+1; hi_indx <= in_p-1; hi_indx++) {
			if (lo_indx->wp_cval > hi_indx->wp_cval) {
				/* Swap! */
				wp_tmp = *lo_indx;
				*lo_indx = *hi_indx;
				*hi_indx = wp_tmp;
			}
		}
	}

	/* Print! */
	for (lo_indx = ar; lo_indx < in_p; lo_indx++) {
		printf("%c %d %d\n", lo_indx->wp_cval, lo_indx->wp_font, lo_indx->wp_psize);
	}
	exit(EXIT_SUCCESS);
}

void
infun(struct wp_char *in_p)
{
	in_p->wp_cval = getchar();
	in_p->wp_font = 2;
	in_p->wp_psize = 10;

	return;
}
