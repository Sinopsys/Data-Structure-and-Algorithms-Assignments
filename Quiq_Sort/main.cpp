//
// Created by Kirill on 7.10.2016.
//

#include <cstdlib>
#include "quick_sort.h"

void q_sort::quick_sort_middle(int *arr, int n)
{
    quick_sort(arr, 0, n, get_middle_pivot);
}

void q_sort::quick_sort_last(int *arr, int n)
{
    quick_sort(arr, 0, n, get_last_pivot);
}

void q_sort::quick_sort_rand(int *arr, int n)
{
    srand((unsigned int) time(0));
    quick_sort(arr, 0, n, get_rand_pivot);
}

int q_sort::get_middle_pivot(int from, int to)
{
    return (to + from - 1) / 2;
}

int q_sort::get_last_pivot(int from, int to)
{
    return to - 1;
}

int q_sort::get_rand_pivot(int from, int to)
{
    return rand() % (to - from) + from;
}

void q_sort::quick_sort(int *arr, int from, int to, pivot_chooser pivot_chooser)
{
    //if case the len of array is > 1
    if (to - from > 1)
    {
        //sort
        int index = rearrange_array_with_pivot(arr, from, to, pivot_chooser(from, to));
        //sort left part
        quick_sort(arr, from, index, pivot_chooser);
        //sort right part
        quick_sort(arr, index + 1, to, pivot_chooser);
    }
}

int q_sort::rearrange_array_with_pivot(int *arr, int from, int to, int pivot_index)
{
    //save pivot
    int pivot = arr[pivot_index];
    //initialize left and right indexes
    int left = 0, right = to - 1;
    while (true)
    {
        //left one
        while ((arr[left] <= pivot) && (left < to - 1))
            left++;
        //right one
        while ((arr[right] >= pivot) && (right > 0))
            right--;
        //at the same point
        if (left >= right)
            break;
        //swap
        else
        {
            int tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;
            left++;
            right--;
        }
    }
    //"inserting pivot"
    //if located in the left part
    if (pivot_index <= right)
    {
        int dop = arr[right];
        arr[right] = arr[pivot_index];
        arr[pivot_index] = dop;
        return right;
    }
    //if located in the right part
    else
    {
        int dop = arr[left];
        arr[left] = arr[pivot_index];
        arr[pivot_index] = dop;
        return left;
    }
}
//EOF
