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
            return l->get_n() < r->get_n();
        }
    };

    Node *_root;

public:

    void encode(string in, string out);

    void decode(string src, string dest);

    ~HuffmanCode();
};


#endif //KDZ_HUFFMANCODE_H
