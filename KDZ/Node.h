//
// Created by kirill on 13.11.16.
//

#ifndef KDZ_NODE_H
#define KDZ_NODE_H


class Node
{
public:
    int n;
    char c;
    Node *left, *right;

    Node(Node *l, Node *r);

    Node();

    ~Node();
};


#endif //KDZ_NODE_H
