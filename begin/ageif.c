#include <stdio.h>

int main()
{
	int age;
	int BARRIER = 100;

	printf("Please enter your age: ");
	scanf("%d", &age);

	if (age < BARRIER) {
		printf("You are pretty young!\n");
	} else if (age == BARRIER) {
		printf("You are old\n");
	} else {
		printf("You are REALLY old!\n");
	}
	return 0;
}
