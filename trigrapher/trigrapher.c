#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *trigrapher_usage_string =
	"Usage: ./trigrapher [-h|--help] [-f|--file infile] [-o|--out outfile]\n"
	"\n"
	"  The file infile is expected to be a C source file, as will be the outfile, but it really\n"
	"  doesn't matter. The substitution happens on a character-for-character basis. If infile\n"
	"  is '-' then stdin is read.\n\n";
	

static FILE *in_fp, *out_fp;
#define INFILE	(1<<0)
#define OUTFILE	(1<<1)
/*
 * The Trigrapher program - take a C source file (.c) and output the same program,
 * substituting all trigraphs.
 * 
 * Here's the table:
 *   #	??=
 *   [	??(
 *   ]	??)
 *   {	??<
 *   }	??>
 *   \	??/
 *   |	??!
 *   ~	??-
 *   ^	??'
 *
 * All other characters shall remain untouched.
 */

void handle_options(int, char**);
int prefixcmp(const char*, const char*);

int
main(int argc, char** argv)
{
	if (argc == 1) {
		/* We try to read from stdin */
		int ch_in;
		while ( (ch_in = getchar()) != EOF) {
			switch(ch_in) {
			default: printf("%c", ch_in); break;
			case '#':  printf("??="); break;
			case '[':  printf("??("); break;
			case ']':  printf("??)"); break;
			case '{':  printf("??<"); break;
			case '}':  printf("??>"); break;
			case '\\': printf("??/"); break;
			case '|':  printf("??!"); break;
			case '~':  printf("??-"); break;
			case '^':  printf("??'"); break;
			}
		}
		exit(EXIT_SUCCESS);
	}

	handle_options(argc, argv);

	exit(0);
}

void
handle_options(int argc, char **argv)
{
	char **arg;
	argc--;
	for (; argc; argc--) {
		/* Is option? */
		arg = argv + argc;
		if (!prefixcmp(*arg, "-")) {
			arg++;
			if (!strcmp(*arg, "h") || !strcmp(*arg, "-help"))
				exit_with_help(0);
		}
	}
}

int
prefixcmp(const char *str, const char *prefix)
{
	for ( ; ; str++, prefix++)
		if (!*prefix)
			return 0;
		else if (*str != *prefix)
			return (unsigned char)*prefix - (unsigned char)*str;
}

void
exit_with_help(int status)
{
	fprintf(stdout, "%s", trigrapher_usage_string);
	exit(status);
}
