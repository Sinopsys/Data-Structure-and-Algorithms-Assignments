//
// Created by kirill on 13.11.16.
//

#include "HuffmanCode.h"

#include "HuffmanCode.h"
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include "Table.h"

using std::map;
using std::list;
using std::vector;
using std::ifstream;
using std::ofstream;

void HuffmanCode::encode(string in, string out)
{
    map<char, int> m;
    ifstream myfile(in);
    while (!myfile.eof())
    {
        char c = (char) myfile.get();
        ++m[c];
    }

    list<Node *> lst;
    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        Node *tmp = new Node();
        tmp->c = itr->first;
        tmp->n = itr->second;
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

    root = lst.front();
    Table table(root);
    myfile.clear();
    myfile.seekg(0);


    myfile.clear();
    myfile.seekg(0);


    ofstream output(out);

    int count = 0;
    char buf = 0;
    while (!myfile.eof())
    {
        char c = (char) myfile.get();
        vector<bool> x = table.table[c];
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
}

void HuffmanCode::decode(string src, string dest)
{
    ifstream from(src);
    ofstream de(dest);

    Node *p = root;
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
            de << p->c;
            p = root;
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
    Node *tmp = root;
    if (tmp->left != nullptr)
        delete tmp->left;
    if (tmp->right != nullptr)
        delete tmp->right;
    delete tmp;
    delete root;
}
