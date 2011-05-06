#include <stdio.h>
#include <stdlib.h>

#define GROW_BY	10

int
main(int argc, char** argv)
{
    char *str_p, *next_p, *tmp_p;
    int ch, need, chars_read;
  
    if ((str_p = (char *)malloc(GROW_BY)) == NULL) {
	fprintf(stderr, "No initial store\n");
	exit(EXIT_FAILURE);
    }

    next_p = str_p;
    chars_read = 0;

    while ((ch = getchar()) != EOF) {
	/*
	  | Completely restart at each new line.
	*/
	if (ch == '\n') {
	    *next_p = 0;
	    printf("%s\n", str_p);
	    free(str_p);
	    chars_read = 0;
	    if ((str_p = (char *)malloc(GROW_BY)) == NULL) {
		fprintf(stderr, "No initial store\n");
		exit(EXIT_FAILURE);
	    }
	    next_p = str_p;
	    continue;
	}
	
	/*
	 * Have we reached the end of the current allocation?
	 */
	if (chars_read == GROW_BY-1) {
	    *next_p = 0;	/* Mark end of string */
	    /*
	     * Use pointer subtraction to find
	     * the length of the current string
	     */
	    need = next_p - str_p + 1;
	    tmp_p = (char *)malloc(need+GROW_BY);
	    if (tmp_p == NULL) {
		fprintf(stderr, "No more store\n");
		exit(EXIT_FAILURE);
	    }
	    /* Copy */
	    strcpy(tmp_p, str_p);
	    free(str_p);
	    str_p = tmp_p;
      
	    /* Reset next_p and character count */
	    next_p = str_p + need - 1;
	    chars_read = 0;
	}
	*next_p++ = ch;	/* Put character at end of current string */
	chars_read++;
    }
    /**
     * EOF - but do unprinted characters exist?
     */
    if (str_p - next_p) {
	*next_p = 0;
	fprintf(stderr, "Incomplete last line\n");
	printf("%s\n", str_p);
    }
    exit(EXIT_SUCCESS);
}
