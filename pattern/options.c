/*
* options() parses option letters and option arguments from the argv list.
* Succesive calls return succesive option letters which match one of
* those in the legal list. Option letters may require option arguments
* as indicated by a ':' following the letter in the legal list.
* for example, a legal list of "ab:c" implies that a, b and c are
* all valid options and that b takes an option argument. The option
* argument is passed back to the calling function in the value
* of the global OptArg pointer. The OptIndex gives the next string
* in the argv[] array that has not already been processed by options().
*
* options() returns -1 if there are no more option letters or if
* double SwitchChar is found. Double SwitchChar forces options()
* to finish processing options.
*
* options() returns '?' if an option not in the legal set is
* encountered or an option needing an argument is found without an
* argument following it.
*
*/
#include "options.h"

static const char sw_char = '-';
static const char unknown_opt = '?';

int OptIndex = 1;
char *OptArg = NULL;

int options(int argc, char** argv, const char *legal)
{
	static char *posn = "";
	char *legal_index = NULL;
	int letter = 0;

	if (!*posn) {
		if ((OptIndex >= argc)
		    || (*(posn = argv[OptIndex]) != sw_char)
		    || !*++posn)
				return -1;

		if (*posn == sw_char) {
			OptIndex++;
			return -1;
		}
	}

	letter = *posn++;

	if (!(legal_index = strchr(legal, letter))) {
		if (!*posn)
			OptIndex++;
		return unknown_opt;
	}

	if (*++legal_index != ':') {
		OptArg = NULL;
		if (!*posn)
			OptIndex++;
	}
	else {
		if (*posn)
			OptArg = posn;
		else
			if (argc <= ++OptIndex) {
				posn = "";
				return unknown_opt;
			}
			else
				OptArg = argv[OptIndex];
		posn = "";
		OptIndex++;
	}
	return letter;
}
