#include "progress.h"
#include <unistd.h>
#include <string.h>

#define TOTAL	300
#define DELAY	200

/* Keep the configuration in a struct */
static struct {
	int delay;
	int total;
	char *msg;
} config = {
	/* Defaults */
	.delay = DELAY, 
	.total = TOTAL,
	.msg   = "Process"
};

int
parse_int_arg(const char *opt, const char *arg, int *target)
{
	int ok = sscanf(arg, "%d", target);
	if (!ok) {
		printf("Wrong format of argument to %s: %s\n", opt, arg);
		exit(EXIT_FAILURE);
	}
	return ok;
}

void
read_cmd_args(int nargs, char **argv)
{
	const char *arg;
	int i;


	for (i=0 ; i < nargs ; i++) {
		arg = argv[i];
		if (!strcmp(arg, "--delay") || !strcmp(arg, "-d")) {
			if (i+1 > nargs) {
				printf("Missing integer argument to %s.\n", arg);
				exit(EXIT_FAILURE);
			}
			parse_int_arg(arg, argv[++i], &config.delay);
		} else if (!strcmp(arg, "--total") || !strcmp(arg, "-t")) {
			if (i+1 > nargs) {
				printf("Missing integer argument to %s.\n", arg);
				exit(EXIT_FAILURE);
			}
			parse_int_arg(arg, argv[++i], &config.total);
		} else if (!strcmp(arg, "--message") || !strcmp(arg, "-m")) {
			if (i+1 > nargs) {
				printf("Missing string argument to %s.\n", arg);
				exit(EXIT_FAILURE);
			}
			config.msg = argv[++i]; /* No errors here */
		} else {
			if (arg[0] == '-')
				printf("Unrecognized option: %s\n", arg);
			else
				printf("Unrecognized argument: %s\n", arg);
		}
	}
}

int
main(int argc, char** argv)
{
	/* Command-line arguments */
	if (argc > 1)
		read_cmd_args(--argc, ++argv);

	struct progress *p = start_progress(config.msg, config.total);
	int i = 0;

	while (i < config.total) {
		usleep(i*config.delay);
		display_progress(p, ++i);
	}
	
	stop_progress_msg(&p, "Done");

	exit(EXIT_SUCCESS);
}
