//
// Created by kirill on 13.11.16.
//

#ifndef KDZ_TABLE_H
#define KDZ_TABLE_H

#include <vector>
#include "Node.h"
#include <map>

using std::vector;
using std::map;

class Table
{
private:
    vector<bool> code;

    void buildTable(Node *root);

public:
    Table()
    {};

    Table(Node *root);

    map<char, vector<bool >> table;
};


#endif //KDZ_TABLE_H
