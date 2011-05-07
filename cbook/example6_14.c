#include <stdio.h>
#include <stdlib.h>

#define NMONTHS	12

int month = 0;

short month_days[] = 
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

char *month_names[] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

int
main()
{
	int day_count = month;

	for ( ; day_count < NMONTHS; day_count++)
		printf("%d days in %s\n", month_days[day_count], month_names[day_count]);

	exit(EXIT_SUCCESS);
}
