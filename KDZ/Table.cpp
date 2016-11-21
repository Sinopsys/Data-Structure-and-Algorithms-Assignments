//
// Created by kirill on 13.11.16.
//

#include "Table.h"

void Table::buildTable(Node *root)
{
    if (root->left != nullptr)
    {
        _code.push_back(0);
        buildTable(root->left);
    }
    if (root->right != nullptr)
    {
        _code.push_back(1);
        buildTable(root->right);
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        _table[root->get_c()] = _code;
    }
    _code.pop_back();
}

Table::Table(Node *root)
{
    buildTable(root);
}

map<char, vector<bool >> Table::get_table()
{
    return this->_table;
}
//
//void Table::buildTable(vector<Node *> vec, int start, int end)
//{
//
//    if (start >= end)
//    {
//        return;
//    }
//    if (start == end - 1)
//    {
//        _table[vec[0]->get_c()].push_back(0);
//        _table[vec[1]->get_c()].push_back(1);
//        return;
//    }
//
//    int highPtr = start;
//    int lowPtr = end;
//    int highSum = vec[highPtr]->get_n();
//    int lowSum = vec[lowPtr]->get_n();
//
//    while (highPtr != lowPtr - 1)
//    {
//        if (highSum > lowSum)
//        {
//            lowPtr--;
//            lowSum += vec[lowPtr]->get_n();
//        } else
//        {
//            highPtr++;
//            highSum += vec[highPtr]->get_n();
//        }
//    }
//
//    int i;
//    for (i = start; i <= highPtr; i++)
//    {
//        _table[vec[i]->get_c()].push_back(0);
//    }
//    for (i = lowPtr; i <= end; i++)
//    {
//        _table[vec[i]->get_c()].push_back(1);
//    }
//
//    buildTable(vec, start, highPtr);
//    buildTable(vec, lowPtr, end);
//}
//
//Table::Table(vector<Node *> vec)
//{
//    buildTable(vec, 0, (int) vec.size() - 1);
//}
