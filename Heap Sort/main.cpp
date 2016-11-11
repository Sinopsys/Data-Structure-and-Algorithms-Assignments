/**
 * @Student :Kupriyanov Kirill
 * @Group   :BSE151(1)
 * @Task    :Implement the HeapSort algorythm based on heapSort.h
 **/


#include <iostream>
#include "heapSort.h"
#include <cstdlib>

using std::swap;
using std::length_error;
using namespace std;

void Heapsort::heapSort(int *arr, int n)
{
    Heap heap(arr, n);
    for (int parent = 0; parent < n; ++parent)
    {
        arr[parent] = heap.extractMin();
    }
}

Heap::Heap(const int *source, const int n) : capacity(n)
{
    currentSize = 0;
    storage = new int[n];
    for (int i = 0; i <= n - 1; ++i)
    {
        insert(source[i]);
    }
}

Heap::~Heap()
{
    delete[] storage;
}

int Heap::getMin()
{
    return storage[0];
}

int Heap::extractMin()
{
    if (currentSize < 1)
        throw length_error("Empty heap.");
    //get the minimum element then
    //reduce the size of heap by 1 and put the
    //last element to the 1st position
    //after that pull it all the way down
    int res = getMin();
    storage[0] = storage[currentSize - 1];
    --currentSize;
    heapifyDown(0);
    return res;
}

void Heap::insert(const int value)
{
    if (currentSize >= capacity)
    {
        throw length_error("Full heep.");
    }
    int oldSize = currentSize;
    storage[currentSize] = value;
    ++currentSize;
    heapifyUp(oldSize);
}

void Heap::heapifyDown(int index)
{
    int parent = index, minElement, leftChild, rightChild;
    //find child's indexes
    if (parent == 0)
    {
        leftChild = 1;
        rightChild = 2;
    }
    else
    {
        leftChild = 2 * parent;
        rightChild = leftChild + 1;
    }
    //find the min child
    if (leftChild <= currentSize && storage[leftChild] <= storage[parent])
    {
        minElement = leftChild;
    }
    else
    {
        minElement = parent;
    }
    if (rightChild <= currentSize && storage[rightChild] <= storage[minElement])
    {
        minElement = rightChild;
    }
    //recursively call heapifydown
    if (minElement != parent)
    {
        swap(storage[parent], storage[minElement]);
        heapifyDown(minElement);
    }
}

void Heap::heapifyUp(int index)
{
    if (index / 2 > -1 && storage[index / 2] > storage[index])
    {
        swap(storage[index], storage[index / 2]);
        heapifyUp(index / 2);
    }
}
//EOF




bool isSorted(int *arr, int len)
{
    for (int i = 0; i < len - 1; ++i)
    {
        if (arr[i + 1] < arr[i])
        {
            std::cout << "PROBLEM" << std::endl;
            return false;
        }
    }
    return true;
}

int **createNarrays(int numberOfArrays, int lengthOfEach, int maxValue)
{
    int **arrays = new int *[numberOfArrays];
    for (int i = 0; i < numberOfArrays; ++i)
    {
        arrays[i] = new int[lengthOfEach];
        for (int j = 0; j < lengthOfEach; ++j)
        {
            arrays[i][j] = rand() % maxValue + 1;
        }
    }
    return arrays;
}

void copyArrys(int *from, int *to, int len)
{
    for (int i = 0; i < len; ++i)
    {
        to[i] = from[i];
    }
}

void printArr(int *arr, int len)
{
    for (int i = 0; i < len; ++i)
    {
        std::cout << arr[i] << '|';
    }
    std::cout << std::endl;
}

int i = 0;

void sortArrays(int **arrays, int numberOfArrays, int lengthOfEach)
{
    Heapsort hs;
    bool ok = true;
    while (ok && i < numberOfArrays)
    {
        int *currArr = new int[lengthOfEach];
        copyArrys(arrays[i++], currArr, lengthOfEach);
        // cout << endl << "UNSORTED:" << endl;
        //printArr(currArr, lengthOfEach);
        hs.heapSort(currArr, lengthOfEach);
        //cout << "SORTED:" << endl;
        //printArr(currArr, lengthOfEach);
        ok = isSorted(currArr, lengthOfEach);
    }
    std::cout << "OK" << std::endl;
}

int main()
{
    srand((unsigned int) (i * time(0)));
    int numberOfArrays = 100,
            lengthOdEach = 20,
            maxValue = 1000;
    int **arrs = createNarrays(numberOfArrays, lengthOdEach, maxValue);
    sortArrays(arrs, numberOfArrays, lengthOdEach);
}
