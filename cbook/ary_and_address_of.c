#include <stdio.h>
#include <stdlib.h>

/*
 Case: when an array name is the operand of the '&' address-of operator. Here,
 it is converted into the address of the whole array.

 What's the difference?

 They have different types. For an array of n elements of type T, then the address
 of the first element has type 'pointer to T'; the address of the whole array has
 type 'pointer to array of n elements of type T'; clearly very different.

 Below example:

 ip:	pointer to int

 ar10i:	pointer to array of 10 ints
 */

int
main(int argc, char** argv)
{
	int ar[10],
	    *ip,
	    (*ar10i)[10];	/* Pointer to array of 10 ints */
	
	ip = ar;		/* Address of first element */
	ip = &ar[0];		/* Address of first element */

	ar10i = &ar		/* Address of the whole array */
}
