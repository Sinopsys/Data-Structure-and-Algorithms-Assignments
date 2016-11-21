//
// Created by kirill on 13.11.16.
//

#include "Node.h"

Node::Node(Node *l, Node *r)
{
    this->left = l;
    this->right = r;
    n = l->n + r->n;
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
