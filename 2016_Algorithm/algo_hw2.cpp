#include <stdio.h>
#include <time.h>

int matProduct(int (* C)[4], int (* A)[4], int (* B)[4], int row, int col);
void printMat(int (* C)[4], int r);
int getMatSum(int ** A, int ** B, int p, int r);
int matProduct2(int(*C)[4], int(*A)[4], int(*B)[4], int p, int r, int orSize, int nowSize);

int main()
{
	int n = 0;
	int A[4][4] =
	{ 1, 1, 1, 1,
	2, 2, 2, 2,
	3, 3, 3, 3,
	4, 4, 4, 4 },
		B[4][4] =
	{ 2, 2, 2, 2,
	3, 3, 3, 3,
	4, 4, 4, 4,
	5, 5, 5, 5 };
	int C[4][4] = { 0, };
	clock_t c1 = 0, c2 = 0;

	c1 = clock();

	for (int i = 0; i < 1000000; i++)
	{
		matProduct(C, A, B, 4, 4);
	}
	c2 = clock();
	printf("c1 : %d, c2 : %d, c2 - c1 : %d\n", c1, c2, c2 - c1);
	//printMat(C, 4);

	//printf("\n");
	c1 = clock();
	for (int i = 0; i < 1000000; i++)
	{
		matProduct2(C, A, B, 0, 0, 4, 4);
	}
	//printMat(C, 4);
	c2 = clock();
	printf("c1 : %d, c2 : %d, c2 - c1 : %d\n", c1, c2, c2 - c1);

	return 0;
}


int matProduct(int(*C)[4], int(*A)[4], int(*B)[4], int p, int r)
{ // naive algorithm
	int i, j, k;

	for (i = 0; i < p; i++)
	{
		for (j = 0; j < r; j++)
		{
			for (k = 0; k < p; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return 0;
}

int matProduct2(int(*C)[4], int(*A)[4], int(*B)[4], int p, int r, int orSize, int nowSize)
{
	int i;
	if (nowSize == 1)
	{
		for (i = 0; i < orSize; i++)
		{
			C[p][r] += A[p][i] * B[i][r];
		}
	}
	else
	{
		nowSize /= 2;
		
		matProduct2(C, A, B, p, r, orSize, nowSize);
		matProduct2(C, A, B, p + nowSize, r, orSize, nowSize);
		matProduct2(C, A, B, p, r + nowSize, orSize, nowSize);
		matProduct2(C, A, B, p + nowSize, r + nowSize, orSize, nowSize);
	}
	return 0;
}

void printMat(int (* C)[4], int r)
{
	int i, j;

	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			printf("C[%d][%d] = %d ", i, j, C[i][j]);
		}
		printf("\n");
	}
}