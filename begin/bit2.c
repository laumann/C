#include <stdio.h>
#include <stdlib.h>
#include "printbits.h"

void newline(void);

/**
 * Version 2 of the 'bit' program - this time it actually prints the bit strings
 */
int
main(int argc, char** argv)
{
	int x,y;
	x = 0;
	y = ~0;
	printf("x = "); print_bits(x); newline();
	printf("y = "); print_bits(y); newline();
	

	while (x != y) {
		print_bits(x); printf("  & "); print_bits(0xff); printf(" = "); print_bits(x&0xff); newline();
		print_bits(x); printf("  | "); print_bits(0x10f); printf(" = "); print_bits((x&0x10f)); newline();
		print_bits(x); printf("  ^ "); print_bits(0xf00f); printf(" = "); print_bits(x&0xf00f); newline();
		print_bits(x); printf(" >> "); print_bits(2); printf(" = "); print_bits(x >> 2); newline();
		print_bits(x); printf(" << "); print_bits(2); printf(" = "); print_bits(x << 2); newline();

		x = (x << 1) | 1;

		printf("\nx = "); print_bits(x); newline();
	}
	exit(EXIT_SUCCESS);
}

void
newline(void)
{ printf("\n"); }
