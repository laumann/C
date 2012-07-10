#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
	char string[BUFSIZ];
	char *p;

	printf("Please enter a long string (max length: %d): ", sizeof(string));

	if (fgets(string, sizeof(string), stdin) != NULL) {
		printf("Thank you. You entered >%s<\n",string);

		if ((p = strchr(string, '\n')) != NULL)
			*p = '\0';
    
		printf("And now our string is >%s<\n", string);
	}

	exit(0);
}
