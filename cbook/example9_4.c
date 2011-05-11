#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

FILE *tmp_file;
void leave(int sig);
char buf[BUFSIZ];

int
main()
{
	(void) signal(SIGINT, leave);

	tmp_file = fopen("log.txt", "w");
	
	for (;;) {
		/*
		 * Print prompt (>>), get input line and output to tmp_file
		 */
		printf(">> ");
		fgets(buf, BUFSIZ, stdin);
		fprintf(tmp_file, "%s", buf);
	}
	exit(EXIT_SUCCESS);
}

void
leave(int sig)
{
	fprintf(stdout, "\nExiting.\n");
	fprintf(tmp_file, "Interrupted...\n");
	fclose(tmp_file);
	exit(sig);
}
