#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define ARRAYSIZE(x)	((sizeof(x)/sizeof(*x))-1)
#define NO_USER		(struct user_s){0,0}


struct user_s {
	char *name, *pass;
};

int
main(int argc, char **argv)
{
	char *name = (char*)malloc(BUFSIZ*sizeof(char));
	char *pass = (char*)malloc(BUFSIZ*sizeof(char));
	struct user_s user = NO_USER;

	/* Set up users */
	const struct user_s users[] = {
		{ "Thomas", "acidophilus" },
		{ "Diana" , "semnificant" },
		{ "Morten", "monsoon" },
		{ 0, 0 }
	};

	printf("Please enter your username: ");

	scanf("%s", name);

	/* Look for the user */
	int i;
	for (i = 0; i < ARRAYSIZE(users); i++) {
		if (!strcmp(users[i].name, name)) {
			user = users[i];
			goto getpass;
		}
	}
	goto wronguser;


getpass:
	pass = getpass("Please enter your password: ");

	printf("Got password '%s'\n", pass);
	if (!strcmp(user.pass, pass)) {
		printf("Successfully logged in as: %s\n", name);
		exit(0);
	} else {
		printf("Wrong password for user %s\n", name);
		exit(1);
	}

	/*
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
	*/

wronguser:
	printf("Login failed. User '%s' not found.\n", name);
	exit(1);

}
