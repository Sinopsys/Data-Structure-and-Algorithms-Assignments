//
// Created by kirill on 14.10.16.
//

#include "knapsack.h"
#include <stdexcept>
#include <cstring>

using std::logic_error;
using std::max;

void deleteArr(int *);

void delete2dArr(int **, int);

void deleteArr(bool *);

void delete2dArr(bool **, int);

//public functions
void Knapsack::initialize(const int capacity, const int *weights, const int *costs, const int n)
{
    if (grid != nullptr)
        delete2dArr(grid, nItems + 1);
    if (itemset != nullptr)
        deleteArr(itemset);

    if (weights != nullptr)
        delete[] Knapsack::weights;
    if (costs != nullptr)
        delete[] Knapsack::costs;

    Knapsack::maxCapacity = capacity;
    Knapsack::weights = new int[n];
    Knapsack::nItems = n;

    Knapsack::costs = new int[n];
    if (costs != nullptr)
        for (int i = 0; i < n; i++)
        {
            Knapsack::costs[i] = costs[i];
        }


    if (weights != nullptr)


        for (int i = 0; i < n; i++)
        {
            Knapsack::weights[i] = weights[i];
        }
    bpCost = 0;
    bpWeight = 0;
    int tmp;
    itemset = new bool[n];
    initialized = true;
}


bool Knapsack::isInitialized()
{
    return initialized;
}

bool Knapsack::isSolved()
{
    return solved;
}

void deleteArr(int *arr)
{
    delete[](arr);
}

void deleteArr(bool *arr)
{
    delete[](arr);
}


void delete2dArr(bool **arr, int n)
{
    // delete rows first
    for (int row = 0; row < n; row++)
    {
        deleteArr(arr[row]);
    }
    // then the 2d array itself
    delete[] arr;
}


void delete2dArr(int **arr, int n)
{
    // delete rows first
    for (int row = 0; row < n; row++)
    {
        deleteArr(arr[row]);
    }
    // then the 2d array itself
    delete[] arr;
}

void Knapsack::solveRecursively()
{
    solved = false;
    bool flag;
    // check for logic error
    if (!isInitialized())
        throw logic_error("Not initialized!");
    if (grid != nullptr)
        delete2dArr(grid, nItems + 1);
    if (itemset != nullptr)
        deleteArr(itemset);

    buildGrid();

    grid[nItems][maxCapacity] = getFromGrid(nItems, maxCapacity);
    backtrack();
    solved = !solved;
}


void Knapsack::solveIteratively()
{
    if (!isInitialized())
        throw logic_error("Not initialized!");
    if (grid != nullptr)
        delete2dArr(grid, nItems + 1);
    if (itemset != nullptr)
        deleteArr(itemset);

    buildGrid();
    for (int i = 1; i < nItems + 1; ++i)
        for (int j = 1; j < maxCapacity + 1; ++j)
        {
            int oneEl = grid[i - 1][j];
            int seen = grid[i - 1][j - weights[i - 1]] + costs[i - 1];

            if (j + 1 > weights[i - 1])
                grid[i][j] = max(oneEl, seen);
            else
                grid[i][j] = grid[i - 1][j];
        }
    backtrack();

    solved = true;
}

void Knapsack::solveGreedy()
{
    if (!isInitialized())
        throw logic_error("Not initialized!");
    if (grid != nullptr)
        delete2dArr(grid, nItems + 1);
    if (itemset != nullptr)
        deleteArr(itemset);

    //TODO: solveGreedy
    solved = true;
}


int Knapsack::getWeight()
{
    //check for logic error
    if (!isSolved())
        throw logic_error("Problem not solved!");
    return bpWeight;
}

int Knapsack::getCost()
{
    //check for logic error
    if (!isSolved())
        throw logic_error("Problem not solved!");
    return bpCost;
}

bool *Knapsack::getItemset()
{
    //check for logic error
    if (!isSolved())
        throw logic_error("Problem not solved!");
    bool *ret = new bool[nItems];
    memcpy(ret, itemset, sizeof(bool) * nItems);
    return ret;

}

//destructor
Knapsack::~Knapsack()
{
    deleteArr(weights);
    deleteArr(itemset);
    deleteArr(costs);
    delete2dArr(grid, nItems + 1);
}

//private functions
void Knapsack::buildGrid()
{
    grid = new int *[nItems + 1];
    for (int i = 0; i < nItems + 1; ++i)
    {
        grid[i] = new int[maxCapacity + 1];
        for (int j = 0; j < maxCapacity + 1; ++j)
            if (j == 0 || i == 0)
                grid[i][j] = 0;
            else
                grid[i][j] = -1;
    }

}

int Knapsack::getFromGrid(int item, int capacity)
{
    bool flag = capacity < weights[item - 1];
    if (item < 1 || capacity < 1)
        return 0;
    if (grid[item][capacity] != -1)
        return grid[item][capacity];
    if (flag)
    {

        grid[item][capacity] =
                getFromGrid(item - 1, capacity);
        return grid[item][capacity];
    }
    else
    {
        int itemID = item - 1;
        int el = capacity - weights[itemID];
        int one = getFromGrid(itemID, capacity);
        int seen = getFromGrid(itemID, el) + costs[itemID];
        grid[item][capacity] = max(el, seen);
        return grid[item][capacity];
    }
}

void Knapsack::backtrack()
{
    bpWeight = 0;
    bpCost = 0;
    int maxItem;
    int maxCost = -1;
    int currCap = maxCapacity;
    itemset = new bool[nItems];
    bool flag = false;
    for (int i = 0; i < nItems; i++)
    {
        itemset[i] = flag;
    }

    bpCost = grid[nItems][maxCapacity];
    bool f = currCap >= 1;
    while (f)
    {
        maxCost = 0;
        flag = true;
        for (int i = 0; i < nItems + 1; ++i)
        {
            if (grid[i][currCap] > maxCost)
            {
                maxCost = grid[i][currCap];

                maxItem = i;
            }
        }
        itemset[maxItem - 1] = flag;
        bpWeight += weights[maxItem - 1];
        currCap -= weights[maxItem - 1];
        f = currCap >= 1;
    }
}


//EOF, blank line
