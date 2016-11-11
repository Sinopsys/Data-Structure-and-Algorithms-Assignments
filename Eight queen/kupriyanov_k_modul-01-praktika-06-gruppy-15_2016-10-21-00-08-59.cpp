//
// Created by kirill on 18.10.16.
//

#include "eight_queen.h"
#include <stdexcept>

// used to initialize board[i][j] with 1
void placeQueen(int **, int, int);

// used to initialize board[i][j] with 0
void removeQueen(int **, int, int);

void QueenProblem::initialize(const int size)
{
    initialized = solved = false;
    board = new int *[size];
    for (int i = 0; i < size; ++i)
        board[i] = new int[size];
    QueenProblem::size = size;

    // flip initialized to true
    initialized = !initialized;
}

bool QueenProblem::isInitialized()
{
    return initialized;
}

bool QueenProblem::isSolved()
{
    return solved;
}

void QueenProblem::backtracking(int queen)
{
    // check for logic eoor
    if (!isInitialized())
        throw std::logic_error("contents are not initialized");


    int row = queen;
    // found a solution
    if (row == size)
    {
        ++numberOfSolutions;
        return;
    }
    for (int col = 0; col < size; ++col)
    {
        if (isInserted(row, col))
        {
            placeQueen(board, row, col);
            // move to the next rwo
            backtracking(row + 1);
            // if we get here, we are bckatracked
            removeQueen(board, row, col);
        }
    }
    // flip solved to true
    solved = true;
}

void placeQueen(int **board, int row, int column)
{
    board[row][column] = 1;
}

void removeQueen(int **board, int row, int column)
{
    board[row][column] = 0;
}


bool QueenProblem::isInserted(int queen_row, int queen_col)
{
    // check for vertical intersection
    for (int row = 0; row < size; ++row)
        if (board[row][queen_col] == 1 && row != queen_row)
            return false;

    // check for left-upper diagonal intersection
    int row = queen_row - 1, col = queen_col - 1;
    while (row >= 0 && col >= 0)
    {
        if (board[row][col] == 1)
            return false;
        --row;
        --col;
    }
    // check for right-upper diagonal intersection
    row = queen_row - 1;
    col = queen_col + 1;
    while (row >= 0 && col <= size - 1)
    {
        if (board[row][col] == 1)
            return false;
        --row;
        ++col;
    }

    // check for left-lower diagonal intersection
    row = queen_row + 1;
    col = queen_col - 1;
    while (row <= size - 1 && col >= 0)
    {
        if (board[row][col] == 1)
            return false;
        ++row;
        --col;
    }

    // check for right-lower diagonal intersection
    row = queen_row + 1;
    col = queen_col + 1;
    while (row <= size - 1 && col <= size - 1)
    {
        if (board[row][col] == 1)
            return false;
        ++row;
        ++col;
    }

    // found no intersections
    // therefore we can insert a queen in this position
    return true;
}

long QueenProblem::getNumberOfSolutions()
{
    if (!isSolved())
        throw std::logic_error("problem is not solved");
    return numberOfSolutions;
}

QueenProblem::~QueenProblem()
{
    for (int i = 0; i < size - 1; ++i)
        delete[] board[i];
    delete[] board;
}
// EOF

