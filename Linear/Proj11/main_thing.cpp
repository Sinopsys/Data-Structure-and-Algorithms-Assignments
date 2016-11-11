#include <iostream>
#include <cmath>
#include "LinearSort.h"

struct Number {
	int base, id;
};


void RadixSort(int *arr, int n, int base);
void SortAtDigit(int *arr, int n, const Number& si);
int get_digit(int number, const Number& dinfo);
int max_element(int *arr, int n, const Number& dinfo);
int min_element(int *arr, int n, const Number& dinfo);
int max_element(int *arr, int n);
int min_element(int *arr, int n);
void copy_array(int *source, int *dest, int size);

int pred(int a, int b, Number& si)
{
	if (get_digit(a, si) > get_digit(b, si)) return 1;
	if (get_digit(a, si) < get_digit(b, si)) return -1;
	return 0;
}

int max_element(int * arr, int n, Number& si)
{
	int max = arr[0];
	for (int i = 1; i < n; ++i)
	{
		if (pred(max, arr[i], si) < 0) {
			max = arr[i];
		}
	}
	return max;
}

int min_element(int * arr, int n, Number& si)
{
	int min = arr[0];
	for (int i = 1; i < n; ++i)
	{
		if (pred(min, arr[i], si) > 0) min = arr[i];
	}
	return min;
}

void counting_sort(int * arr, int n)
{
	int max = max_element(arr, n);
	int min = min_element(arr, n);

	int *temp = new int[max - min + 1];
	for (int i = 0; i < max - min + 1; ++i) {
		temp[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		temp[arr[i] - min] = temp[arr[i] - min] + 1;
	}
	for (int i = 1; i < max - min + 1; ++i) {
		temp[i] = temp[i] + temp[i - 1];
	}

	int *output = new int[n];
	for (int i = 0; i < n; ++i) {
		output[i] = 0;
	}
	for (int i = n - 1; i >= 0; --i) {
		output[temp[arr[i] - min] - 1] = arr[i];
		temp[arr[i] - min] = temp[arr[i] - min] - 1;
	}
	copy_array(output, arr, n);
	delete[] temp;
	delete[] output;
}

void counting_sort(int * arr, int n, const Number& si)
{
	int max_dig = max_element(arr, n, si);
	int min_dig = min_element(arr, n, si);

	int *temp = new int[max_dig - min_dig + 1];
	for (int i = 0; i < max_dig - min_dig + 1; ++i) {
		temp[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		temp[get_digit(arr[i], si) - min_dig] = temp[get_digit(arr[i], si) - min_dig] + 1;
	}
	for (int i = 1; i < max_dig - min_dig + 1; ++i) {
		temp[i] = temp[i] + temp[i - 1];
	}

	int *output = new int[n];
	for (int i = 0; i < n; ++i) {
		output[i] = 0;
	}
	for (int i = n - 1; i >= 0; --i) {
		output[temp[get_digit(arr[i], si) - min_dig] - 1] = arr[i];
		temp[get_digit(arr[i], si) - min_dig] = temp[get_digit(arr[i], si) - min_dig] - 1;
	}
	copy_array(output, arr, n);
	delete[] temp;
	delete[] output;
}

int number_length(int number, int base)
{
	int count = 0;
	while (number)
	{
		number /= base;
		count++;
	}
	return count;
}

void print1(int *arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}

void radix_sort(int * arr, int n, int base)
{
	int len = number_length(max_number_abs(arr, n), base);
	int digit = 0;
	while (digit < len)
	{
		SortAtDigit(arr, n, base, id);
		digit++;
	}
}

int max_number_abs(int * arr, int n)
{
	// here we think in terms of digit
	int max = abs(arr[0]);
	for (int i = 1; i < n; ++i)
	{
		int dig = abs(arr[i]);
		if (max < dig) {
			max = dig;
		}
	}
	return max;
}

void SortAtDigit(int * arr, int n, const Number& si)
{
	counting_sort(arr, n, si);
}

int get_digit(int number, const Number& dinfo)
{
	return ((int)(number / pow(dinfo.base, dinfo.id))) % dinfo.base;
}

int max_element(int * arr, int n, const Number& dinfo)
{
	// here we think in terms of digit
	int max = get_digit(arr[0], dinfo);
	for (int i = 1; i < n; ++i)
	{
		int dig = get_digit(arr[i], dinfo);
		if (max < dig) {
			max = dig;
		}
	}
	return max;
}

int min_element(int *arr, int n, const Number& dinfo)
{
	// here we think in terms of digit
	int min = get_digit(arr[0], dinfo);
	for (int i = 1; i < n; ++i)
	{
		int dig = get_digit(arr[i], dinfo);
		if (min > dig) {
			min = dig;
		}
	}
	return min;
}

int max_element(int * arr, int n)
{
	int max = arr[0];
	for (int i = 1; i < n; ++i)
	{
		if (max < arr[i]) max = arr[i];
	}
	return max;
}

int min_element(int *arr, int n)
{
	int min = arr[0];
	for (int i = 1; i < n; ++i)
	{
		if (min > arr[i]) min = arr[i];
	}
	return min;
}

void copy_array(int *source, int *dest, int size)
{
	for (int i = 0; i < size; ++i)
	{
		dest[i] = source[i];
	}
}