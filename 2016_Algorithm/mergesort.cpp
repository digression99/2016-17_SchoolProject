#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 정적 -> 동적으로 만들기.
void combine(int * A, int p, int q, int r);
int * mergeSort(int * A, int p, int r);
void printArray(int *A, int size);

int main()
{
	int A[8] = { 8, 7, 6, 5, 4, 3, 2, 1 }; // 원래 배열, worst-case
	mergeSort(A, 1, 8);
	printArray(A, 8);
	
	return 0;
}

void printArray(int * A, int size)
{
	int i = 0;

	for (i = 0; i < size; i++)
	{
		printf("A[%d] = %d\n", i, A[i]);
	}

	return;
}

void combine(int * A, int p, int q, int r)
{ // p, q, r은 배열 번호에 관계 없이 그 방의 번호로 줘야한다.
	int n1 = q - p + 1; // 4
	int n2 = r - q; // 4
	int * L = (int *)calloc(n1 + 1, sizeof(int)); // 5개의 방
	int * R = (int *)calloc(n2 + 1, sizeof(int)); // 5개의 방
	int i = 0;
	int j = 0;
	int k = 0;
	// 복사 후
	for (i = 0; i < n1; i++)
	{
		L[i] = A[p + i - 1]; // 0, 1, 2, 3
	}

	for (j = 0; j < n2; j++)
	{
		R[j] = A[q + j]; // 4, 5, 6, 7
	}

	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	i = 0; // 즉 첫 번째 원소부터
	j = 0;

	for (k = p - 1; k < r; k++)
	{ // 솔직히 여기가 소팅을 담당한다.
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}
	free(L);
	free(R);
}

int * mergeSort(int *A, int p, int r)
{
	int q = 0;
	if (p < r)
	{
		q = (p + r) / 2; //중간 -> 그냥 더해 나눔 -> 짝수든 홀수든 관계 x
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		combine(A, p, q, r);
	}
	else if (p == r)
	{
		// do nothing
	}
	return A;
}