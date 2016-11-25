//
// Created by kirill on 13.11.16.
//

#include "HuffmanCode.h"
#include <map>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "Table.h"

using std::map;
using std::list;
using std::vector;
using std::ifstream;
using std::ofstream;

ofstream s("asd.txt");

void printVec(vector<bool> vec)
{
    for (auto i = vec.begin(); i != vec.end(); ++i)
    {
        s << *i;
    }
}

void HuffmanCode::encode(string in, string out)
{
    map<char, int> m;
    ifstream myfile(in);
    char c;
    while (true)
    {
        char tmp = (char) myfile.get();
        if (tmp != EOF)
            c = tmp;
        else
            break;
        ++m[c];
    }


    list<Node *> lst;
    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        Node *tmp = new Node();
        tmp->set_c(itr->first);
        tmp->set_n(itr->second);
        lst.push_back(tmp);
    }

    while (lst.size() != 1)
    {
        lst.sort(Compare());
        Node *tmp_left = lst.front();
        lst.pop_front();
        Node *tmp_right = lst.front();
        lst.pop_front();
        lst.push_front(new Node(tmp_left, tmp_right));
    }

    _root = lst.front();
    Table *table = new Table(_root);


    myfile.clear();
    myfile.seekg(0);

    ofstream output(out);

    int count = 0;
    char buf = 0;
    while (!myfile.eof())
    {
        char c = (char) myfile.get();
        vector<bool> x = table->get_table()[c];
        for (int n = 0; n < x.size(); ++n)
        {
            buf = buf | x[n] << (7 - count);
            count++;
            if (count == 8)
            {
                count = 0;
                output << buf;
                buf = 0;
            }
        }
    }

    myfile.close();
    output.close();

    m.clear();
    lst.clear();



    delete table;
}

void HuffmanCode::decode(string src, string dest)
{
    ifstream from(src);
    ofstream de(dest);

    Node *p = _root;
    int count = 0;
    char byte;
    byte = (char) from.get();
    while (!from.eof())
    {
        bool b = (bool) (byte & (1 << (7 - count)));
        if (b)
            p = p->right;
        else
            p = p->left;
        if (p->left == nullptr && p->right == nullptr)
        {
            de << p->get_c();
            p = _root;
        }
        count++;
        if (count == 8)
        {
            count = 0;
            byte = (char) from.get();
        }
    }
    from.close();
}

HuffmanCode::~HuffmanCode()
{
    Node *tmp = _root;
    if (tmp->left != nullptr)
        delete tmp->left;
    if (tmp->right != nullptr)
        delete tmp->right;
    delete tmp;
    delete _root;
}
