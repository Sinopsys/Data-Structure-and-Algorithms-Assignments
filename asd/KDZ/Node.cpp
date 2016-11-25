//
// Created by kirill on 13.11.16.
//

#include "Node.h"

Node::Node(Node *l, Node *r)
{
    this->left = l;
    this->right = r;
    _n = l->_n + r->_n;
}

Node::Node()
{
    this->right = this->left = nullptr;
}

Node::~Node()
{
    delete this->right;
    delete this->left;
}

int Node::get_n()
{
    return this->_n;
}

char Node::get_c()
{
    return this->_c;
}

void Node::set_n(int n)
{
    this->_n = n;
}

void Node::set_c(char c)
{
    this->_c = c;
}
