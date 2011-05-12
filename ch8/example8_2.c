#include <stdio.h>

/*
 * Things with external linkage:
 *   accessible throughout the entire program!
 *
 * These are declarations, not definitions, so we assume the declaration is out
 * there somewhere.
 */
extern int important_variable;
extern int library_function(double, int);

/**
 * Definitions with external linkage.
 */
extern int ext_int_def = 0;	/* explicit def. */
extern int tentative_int_def;	/* tentative def. */

/*
 * Things with internal linkage:
 *   Only accessible within this file. The use of static, means
 *   that they are also tentative definitions
 */
#define INTERNAL_LINKAGE	static

INTERNAL_LINKAGE int less_important_variable;
INTERNAL_LINKAGE struct {
	int member_1;
	int member_2;
}local_struct;

/**
 * Also with internal linkage (static), but NOT a tentative definition
 * because this is a function.
 */
INTERNAL_LINKAGE void lf(void);

/**
 * Definition with internal linkage
 */
INTERNAL_LINKAGE float int_link_f_def	= 3.5;


/* Final section - definitions of functions in this file */

/**
 * Has external linkage => can be called from anywhere in this program
 */
void f1(int a){}

/**
 * The following two functions can only be invoked by name from within this
 * file.
 */
INTERNAL_LINKAGE
int local_function(int a1, int a2) {
	return a1*a2;
}

INTERNAL_LINKAGE
void lf(void) {
	/**
	 * Static (internal linkage) variable with no linkage =>
	 *   only usable within this function.
	 * 
	 * Is a definition (because of no linkage)
	 */
	INTERNAL_LINKAGE /* static */ int count;

	/**
	 * Automatic variable with no linkage, but an initializer.
	 */
	int i = 1;

	printf("lf called for time no %d\n", ++count);
}
