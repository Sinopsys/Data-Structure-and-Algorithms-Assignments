//
// Created by kirill on 17.11.16.
//

/**
 * Please note the plural word "vertices" in singular is VERTEX, not vertice
 * I am not responsible for that awful typo!
 */

#include "SCCSolver.h"
#include <stdexcept>
#include <algorithm>

using std::vector;
using std::logic_error;

Vertice::Vertice(int id)
{
    Vertice::id = id;
}

void Vertice::refresh()
{
    // post conditions
    finished_step = -1;
    discovered_step = -1;
    passed = false;
}

bool Vertice::compare(Vertice *v1, Vertice *v2)
{
    return (*v1).finished_step > (*v2).finished_step;
}

void SCCSolver::initialize(std::vector<int> *adjList, int n)
{
    // check if adjacencyList is not nullptr and vertPool is not empty and clearing them if they are
    // before the intiialization
    if (adjacencyList != nullptr || vertPool.size() > 0)
    {
        delete[] adjacencyList;
        vector<Vertice *>::iterator itr;
        for (itr = vertPool.begin(); itr != vertPool.end(); ++itr)
        {
            delete *itr;
        }
        vertPool.clear();
    }

    nVertices = n;
    adjacencyList = new vector<int>[n];

    // initialize a new vector from the old one
    for (int i = 0; i < n; ++i)
    {
        adjacencyList[i] = vector<int>(adjList[i]);
    }

    buildPool();
    // post codnitions
    initialized = true;
    solved = false;
}

void SCCSolver::solve()
{
    if (!initialized)
    {
        throw logic_error("not yet initialized");
    }
    runDFS();
    vector<int> *vec = reverseAdjacencyList(adjacencyList, nVertices);
    adjacencyList = vec;
    sortPool();
    result = runDFS();
    solved = true;
}

std::vector<int> *SCCSolver::reverseAdjacencyList(std::vector<int> *adjList, int n)
{
    vector<int> *res = new vector<int>[n];
    int v = 0;
    // run as N^2
    while (v != n)
    {
        res[v] = vector<int>();
        for (int v1 = 0; v1 < n; ++v1)
        {
            vector<int>::iterator itr;
            // go through the starting adjList
            for (itr = adjList[v1].begin(); itr != adjList[v1].end(); ++itr)
            {
                // find the vertex
                if (*itr == v)
                {
                    res[v].push_back(v1);
                }
            }
        }
        ++v;
    }
    return res;
}

std::vector<std::vector<int>> SCCSolver::getResult()
{
    if (!solved)
    {
        throw logic_error("yet not solved");
    }
    return result;
}

bool SCCSolver::isSolved()
{
    return solved;
}

bool SCCSolver::isInitialized()
{
    return initialized;
}

SCCSolver::~SCCSolver()
{
    if (adjacencyList != nullptr)
    {
        delete[] adjacencyList;
    }
    if (vertPool.size() > 0)
    {
        for (int i = 0; i < vertPool.size(); ++i)
        {
            delete vertPool[i];
        }
        vertPool.clear();
    }
}

void SCCSolver::buildPool()
{
    vertPool = vector<Vertice *>();
    int count = 0;
    while (count != nVertices)
    {
        vertPool.push_back(new Vertice(count));
        ++count;
    };
}


// used Kormen to implement this function
std::vector<std::vector<int>> SCCSolver::runDFS()
{
    refreshPool();
    int c = 0;

    vector<vector<int>> res;
    vector<Vertice *>::iterator itr;
    for (itr = vertPool.begin(); itr != vertPool.end(); ++itr)
    {
        // check if discovered_step is < 0
        if ((*itr)->discovered_step < 0)
        {
            int tmp = ((*itr)->id);
            vector<int> tree = vector<int>();
            // add a new root, then get the others
            tree.push_back(tmp);
            DFSVisit(*itr, c, tree);
            res.push_back(tree);
        }
    }
    return res;
}

void SCCSolver::DFSVisit(Vertice *v, int &step, std::vector<int> &tree)
{
    ++step;
    v->discovered_step = step;
    v->passed = true;

    vector<int>::iterator itr;
    for (itr = adjacencyList[v->id].begin(); itr != adjacencyList[v->id].end(); ++itr)
    {
        Vertice *vptr = getVertice(*itr);
        if ((*vptr).discovered_step < 0)
        {
            tree.push_back(*itr);
            DFSVisit(vptr, step, tree);
        }
    }
    ++step;
    v->finished_step = step;
}


void SCCSolver::sortPool()
{
    std::sort(vertPool.begin(), vertPool.end(), Vertice::compare);
}

void SCCSolver::refreshPool()
{
    vector<Vertice *>::iterator itr;
    for (itr = vertPool.begin(); itr != vertPool.end(); ++itr)
    {
        (*itr)->refresh();
    }
}

Vertice *SCCSolver::getVertice(int id)
{
    vector<Vertice *>::iterator itr;
    for (itr = vertPool.begin(); itr != vertPool.end(); ++itr)
    {
        if ((*itr)->id == id)
        {
            return *itr;
        }
    }
    return nullptr;
}


// EOF
