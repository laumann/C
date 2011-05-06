#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char** argv)
{
	int x,y;
	x = 0;
	y = ~0;

	while (x != y) {
		printf("%8x & %4x = %8x\n", x, 0xff,   x & 0xff);
		printf("%8x | %4x = %8x\n", x, 0x10f,  x | 0x10f);
		printf("%8x ^ %4x = %8x\n", x, 0xf00f, x ^ 0xf00f);
		printf("%8x >> 2   = %8x\n", x, x >> 2);
		printf("%8x << 2   = %8x\n", x, x << 2);
		x = (x << 1) | 1;
		printf("x = %8x\n", x);
	}
	exit(EXIT_SUCCESS);
}
