#include "debug.h"

/* Label of Graded Goods */
char *logg(char *msg, ...) {
	static char m[100];
	va_list ap;
	va_start(ap, msg);
	vsprintf(m, msg, ap);
	return m;
}
