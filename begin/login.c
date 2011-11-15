#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define ARRAYSIZE(x)	((sizeof(x)/sizeof(*x))-1)

struct user_s {
	char *name, *pass;
};

int
main(int argc, char **argv)
{
	char *name = (char*)malloc(BUFSIZ*sizeof(char));
	char *pass = (char*)malloc(BUFSIZ*sizeof(char));

	struct user_s users[] = {
		{ "Thomas", "acidophilus" },
		{ "Diana" , "semnificant" },
		{ "Morten", "monsoon" },
		{ 0, 0 }
	};

	printf("Please enter your username: ");

	scanf("%s", name);


/*	int c = getchar(), i = 0;
	for (;;) {
		c = getch();
		if (c == '\n' || c == EOF)
			break;
		*(pass + i++) = (char)c;
		putchar('\b');
		putchar('*');
	}
*/
	pass = getpass("Please enter your password: ");

	printf("Got password '%s'\n", pass);

	int i;
	for (i = 0 ; i < ARRAYSIZE(users); i++)
		if (!strcmp(users[i].name, name)) {
			if (!strcmp(users[i].pass, pass)) {
				printf("Successfully logged in as: %s\n", name);
				exit(0);
			}
			else {
				printf("Wrong password for user %s\n", name);
				exit(1);
			}
		}
	
	printf("Login failed. User %s not found.\n", name);
	exit(1);
}
