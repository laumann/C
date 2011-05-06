#include <stdio.h>
#include <stdlib.h>

void
recursive_print_100(void)
{
	static int v; /* = 0, static variable (visible throughout several calls */
	if (++v < 100)
		recursive_print_100();
	printf("%d ",v);
	v--;
}

int
main(int argc, char** argv)
{
	recursive_print_100();
	exit(EXIT_SUCCESS);
}
