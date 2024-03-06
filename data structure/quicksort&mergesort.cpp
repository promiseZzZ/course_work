#include<iostream>
using namespace std;
void swap(int A[], int a, int b)
{
	int temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}
int findpivot(int A[], int c, int d)//避免把所有的结点划分到一边，选取数组中间点的方法
{
	return (c + d) / 2;
}
int partition(int A[], int l, int r, int& pivot)
{
	while (l < r)
	{
		while ((A[l] <= A[pivot])&&(l<r))//左边找大
		{
			l++;
		}
		while ((A[r] >= A[pivot])&&(l<r))//右边找小
		{
			r--;
		}
		swap(A, l, r);
	}
	return l;
}
void QuickSort(int A[], int begin, int end)
{
	if (end<=begin)//0个或者1个元素的情况不用排序
	{
		return;
	}
	int pivotindex = findpivot(A, begin, end);
	swap(A,pivotindex,end);
	int k = partition(A, begin, end, end);
	swap(A, k,end);
	//[begin:k-1]k[k+1:end]
	QuickSort(A, begin, k - 1);
	QuickSort(A, k + 1, end);
}
void MergeSort(int A[], int temp[], int start, int end)
{
	//将数组一直不断地分为两半，直到子数组的长度为1
	if (start==end)
	{
		return;
	}
	int mid = (start + end) / 2;
	MergeSort(A, temp, start, mid);
	MergeSort(A, temp, mid + 1, end);
	//归并操作
	for (int i = start; i <= end; i++)
	{
		temp[i] = A[i];
	}
	int i1 = start;  int i2 = mid + 1;
	for (int  curr = start; curr <= end; curr++)
	{
		if (i1 == mid + 1)
		{
			A[curr] = temp[i2++];
		}
		else if (i2>end)
		{
			A[curr] = temp[i1++];
		}
		else if (temp[i1]<=temp[i2])
		{
			A[curr] = temp[i1++];
		}
		else
		{
			A[curr] = temp[i2++];
		}
	}
}
int main()
{
	int Arr1[10] = { 72,6,57,88,60,42,83,73,48,85 };
	int Arr2[8] = {36,20,17,13,28,14,23,15};
	int temp[8] = {};
	QuickSort(Arr1, 0, 9);
	for (int i = 0; i < 10; i++)
	{
		cout << Arr1[i] << " ";
	}
	cout << endl;
	MergeSort(Arr2, temp, 0, 7);
	for (int i = 0; i < 8; i++)
	{
		cout << Arr2[i] << " ";
	}
	cout << endl;

}