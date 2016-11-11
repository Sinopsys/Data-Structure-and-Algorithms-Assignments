/**
 * @author  Kirill Kupriyanov BSE151-1
 * @created 14.10.2016
 * @version 1.0
 */

#include <iostream>
#include "Knapsack.cpp"
#include "knapsack.h"
using namespace std;

int main()
{
    //считывание данных
    int capacity, n;
    cin >> capacity;
    cin >> n;
    int *weights = new int[n];
    int *costs = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> weights[i];
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> costs[i];
    }
//объект класса Knapsack
    Knapsack *knap = new Knapsack();
    knap->initialize(capacity, weights, costs, n);
//используем жадный алгоритм
    knap->solveIteratively(); //или любую другую
    cout << "Weight: " << knap->getWeight() << endl;
    cout << "Cost: " << knap->getCost() << endl;
    cout << "Used number of items: ";
    for (int j = 0; j < n; ++j)
    {
        if (knap->getItemset()[j])
            cout << j + 1 << " ";
    }
    return 0;
}

/*
5
3
1
4
3
10
15
20

 */