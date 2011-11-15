/**
 * YAML 1.2 implementation in C
 *
 * author: Thomas Bracht Laumann Jespersen, <laumann.thomas@gmail.com>
 *
 * This will be an implementation of YAML 1.2 in C, following this specification
 *
 *   http://www.yaml.org/spec/1.2/spec.html
 *
 */

#include "yamlparser.h"
#include <stdarg.h>

/* Our working file */
static FILE	*yaml_stream;

/* Function prototypes */
static void	l_directive(FILE *);
static void	ns_yaml_directive(FILE *);
static void	ns_tag_directive(FILE *);
static void	s_separate_in_line(FILE *);

static void	l_comment(FILE *);

static void	c_named_tag_handle(char *);

/* Helpers */
static int	isbreak(int c);
static int	isword(const char*);
static int	prefixcmp(const char*, const char*);
static void	reset();

/* Error functions */
static void	error(const char*, ...);
static void	error_premature_eof(void);

/* Globally used variables */
int	YAML_DIRECTIVE_SPECIFIED;	/* We have by default not seen '%YAML X.Y' */

static struct {
	int major, minor;
} yaml_version;

void
parse_yaml_stream(FILE *stream)
{
	yaml_stream = stream;

	reset();

	/* GIANT opening switch */
	int c;
	while ((c = fgetc(yaml_stream)) != EOF) {
		switch (c) {

		case '%': /* [20] c-directive ::= "%" */
			printf("DIRECTIVE ");
			l_directive(yaml_stream);
			break;
		default:
			printf("%c", (char)c);
		}
	}
	printf("\nEnd of debugging output");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	printf("%%YAML %d.%d\n", yaml_version.major, yaml_version.minor);
	printf("---\n");
}

/*
  [82] l-directive ::=	'%'
			( ns-yaml-directive
			| ns-tag-directive
			| ns-reserved-directive )
			s-l-comments
 */
static void l_directive(FILE *s)
{
	char directive[BUFSIZ];

	/* Get directive */
	fscanf(s, "%s", directive);

	if (!strcmp(directive, "YAML"))
		ns_yaml_directive(s);
	else if (!strcmp(directive, "TAG"))
		ns_tag_directive(s);
	else
		; /* What else? */

	/* After parsing, should match newline... */
}

/*
  [78] l-comment	::= s-separate-in-line c-nb-comment-text? b-comment
 */
static void l_comment(FILE *s)
{
	s_separate_in_line(s);

	/* c-nb-comment-text?	::= '#' nb-char* */
	int c = fgetc(s);
	if (isbreak(c))
		return;
	
	if (c == '#') {
		while ((c = fgetc(s)) != EOF && !isbreak(c))
			; /* Eat comment */
	}
	else
		error("Error in comment, unmatched character: %c", (char)c);

	/* b-comment ::= b-break | EOF */
}

static int isbreak(int c)
{
	return c == '\n' || c == '\r';
}

/*
  [86] ns-yaml-directive ::=	"Y" "A" "M" "L"
  				s-separate-in-line ns-yaml-version
 */
static void ns_yaml_directive(FILE *s)
{
	printf("YAML ");

	/* Skip */
	s_separate_in_line(s);
	
	/* ns-yaml-version ::=	ns-dec-digit+ "." ns-dec-digit+ */
	int c = fgetc(s);

	/* major version number */
	if (isdigit(c)) {
		ungetc(c, s);
		fscanf(s, "%d", &yaml_version.major);
	}
	else
		error("(ns-yaml-directive), expected digit, got %c\n", (char)c);

	if ( (c = fgetc(s)) != '.')
		error("(ns-yaml-directive), expected '.', got %c\n", (char)c);
	
	/* minor version*/
	c = fgetc(s);
	if (isdigit(c)) {
		ungetc(c, s);
		fscanf(s, "%d", &yaml_version.minor);
	}
	else
		error("(ns-yaml-directive), expected digit, got %c.\n", (char)c);

	/* Checking */
	if (YAML_DIRECTIVE_SPECIFIED)
		error("The YAML directive must only be given at most once per document\n");
	
	if (yaml_version.major == 1) {
		if (yaml_version.minor > 2)
			fprintf(stderr, "WARNING:\nYAML minor version set higher than current standard: 1.%d. "
					"Will parse as version 1.2\n", yaml_version.minor);
		else if (yaml_version.minor <= 1)
			fprintf(stderr, "YAML 1.%d specified. Parsing as YAML 1.2 with appropriate compatibility warnings.\n",
				yaml_version.minor);
			/* Parse as YAML 1.2 and issue warnings at points of compatibility */
		else
			/* 1.2 - what? */
			;
	}
	else if (yaml_version.major > 1)
		error("YAML major version > 1 (%d.%d)\n", yaml_version.major, yaml_version.minor);

	/* Set globally that YAML directive has already been given */
	YAML_DIRECTIVE_SPECIFIED = 1;
}

