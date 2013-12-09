#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(int argc, char* argv)
{
	int a = 10;
	int b = 20;
	printf("before swap, %d, %d\n", a, b);
	swap(&a, &b);
	printf("after swap, %d, %d\n", a, b);
}

void swap(int *a, int *b)
{
	if(*a == *b)
	{
		return;
	}
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
