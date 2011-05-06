#include <stdio.h>
#include <stdlib.h>
#define  INTSIZ  32

int
read_number(void)
{
	char number[INTSIZ];
	int i=0, ch;
	
	for(;;) {
		ch = getchar();
		if (ch >= '0' && ch <= '9') {
			number[i] = ch;
			++i;
		}
		else
			break;
		if (i+1==INTSIZ)
			break;
	}
	return atoi(number);
}

int
main(int argc, char** argv)
{
	printf("Read number: %d\n", read_number());
	exit(EXIT_SUCCESS);
}
