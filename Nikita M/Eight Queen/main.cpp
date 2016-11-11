#include <iostream>
#include "Eight_Queen.cpp"

using namespace std;

int main()
{
    QueenProblem qp;
    qp.initialize(8);
    qp.backtracking(0);
    std::cout<< "Number of solutions: " << qp.getNumberOfSolutions() << " sovled? " << qp.isSolved();
    return 0;
}

