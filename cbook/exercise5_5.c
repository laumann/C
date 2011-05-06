#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* b(const char*, char);
char* c(const char*, const char*);

int
main(int argc, char *argv[])
{
	const char thomas[] 		= "Thomasomu";
	const char oma[]		= "oma";
	const char not_a_substr[]	= "foo";
	const char thomasine[]		= "Thomasine";	/* She is not a substring of Thomas */
	const char test_reset[]		= "omu";	/* Should find 'omu' (when 'om' has been eaten, should reset)*/

	char *cp;

	/* b function */
	cp = b(thomas, 'o');
	if (cp)
		printf("Found\n");
	else
		printf("Error finding 'o' in %s\n", thomas);

	/* c function (two tests) */
	cp = c(oma, thomas);
	if (cp) printf("'%s' found in '%s'\n", oma, thomas);
	else	printf("Error! Didn't find '%s' in '%s'\n", oma, thomas);

	cp = c(not_a_substr, thomas);
	if (cp) printf("Error! Should not have found '%s' in '%s'\n", not_a_substr, thomas);
	else	printf("'%s' correctly not found in '%s'\n", not_a_substr, thomas);

	cp = c(thomasine, thomas);
	if (cp) printf("Error! Should not have found '%s' in '%s'\n", thomasine, thomas);
	else	printf("'%s' correcly not found in '%s'\n", thomasine, thomas);

	cp = c(test_reset, thomas);
	if (cp) printf("Found '%s' in '%s'\n", test_reset, thomas);
	else	printf("Error! '%s' not found in '%s'\n", test_reset, thomas);

	exit(EXIT_SUCCESS);
}


/**
 * Finds the first occurence of a specific character in a given string. Returns a pointer
 * to the occurence in the string, or zero if it is not found.
 *
 * Traverses the string using a pointer (cp - char pointer)
 */
char* b(const char *str_p, char c)
{
	char *cp = (char*) str_p;
	for ( ; *cp; cp++) {
		printf("Looking at %c\n", *cp);
		if (*cp == c)
			return cp;
	}
	return NULL;	/* 0 */
}

/**
 * Take two strings as arguments. If the first exists in the second as a substring, return a pointer
 * to the first occurence, otherwise zero.
 */
char* c(const char *substr_p, const char *str_p)
{
	char *begin_p;
	char *c_substr_p = (char*)substr_p;
	char *c_str_p	 = (char*)str_p;
	
	/* Look for beginning match - save pointer in 'beginning of match' */
	while (*c_str_p) {
		printf("Current positions: %c, %c\n", *c_str_p, *c_substr_p);
		if (*c_substr_p == *c_str_p) {
			/* Save and increment */
			begin_p = c_str_p;
			c_substr_p++;
			c_str_p++;

			/* Begin matching */
			for ( ; *c_substr_p && *c_str_p; c_substr_p++, c_str_p++) {
				printf("  Current substring matching positions: %c, %c\n", *c_str_p, *c_substr_p);
				if (*c_substr_p != *c_str_p) break;
			}
			
			/* if substring has been eaten => Success! */
			if (!*c_substr_p)
				return begin_p;
			/* if string has been eaten => FAIL! */
			if (!*c_str_p) {
				return NULL;
			}
			/* else reset */
			c_str_p = begin_p;
			c_substr_p = (char*)substr_p;

		}
		/* Update */
		c_str_p++;
	}
	return NULL;	/* 0 */
}
