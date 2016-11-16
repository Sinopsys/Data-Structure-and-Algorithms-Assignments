#include "Header.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void merge_sort(int *arr, int n);
void merge(int* arr, int start_first, int start_second, int end);
void divide_and_merge(int *arr, int left, int right);

void merge_sort(int *arr, int n)
{
	divide_and_merge(arr, 0, n - 1);
}

void merge(int* arr, int start_first, int start_second, int end)
{
	int i = start_first, h = start_first, j = start_second + 1;
	int *temp_arr = new int[end];
	for (int i = 0; i < end; ++i)
		temp_arr[i] = arr[i];
	while (h <= start_second && j <= end)
	{
		if (arr[h] <= arr[j])
		{
			temp_arr[i] = arr[h];
			++h;
		}
		else
		{
			temp_arr[i] = arr[j];
			++j;
		}
		++i;
	}
	if (start_second < h)
	{
		while(j <= end)
		{
			temp_arr[i] = arr[j];
			++i;
			++j;
		}
	}
	else
	{
		while(start_second >= h)
		{
			temp_arr[i] = arr[h];
			++i;
			++h;
		}
	}
	for (i = start_first; i <= end; ++i) 
		arr[i] = temp_arr[i];
}

void divide_and_merge(int *arr, int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = left + (right - left) / 2;
		divide_and_merge(arr, left, mid);
		divide_and_merge(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

void printArray(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << "; ";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int* arr = new int[5]{ 5,4,3,2,1 };
	printArray(arr, 5);
	merge_sort(arr, 5);
	cout << "\n Сортированный массив:" << endl;
	printArray(arr, 5);
	cout << endl;
	system("pause");
	return 0;
}