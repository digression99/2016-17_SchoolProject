//
// ���� �׽�Ʈ ���̽��� �����Ͽ� Ǯ���.
// �׸��� �װ��� �Ϲ�ȭ�Ѵ�.
//
//
#pragma warning(disable:4996)

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char findMajElmt(char *A, int p, int r);
int getCount(char * A, int p, int r, char c);
char getMajElmt(char * A, int p, int r);
char * getInput(int * size);

int main()
{
	char * A = NULL; int size = 0;
	char c = 0;

	A = getInput(&size);

	c = findMajElmt(A, 1, size);

	if (c == 0)
	{
		printf("No Majority Element\n");
	}
	else
	{
		printf("Majority Element : %c\n", c);
	}
	free(A);

	return 0;
}

char * getInput(int * size)
{
	int n = 0, i = 0;
	char * cp = NULL;
	scanf("%d", &n);
	
	cp = (char *)calloc(n, sizeof(char));

	for (i = 0; i < n; i++)
	{
		cp[i] = getchar();
	}
	*size = n;
	return cp;
}

char findMajElmt(char * A, int p, int r)
{
	int q = 0, cnt = 0;
	char lMaj = 0, rMaj = 0;

	if (p == r) return A[p - 1]; // �ʱ� dac

	q = (p + r) / 2;

	lMaj = findMajElmt(A, p, q);
	rMaj = findMajElmt(A, q + 1, r);

	if (lMaj == rMaj && lMaj != 0)
	{ // ���ٸ� �ٷ� ����
		return lMaj;
	}

	if (lMaj == 0 && rMaj == 0)
	{ 
		// major element �ĺ����� �ָ� �ø���?
		return getMajElmt(A, p, r);	
	}
	else if (lMaj == 0 && rMaj != 0)
	{
		if (getCount(A, p, r, rMaj) > (r - p) / 2 + 1) 
			return rMaj;
	}
	else if (rMaj == 0 && lMaj != 0)
	{
		if (getCount(A, p, r, lMaj) > (r - p) / 2 + 1) 
			return lMaj;
	}

	return 0;
}

int getCount(char * A, int p, int r, char c)
{
	int i, cnt = 0;

	for (i = p - 1; i < r; i++)
	{
		if (A[i] == c) cnt++;
	}
	return cnt;
}

char getMajElmt(char * A, int p, int r)
{ // �־��� ��Ȳ�� �� ���� �Լ�.
	int i, j, maxCount = 0, cnt = 0;
	char c = 0;

	for (i = p - 1; i < r; i++)
	{
		cnt = 0;
		for (j = i + 1; j < r; j++)
		{
			if (A[i] == A[j])
			{
				cnt++;
			}
		}
		if (maxCount < cnt)
		{
			maxCount = cnt;
			c = A[i];
		}
	}
	if (maxCount > (r - p) / 2 + 1)
	{
		return c;
	}
	return 0;
}