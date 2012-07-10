#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int a;
	int b;
	int c;
} x;

void struct_f(x);
void struct_pointer_f(x*);
void print_function(const char *, const char *, int);

int
main(int argc, char **argv)
{
	x z;

	z.a = 10;
	z.a *= 4;
	z.a++;

	struct_f(z);
	print_function("main", "z.a", z.a);

	struct_pointer_f(&z);
	print_function("main", "z.a", z.a);

	exit(0);
}

void
struct_f(x z)
{
	print_function("struct_f", "z.a", ++z.a);
}

void
struct_pointer_f(x *zp)
{
	print_function("struct_pointer_f", "(*zp).a", ++(*zp).a);
}

void
print_function(const char *fname, const char *name, int value)
{
	printf("%-16s: %8s = %d\n", fname, name, value);
}
