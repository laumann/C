#include "progress.h"
#include <unistd.h>
#include <string.h>

static char usage_string[] =
	"Usage: use_progress [options]...\n\n"
	"Options:\n"
	"  -t, --total <int>     The total progress.\n"
	"  -d, --delay <int>     The delay to add.\n"
	"  -m, --message <msg>   Set process message.\n"
	"  -h, --help            Print this help message and exit.\n";

/* Keep the configuration in a struct */
static struct {
	int delay;
	int total;
	char *msg;
} config = {
	/* Defaults */
	.delay = 150, 
	.total = 300,
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
		if (!strcmp(arg, "-d") || !strcmp(arg, "--delay")) {
			if (i+1 > nargs) {
				printf("Missing integer argument to %s.\n", arg);
				exit(EXIT_FAILURE);
			}
			parse_int_arg(arg, argv[++i], &config.delay);
		} else if (!strcmp(arg, "-t") || !strcmp(arg, "--total")) {
			if (i+1 > nargs) {
				printf("Missing integer argument to %s.\n", arg);
				exit(EXIT_FAILURE);
			}
			parse_int_arg(arg, argv[++i], &config.total);
		} else if (!strcmp(arg, "-m") || !strcmp(arg, "--message")) {
			if (i+1 > nargs) {
				printf("Missing string argument to %s.\n", arg);
				exit(EXIT_FAILURE);
			}
			config.msg = argv[++i]; /* No errors here */
		} else if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
			printf("%s", usage_string);
			exit(EXIT_SUCCESS);
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
