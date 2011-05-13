#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "options.h"

#define CFLAG	(1<<0)	/* Only count the number of matching lines */
#define IFLAG	(1<<1)	/* Ignore case of letters */
#define LFLAG	(1<<2)	/* Show line numbers */
#define NFLAG	(1<<3)	/* Show input file names */
#define VFLAG	(1<<4)	/* Show lines which do NOT match */

extern int OptIndex;	/* Current index into argv[] */
extern char *OptArg;	/* Global option argument pointer */

/* fetch cmd line arguments from main() */
int options(int, char **, const char *);

/* record the required options ready to control program behaviour */
unsigned set_flags(int, char **, const char *);

/* check each line of the input file for a match */
int look_in(const char *, const char *, unsigned);

void print_line(unsigned mask, const char *fname, int lnno, const char *text);

static const char
	*OptString 	= "cilnv",
	*errmsg		= "Usage: pattern [-cilnv] word [filename]\n";

int
main(int argc, char *argv[])
{
	unsigned flags 	= 0;
	int success	= 0;
	char* search_string;

	if (argc < 2) {
		fprintf(stderr, "%s", errmsg);
		exit(1);
	}

	flags = set_flags(argc, argv, OptString);

	if (argv[OptIndex])
		search_string = argv[OptIndex++];
	else {
		fprintf(stderr, "%s", errmsg);
		exit(1);
	}

	if (flags & IFLAG) {
		char *p;
		for (p = search_string; *p; p++)
			if (isupper(*p))
				*p = tolower(*p);
	}

	if (!argv[OptIndex])
		success = look_in(NULL, search_string, flags);
	else
		while (argv[OptIndex])
			success += look_in(argv[OptIndex++], search_string, flags);

	if (flags & CFLAG)
		printf("%d\n", success);
	
	exit(success ? 0 : 1);
}

unsigned 
set_flags(int argc, char **argv, const char *opts)
{
	unsigned flags	= 0;
	int ch		= 0;

	while ((ch = options(argc, argv, opts)) != -1) {
		switch (ch) {
		case 'c':
			flags |= CFLAG;
			break;
		case 'i':
			flags |= IFLAG;
			break;
		case 'l':
			flags |= LFLAG;
			break;
		case 'n':
			flags |= NFLAG;
			break;
		case 'v':
			flags |= VFLAG;
			break;
		case 'h':
			fprintf(stderr, "%s", errmsg);
			exit(1);
		}
	}
	return flags;
}

int
look_in(const char *infile, const char *pat, unsigned flags)
{
	FILE *in;
	char line[2][BUFSIZ];	/* line[0] stores input line, line[1] converted to lower-case if necessary */
	int 	lineno 	= 0,
		matches = 0;
	
	if (infile) {
		if (!(in = fopen(infile, "r"))) {
			perror("pattern");
			return 0;
		}
	}
	else
		in = stdin;
	
	while (fgets(line[0], BUFSIZ, in)) {
		char *line_to_use = line[0];
		lineno++;
		if (flags & IFLAG) {
			char *p;
			strcpy(line[1], line[0]);
			for (p=line[1]; *p; p++)
				if (isupper(*p))
					*p = tolower(*p);
			line_to_use = line[1];
		}

		if (strstr(line_to_use, pat)) {
			matches++;
			if (!(flags & VFLAG))
				print_line(flags, infile, lineno, line[0]);

		} else if (flags & VFLAG)
			print_line(flags, infile, lineno, line[0]);
	}
	fclose(in);
	return matches;
}

void
print_line(unsigned mask, const char *fname, int lnno, const char *text)
{
	if (mask & CFLAG)
		return;
	if (mask & NFLAG)
		printf("%s: ", (fname && *fname) ? fname : "stdin");
	if (mask & LFLAG)
		printf("%4d:\t", lnno);
	printf("%s", text);
}
