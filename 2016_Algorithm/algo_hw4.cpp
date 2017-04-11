#include <stdio.h>
#include <math.h>

typedef struct _Point {
	int x, y;
}Point;

// 따로 기억해 놓아야 할 게 있을까?
// 가까운 두 점 -> 값을 굳이 리턴할 필요는 없다.
// 인덱스만 저장해 놓아도 된다.
// 가까운 두 점의 인덱스와 거리를 리턴한다?
// maximumSubarray 로직을 이용.

double getDistance(int x1, int y1, int x2, int y2);
double dacPointDistance(Point * A, int p, int r, int * p1, int * p2);
double dacCrossingDistance(Point * A, int p, int r, int q, int * idx1, int * idx2);
int tripleCompare(double d1, double d2, double d3);


int main()
{
	Point pArr[8];
	double dist = 0;
	int p1 = 0, p2 = 0;

	pArr[0].x = 0, pArr[0].y = 0;
	pArr[1].x = 5, pArr[1].y = 5;
	pArr[2].x = 10, pArr[2].y = 10;
	pArr[3].x = 15, pArr[3].y = 15;
	pArr[4].x = 16, pArr[4].y = 16;
	pArr[5].x = 25, pArr[5].y = 25;
	pArr[6].x = 30, pArr[6].y = 30;
	pArr[7].x = 35, pArr[7].y = 35;

	dist = dacPointDistance(pArr, 1, 8, &p1, &p2);

	printf("point 1 : %d, point 2 : %d, distance: %lf\n", p1, p2, dist);


	return 0;
}

double getDistance(int x1, int y1, int x2, int y2)
{
	return sqrt((double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double dacPointDistance(Point * A, int p, int r, int * p1, int * p2)
{
	double d1 = 999, d2 = 999, d3 = 999;
	int q = 0;
	int idx1 = 0, idx2 = 0, 
		idx3 = 0, idx4 = 0, 
		idx5 = 0, idx6 = 0;

	if (p == r)
	{
		*p1 = p;
		*p2 = p;
		return 999;
	}
	else
	{
		q = (p + r) / 2;

		d1 = dacPointDistance(A, p, q, &idx1, &idx2);
		d2 = dacPointDistance(A, q + 1, r, &idx3, &idx4);
		d3 = dacCrossingDistance(A, p, r, q, &idx5, &idx6);

		if (idx1 != idx2) // 처음이 아니라면
		{
			int n = tripleCompare(d1, d2, d3);

			switch (n)
			{
			case 1:
				*p1 = idx1;
				*p2 = idx2;
				printf("point 1 : %d, point 2 : %d, distance: %lf\n", *p1, *p2, d1);
				return d1;
			case 2:
				*p1 = idx3;
				*p2 = idx4;
				printf("point 1 : %d, point 2 : %d, distance: %lf\n", *p1, *p2, d2);
				return d2;
			case 3:
				*p1 = idx5;
				*p2 = idx6;
				printf("point 1 : %d, point 2 : %d, distance: %lf\n", *p1, *p2, d3);
				return d3;
			}
		}
		else
		{ // 점이 두개만 있는 배열일 때.
			d1 = getDistance(
				A[p - 1].x, A[p - 1].y, 
				A[r - 1].x, A[r - 1].y);
			*p1 = p;
			*p2 = r;
			printf("point 1 : %d, point 2 : %d, distance: %lf\n", p, r, d1);
			return d1;
		}
	}
}

double dacCrossingDistance(Point * A, int p, int r, int q, int * idx1, int * idx2)
{
	int i, j;
	double minDist = 999, dist = 0;

	for (i = q; i >= p; i--)
	{
		for (j = q + 1; j <= r; j++)
		{
			dist = getDistance(A[i - 1].x, A[i - 1].y, A[j - 1].x, A[j - 1].y);
			if (minDist > dist)
			{
				*idx1 = i;
				*idx2 = j;
				minDist = dist;
			}
		}
	}
	printf("point 1 : %d, point 2 : %d, MinDistance: %lf\n", *idx1, *idx2, minDist);
	return minDist;
}

int tripleCompare(double d1, double d2, double d3)
{
	if (d1 < d2)
	{
		if (d1 < d3)
		{
			return 1;
		}
	}
	else
	{
		if (d2 < d3)
		{
			return 2;
		}
	}
	return 3;
}