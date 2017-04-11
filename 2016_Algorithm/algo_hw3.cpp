#include <stdio.h>

void findMaxMin(int * A, int * max, int * min, int p, int r);

int main()
{
	int A[8] = { 6, 4, 3, 2, 1, 7, 8, 5 };
	int max = 0, min = 0;

	findMaxMin(A, &max, &min, 1, 8);

	printf("max : %d, min : %d\n", max, min);

	return 0;
}

void findMaxMin(int * A, int * max, int * min, int p, int r)
{
	int q = 0;
	int mx1 = 0, mx2 = 0, mn1 = 0, mn2 = 0;
	//int temp;

	if (p != r)
	{
		q = (p + r) / 2;
		findMaxMin(A, &mx1, &mn1, p, q);
		findMaxMin(A, &mx2, &mn2, q + 1, r);

		*max = (mx1 >= mx2) ? mx1 : mx2;
		*min = (mn1 <= mn2) ? mn1 : mn2;
	}
	else
	{
		*max = *min = A[p - 1];
	}
	return;
}

