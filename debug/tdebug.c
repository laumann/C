#include "debug.h"

#include <sys/time.h>
#include <unistd.h>

int
main()
{
	struct timeval tv_init, tv_a, tv;
	gettimeofday(&tv_init, NULL);
	
	usleep(300);
	
	gettimeofday(&tv_a, NULL);

	timersub(&tv_a, &tv_init, &tv);
	LOG_INFO("(%lu.%06lu) It begins...",
	       tv.tv_sec,
	       tv.tv_usec);

	sleep(1);

	gettimeofday(&tv_a, NULL);
	timersub(&tv_a, &tv_init, &tv);
	LOG_WARN("(%lu.%06lu) More time has gone by",
		 tv.tv_sec,
		 tv.tv_usec);

	sleep(1);
	usleep(223456);

	gettimeofday(&tv_a, NULL);
	timersub(&tv_a, &tv_init, &tv);
	LOG_FATAL("(%lu.%06lu) About to show a message!",
		  tv.tv_sec,
		  tv.tv_usec);
	
	LOG("Testing");
	return 0;
}
