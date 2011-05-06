#include <stdio.h>
#include <stdlib.h>

/*
 Function pointers! - I have been waiting for these; example: pointer to function returning an int:

   int (*func)(int, float);

 Once you got the pointer, you can assign the address of the right sort of function just by using its
 name: like an array, a function name is turned into an address when it's used in an expression. You
 can call the function in one of two forms:

   (*func)(1,2)

 or

   func(1,2)
 
 If you like writing finite state machines (yeah!), you might like to know that you can have an array of pointers
 functions, with declaration and use like this:

   void (*fparr[])(int, float) = {
	// Initialisers in here
   };

 and usage like this:

   fparr[5](1, 3.4);
 
 *
 */

void func(int);		/* Function prototype (declaration) */

int
main(int argc, char *argv[])
{
	/* Function pointer declaration */
	void (*fp)(int);

	fp = func;

	(*fp)(1);
	fp(2);

	exit(EXIT_SUCCESS);
}

void
func(int arg)
{
	printf("%d\n", arg);
}
