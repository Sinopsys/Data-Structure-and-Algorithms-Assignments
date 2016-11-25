//
// Created by kirill on 13.11.16.
//

#ifndef KDZ_TABLE_H
#define KDZ_TABLE_H

#include <vector>
#include "Node.h"
#include <map>
#include <vector>

using std::vector;
using std::map;
using std::vector;

class Table
{
private:
    vector<bool> _code;

    void buildTable(Node *root);

    map<char, vector<bool >> _table;
public:
    Table()
    {};

    Table(Node *root);

    map<char, vector<bool >> get_table();

    ~Table();
};


#endif //KDZ_TABLE_H
