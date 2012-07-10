#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
	struct utsname name;

	if (uname(&name) == -1) {
		printf("Something went wrong");
		return -1;
	}

	printf("sysname:  %s\n", name.sysname);
	printf("nodename: %s\n", name.nodename);
	printf("release:  %s\n", name.release);
	printf("version:  %s\n", name.version);
	printf("machine:  %s\n", name.machine);

	/* free(name); */

	return 0;
}
