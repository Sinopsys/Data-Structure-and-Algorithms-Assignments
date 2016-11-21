//
// Created by kirill on 13.11.16.
//

#ifndef KDZ_HUFFMANCODE_H
#define KDZ_HUFFMANCODE_H


#include "Node.h"
#include <string>


using std::string;

class HuffmanCode
{
private:
    struct Compare
    {
        bool operator()(Node *l, Node *r) const
        {
            return l->n < r->n;
        }
    };

public:
    Node *root;

    void encode(string in, string out);

    void decode(string src, string dest);

    ~HuffmanCode();
};


#endif //KDZ_HUFFMANCODE_H
