#include <stdio.h>
#include <stdlib.h>

#include "printbits.h"

/**
 * This is a program to show how git commands give 'enum' commands
 * (and to see their values).
 */
#define RUN_SETUP		(1<<0)
#define RUN_SETUP_GENTLY	(1<<1)
#define USE_PAGER		(1<<2)

#define NEED_WORK_TREE		(1<<3)

int
main(int argc, char** argv)
{	
	printf("RUN_SETUP        = %08X\n", RUN_SETUP); 
	printf("RUN_SETUP_GENTLY = %08x\n", RUN_SETUP_GENTLY);
	printf("USE_PAGER        = %08x\n", USE_PAGER);
	printf("NEED_WORK_TREE   = %08x\n\n", NEED_WORK_TREE);

	printf("RUN_SETUP | NEED_WORK_TREE         = %08x\n", RUN_SETUP | NEED_WORK_TREE);
	printf("RUN_SETUP_GENTLY | NEED_WORK_TREE  = %08x\n", RUN_SETUP_GENTLY | NEED_WORK_TREE);
	
	printf("\nAnd now for the bit version!\n\n");

	printf("RUN_SETUP        = "); print_bits(RUN_SETUP); printf("\n"); 
	printf("RUN_SETUP_GENTLY = "); print_bits(RUN_SETUP_GENTLY); printf("\n"); 
	printf("USE_PAGER        = "); print_bits(USE_PAGER); printf("\n"); 
	printf("NEED_WORK_TREE   = "); print_bits(NEED_WORK_TREE); printf("\n"); 

	printf("\nRUN_SETUP | NEED_WORK_TREE         = "); print_bits(RUN_SETUP | NEED_WORK_TREE); printf("\n"); 
	printf("RUN_SETUP_GENTLY | NEED_WORK_TREE  = "); print_bits(RUN_SETUP_GENTLY | NEED_WORK_TREE); printf("\n"); 

	exit(EXIT_SUCCESS);
}
