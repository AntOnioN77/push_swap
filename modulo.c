#include <stdio.h>
int main(void)
{
	int index = 1;
	int slots = 5;
	index = (index + slots) % slots;
	printf("%d\n", index);
}
