#include<iostream>
using namespace std;
template<typename E>
void swap(E A[], int a, int b)
{
	E temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}
template <typename E>
void InsertSort(E arr[], int n)
{
	for (int i = 0; i < n-1; i++)
	{
		int end = i;
		int term = arr[i + 1];
		for (int j = 0; j <=end; j++)
		{
			if (term < arr[j])
			{
				swap(arr, i + 1,j);
			}
		}
	}
}
template<typename E>
void SelectSort(E arr[], int n)
{
	int	begin = 0;
	int end = n - 1;
	for (int i = begin; i < end; i++)
	{
		int mini = i;
		for (int j = i+1; j<=end; j++)
		{
			if (arr[j] < arr[mini])
			{
				mini = j;
			}
		}
		swap(arr, i, mini);
	}
}
template<typename E>
void InsertSorthelp(E arr[], int n, int m)
{
	for (int i = m; i < n; i=i+m)
	{
		for (int j = i; j >= m; j = j - m)
		{
			if (arr[j]<arr[j-m])
			{
				swap(arr, j, j - m);
			}
		}
	}
}
template<typename E>
void ShellSort(E arr[], int n)
{
	for (int i = n/2; i >2; i=i/2)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j+i]>arr[j])
			{
				InsertSorthelp(&arr[j], n - j, i);
			}
		}
	}
	InsertSorthelp(arr, n,1);
}
int main()
{
	int a[16] = { 59,20,17,13,28,14,23,83,36,98,11,70,65,41,42,15 };
	int b[16] = { 59,20,17,13,28,14,23,83,36,98,11,70,65,41,42,15 };
	int c[16] = { 59,20,17,13,28,14,23,83,36,98,11,70,65,41,42,15 };
	InsertSort(a, 16);
	SelectSort(b, 16);
	ShellSort(c, 16);
	for (int i = 0; i < 16; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 16; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 16; i++)
	{
		cout << c[i] << " ";
	}
}