static char *ns_char_plus(FILE *s)
{
	/* TODO: think, this probably doesn't work */
	char **str;
	int c = fgetc(s);

	if (!isgraph(c))
		error("Expected printable string.");

	ungetc(c, s);

	fscanf(s, "%as", str);
	return *str;
}

/*
  [88]	ns-tag-directive ::=	 “T” “A” “G”
				 s-separate-in-line c-tag-handle
				 s-separate-in-line ns-tag-prefix
 */
static void ns_tag_directive(FILE *s)
{
	printf("TAG ");
	char *tag = (char*)malloc(BUFSIZ*sizeof(char));

	s_separate_in_line(s);

	/* [89] c-tag-handle	::= c-named-tag-handle | c-secondary-tag-handle | c-primary-tag-handle */
	if (!fscanf(s, "%s", tag))
		error("Malformed stream (in TAG directive)\n");

	if (!*tag)
		error("Could not read tag\n");

	if (*tag == '!') {
		switch (*++tag) {
		case '\0':	fprintf(stderr, "Primary tag found\n"); break;
		case '!' :	fprintf(stderr, "Secondary tag found\n"); break;
		default  :	fprintf(stderr, "Named tag handle: !%s\n", tag);
				c_named_tag_handle(tag);
				printf("tag: %s\n", tag);
		}
		/* if tag =~ /!\w*!/ */
	}
	else
		error("Expected '!' - got %c", *tag);

	s_separate_in_line(s);

	/* [93] ns-tag-prefix ::=	c-ns-local-tag-prefix | ns-global-tag-prefix */
	
}

/*
  [92] c-named-tag-handle	::= "!" ns-word-char+ "!"
 */
static void c_named_tag_handle(char *tag)
{
	int len = strlen(tag);

	if (*(tag + len-1) != '!')
		error("In named tag handle: Not terminated with '!'\n");
	else
		*(tag+len-1) = '\0';

	if (!isword(tag)) 
		error("Tag named '%s' contains non-word characters\n", tag);

}

/*
 [38]	ns-word-char	::=	ns-dec-digit | ns-ascii-letter | “-”

 	Return non-zero if given argument conforms to ns-word-char+ (at least ONE 
 */
static int isword(const char *word)
{
	if (*word == '\0')
		return 0;
	for ( ; *word; word++)
		if (!isalnum(*word) && !*word == '-')
			return 0;
	return 1;	
}

/*
 * Display formatted error message and exit.
 */
static void error(const char *msg, ...)
{
	va_list ap;
	va_start(ap, msg);
	fprintf(stderr, "ERROR:\n");
	vfprintf(stderr, msg, ap);
	exit(1);
}

/*
  [66] s-separate-in-line :: 	| // start of line (empty)
  				s-white+
 */
static void s_separate_in_line(FILE *s)
{
	int c = fgetc(s), count = 1;
	if (c == EOF)
		error_premature_eof();
		
	if (isblank(c)) {
		while ((c = fgetc(s)) != EOF && isblank(c))
			count++;
		ungetc(c, s);	/* Put last character back into stream */
/*		fprintf(stderr, "Skipped %d blank%s.\n", count, (count == 1) ? "" : "s" );*/
	}
	else
		error("(s-separate-in-line), expected white space character - got %c", (char)c);
}

/*
 * prefixcmp assumes that the given prefix is shorter than the string.
 */
static int prefixcmp(const char *str, const char *prefix)
{
	for ( ; ; str++, prefix++)
		if (!*prefix)
			return 0;
		else if (*str != *prefix)
			return (unsigned char)*prefix - (unsigned char)*str;
}

/* Report the error "Premature End of File" and exit */
static void error_premature_eof()
{
	fprintf(stderr, "Error! Premature end-of-file. Exiting.\n");
	/* TODO: Cleanup! */
	exit(1);
}

void
parse_yaml_document(char *f)
{
	yaml_stream = fopen(f, "r");
	
	if (!yaml_stream)
		fprintf(stderr, "Unable to open document: %s\n", f);
}

/* Reset the global variables */
static void
reset()
{	
	YAML_DIRECTIVE_SPECIFIED= 0;
	yaml_version.major 	= 1;
	yaml_version.minor 	= 2;
}
