//
// Created by kirill on 13.11.16.
//

#include "Table.h"

void Table::buildTable(Node *root)
{
    if (root->left != nullptr)
    {
        code.push_back(0);
        buildTable(root->left);
    }
    if (root->right != nullptr)
    {
        code.push_back(1);
        buildTable(root->right);
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        table[root->c] = code;
    }
    code.pop_back();
}

Table::Table(Node *root)
{
    buildTable(root);
}
