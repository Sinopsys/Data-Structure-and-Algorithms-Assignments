#include <iostream>
#include "SCCSolver.h"

using std::vector;
using std::cout;
using std::endl;

void printVec(vector<vector<int>> vec)
{
    vector<vector<int>>::iterator out_itr;
    vector<int>::iterator in_itr;

    for (out_itr = vec.begin(); out_itr != vec.end(); ++out_itr)
    {
        for (in_itr = out_itr->begin(); in_itr != out_itr->end(); ++in_itr)
        {
            cout << *in_itr << ' ';
        }
        cout << endl;
    }
}

//-------------------------test Maksa-----------------
void test_0()
{
    SCCSolver *solver = new SCCSolver;

    int n;
    std::vector<int> *adjlist;
    n = 4;
    adjlist = new std::vector<int>[n];
    adjlist[1].push_back(2);
    adjlist[1].push_back(0);
    adjlist[2].push_back(3);
    adjlist[3].push_back(1);

    solver->initialize(adjlist, n);
    solver->solve();
    std::cout << solver->getResult().size() << "\n";
    for (std::vector<int> v : solver->getResult())
    {
        for (int i : v)
            std::cout << i << " ";
        std::cout << std::endl;
    }
    delete[] adjlist;

    std::cout << std::endl;

    n = 10;
    adjlist = new std::vector<int>[n];
    adjlist[0].push_back(1);
    adjlist[0].push_back(2);
    adjlist[1].push_back(3);
    adjlist[2].push_back(5);
    adjlist[3].push_back(4);
    adjlist[3].push_back(6);
    adjlist[4].push_back(1);
    adjlist[4].push_back(2);
    adjlist[4].push_back(6);
    adjlist[5].push_back(4);
    adjlist[5].push_back(9);
    adjlist[6].push_back(7);
    adjlist[7].push_back(9);
    adjlist[8].push_back(7);
    adjlist[9].push_back(8);

    solver->initialize(adjlist, n);
    solver->solve();
    std::cout << solver->getResult().size() << "\n";
    for (std::vector<int> v : solver->getResult())
    {
        for (int i : v)
            std::cout << i << " ";
        std::cout << std::endl;
    }
    delete[] adjlist;

    delete solver;
}
//-------------------------test Maksa-----------------


int main()
{
//-----------------------------test 1--------------------------
    vector<int> *testVec = new vector<int>[8];
    testVec[0] = {1};
    testVec[1] = {6, 2, 7};
    testVec[2] = {3, 5};
    testVec[3] = {2, 4};
    testVec[4] = {4};
    testVec[5] = {6, 4};
    testVec[6] = {5};
    testVec[7] = {0, 6};

    SCCSolver sccs;
    sccs.initialize(testVec, 8);

    sccs.solve();
    vector<vector<int>> res = sccs.getResult();
    cout << "\ntest 1:\n";
    printVec(res);
    testVec->clear();
    for (int i = 0; i < res.size(); ++i)
    {
        res[i].clear();
    }
    cout << endl;
//    0 7 1
//    2 3
//    6 5
//    4
//-----------------------------test 1--------------------------


//-----------------------------test 2--------------------------
    testVec = new vector<int>[12];
    testVec[0] = {1, 4};
    testVec[1] = {2, 6};
    testVec[2] = {1, 3, 7};
    testVec[3] = {2, 8};
    testVec[4] = {0, 5};
    testVec[5] = {0, 4};
    testVec[6] = {1, 7};
    testVec[7] = {2, 6};
    testVec[8] = {3, 9};
    testVec[9] = {8};
    testVec[10] = {11};
    testVec[11] = {10};


    sccs.initialize(testVec, 12);
    sccs.solve();
    res = sccs.getResult();
    cout << "test 2:\n";
    printVec(res);
    testVec->clear();
    for (int i = 0; i < res.size(); ++i)
    {
        res[i].clear();
    }
    cout << endl;
//    10 11
//    0 4 5
//    1 2 3 8 9 7 6
//-----------------------------test 2--------------------------


//-----------------------------test 3--------------------------
    testVec = new vector<int>[8];
    testVec[0] = {1};
    testVec[1] = {2, 3};
    testVec[2] = {0, 3};
    testVec[3] = {4};
    testVec[4] = {3};
    testVec[5] = {4, 6};
    testVec[6] = {5, 7};
    testVec[7] = {6, 4};


    sccs.initialize(testVec, 8);
    sccs.solve();
    res = sccs.getResult();
    cout << "test 3:\n";
    printVec(res);
    testVec->clear();
    for (int i = 0; i < res.size(); ++i)
    {
        res[i].clear();
    }
    cout << endl;
//    5 6 7
//    0 2 1
//    3 4
//-----------------------------test 3--------------------------

    //-------------------------test Maksa-----------------

// Output:
    // 2
    // 1 3 2
    // 0
    //
    // 4
    // 0
    // 1 4 3 5 2
    // 6
    // 9 7 8
    cout << "Test Maksa:\n";
//    while (true)
    test_0();
    //-------------------------test Maksa-----------------

    return 0;
}

// EOF
