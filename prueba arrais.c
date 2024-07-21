#include <stdlib.h>
int main(void)
{
	int *pnt;
	int i = 0;
	pnt = (int *)malloc(sizeof(int) * 500);
	
	while (i < 500)
	{
		pnt[i] = i;
		i++;
	}

	return (0);
}