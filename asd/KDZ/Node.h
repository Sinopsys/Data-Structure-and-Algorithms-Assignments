//
// Created by kirill on 13.11.16.
//

#ifndef KDZ_NODE_H
#define KDZ_NODE_H


class Node
{
private:
    int _n;

    char _c;
public:
    int get_n();

    char get_c();

    void set_c(char c);

    void set_n(int n);

    Node *left, *right;

    Node(Node *l, Node *r);

    Node();

    ~Node();
};


#endif //KDZ_NODE_H
