#include "printbits.h"

void
print_bits(int number) {
        unsigned int mask = 0x10000000;

        while (mask) {
		printf("%d", (mask&number) ? 1 : 0);
                mask >>= 1;
        }
}
