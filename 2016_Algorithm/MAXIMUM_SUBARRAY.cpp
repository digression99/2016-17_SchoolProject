//
// 매일 얼마가 변하는 지를 본다.
// max_subarray of a[1...16] ->a[8..11], sum is 43
//
//
//
//
//
//
//

struct ArrStruct
{
	int A[12] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5 };
	int left = 0;
	int right = 11;
	int mid = (left + right) / 2;
	int sum = 0;
};

typedef struct ArrStruct ArrStruct;


//int findMaxCrossingSubarray(int * A, int low, int mid, int high);
//int findMaximumSubarray(int * A, int low, int high);

ArrStruct * findMaxCrossingSubarray(ArrStruct * as);
ArrStruct * findMaximumSubarray(ArrStruct * as);


#include <stdio.h>

int main()
{
	ArrStruct as;




	return 0;
}

ArrStruct * findMaxCrossingSubarray(ArrStruct * as)
{
	int leftSum = -9999, rightSum = -9999;
	int i, j;
	int maxLeft, maxRight;
	int sum = 0;

	for (i = as->mid; i > as->left; i--)
	{
		sum += as->A[i];
		if (sum > leftSum)
		{
			leftSum = sum;
			maxLeft = i;
		}
	}
	sum = 0;

	for (j = as->mid + 1; j < as->right; j++)
	{
		sum += as->A[j];
		if (sum > rightSum)
		{
			rightSum = sum;
			maxRight = j;
		}
	}
	as->left = maxLeft;
	as->right = maxRight;
	as->sum = leftSum + rightSum;
	
	return as;
}

ArrStruct * findMaximumSubarray(ArrStruct * as)
{
	ArrStruct leftStruct, rightStruct, crossStruct;

	if (as->left == as->right)
	{
		as->sum = as->A[as->left];
		return as;
	}
	else
	{
		//as->mid = (as->left + as->right) / 2;
		as->right = as->mid;

		leftStruct = *findMaximumSubarray(as);



		rightStruct = *findMaximumSubarray(as);

		// 이렇게 right, cross도.
	}
}

int findMaxCrossingSubarray(int * A, int low, int mid, int high)
{ // divide&conquer로 일반적으로 찾는다.
	int leftSum = -999, rightSum = -999;
	int sum = 0;
	int i, j;
	int maxLeft, maxRight;

	for (i = mid; i > low; i--)
	{
		sum = sum + A[i];
		if (sum > leftSum)
		{
			leftSum = sum;
			maxLeft = i;
		}
	}

	sum = 0;

	for (j = mid + 1; j < high; j++)
	{
		sum = sum + A[j];
		if (sum > rightSum)
		{
			rightSum = sum;
			maxRight = j;
		}
	}

	return 1;
	//return maxLeft, maxRight, leftSum + rightSum; 
}

int findMaximumSubarray(int * A, int low, int high)
{
	int mid;
	int leftHigh, leftLow, leftSum,
		rightHigh, rightLow, rightSum,
		crossHigh, crossLow, crossSum;

	if (high == low)
	{
		//return low, high, A[low];
		return 1;
	}
	else
	{
		mid = (low + high) / 2;

		//leftHigh, leftLow, leftSum = findMaximumSubarray(A, low, mid); // 왼쪽
		//rightHigh, rightLow, rightSUm = findMaximumSubarray(A, mid + 1, high); // 오른쪽
		//crossLow, crossHigh, crossSum = findMaxCrossingSubarray(A, low, mid, high); // 중간을 지난다.

		if (leftSum >= rightSum && leftSum >= crossSum)
		{
			//return leftLow, leftHigh, leftSum;
			return 1;
		}
		else if (rightSum >= leftSum && rightSum >= crossSum)
		{
			// return rightLow, rightHigh, rightSum;
			return 1;
		}
		else
		{
			// return crossLow, crossHigh, crossSum;
			return 1;
		}
	}
}