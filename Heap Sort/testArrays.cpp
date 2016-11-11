


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
