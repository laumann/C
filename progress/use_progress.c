#include "progress.h"
#include <unistd.h>

#define TOTAL	300
#define DELAY	60

int
main(int argc, char** argv)
{
	struct progress *p = start_progress("Progress", TOTAL);
	int i = 0;

	while (i<TOTAL) {
		usleep(i*DELAY);
		display_progress(p, ++i);
	}
	
	stop_progress_msg(&p, "Done");

	exit(EXIT_SUCCESS);
}
