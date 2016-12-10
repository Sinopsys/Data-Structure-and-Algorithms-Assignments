//
// Created by kirill on 09.12.16.
//

#include <iostream>
#include "RBT.h"

using namespace std;

static Node NIL = {0, 0, 0, 0, BLACK};

#define NIL_NODE (&NIL)

Node *RBT::new_node(int key)
{
    Node *node = new Node;

    node->key = key;
    node->left = NIL_NODE;
    node->right = NIL_NODE;
    node->parent = NIL_NODE;
    node->color = RED;

    return node;
}

Node *RBT::search(int key)
{
    if (_root == NIL_NODE)
    {
        return NIL_NODE;
    } else
    {
        Node *x = _root;

        while (x != NIL_NODE)
        {
            if (key < x->key)
            {
                x = x->left;
            } else if (key > x->key)
            {
                x = x->right;
            } else
            {
                return x;
            }
        }
    }
    return NIL_NODE;
}

void RBT::left_rotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NIL_NODE)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NIL_NODE)
    {
        _root = y;
    } else if (x == x->parent->left)
    {
        x->parent->left = y;
    } else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void RBT::right_rotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;

    if (x->right != NIL_NODE)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NIL_NODE)
    {
        _root = x;
    } else if (y == y->parent->left)
    {
        y->parent->left = x;
    } else
    {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;

}

void RBT::insert(int key)
{
    Node *z = new_node(key);

    if (_root == nullptr || _root == NIL_NODE)
    {
        _root = z;
        _root->color = BLACK;

        cout << "inserted" << endl;
        return;
    } else
    {
        Node *y = NIL_NODE;
        Node *x = _root;
        while (x != NIL_NODE)
        {
            y = x;
            if (z->key < x->key)
            {
                x = x->left;
            } else if (z->key > x->key)
            {
                x = x->right;
            } else
            {
                cout << "key repeated" << endl;
                return;
            }
        }

        z->parent = y;

        if (y == NIL_NODE)
        {
            _root = z;
        } else if (z->key < y->key)
        {
            y->left = z;
        } else
        {
            y->right = z;
        }

        insert_fixup(z);
        return;
    }
}

void RBT::insert_fixup(Node *z)
{
    Node *y = NIL_NODE;

    while (z->parent != NIL_NODE && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y->color == RED)//case1
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            } else
            {
                if (z == z->parent->right)//case2
                {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = BLACK;//case3
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);

            }
        } else
        {
            y = z->parent->parent->left;
            if (y->color == RED)//case4
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            } else
            {
                if (z == z->parent->left)//case5
                {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = BLACK;//case6
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);

            }
        }
    }
    _root->color = BLACK;
    return;
}

Node *RBT::tree_min(Node *x)
{
    while (x->left != NIL_NODE)
    {
        x = x->left;
    }
    return x;
}

Node *RBT::get_successor(Node *x)
{
    if (x->right != NIL_NODE)
    {
        return tree_min(x->right);
    } else
    {
        Node *y = x->parent;
        while (y != NIL_NODE && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }
}

void RBT::del(int key)
{
    Node *z = search(key);

    if (z == NIL_NODE)
    {
        cout << "key doesn't exist!" << endl;
    } else
    {
        Node *y = NIL_NODE;
        Node *x = NIL_NODE;

        if (z->left == NIL_NODE || z->right == NIL_NODE)
        {
            y = z;
        } else
        {
            y = get_successor(z);
        }

        if (y->left != NIL_NODE)
        {
            x = y->left;
        } else
        {
            x = y->right;
        }

        x->parent = y->parent;

        if (y->parent == NIL_NODE)
        {
            _root = x;
        } else if (y == y->parent->left)
        {
            y->parent->left = x;
        } else
        {
            y->parent->right = x;
        }

        if (y != z)
        {
            z->key = y->key;
        }

        if (y->color == BLACK)
        {
            del_fixup(x);
        }

        delete y;
        cout << "deleted" << endl;
    }
    return;
}

void RBT::del_fixup(Node *x)
{
    Node *uncle = NIL_NODE;
    if (x->color == RED)
    {
        x->color = BLACK;
    } else
    {
        while (x->color == BLACK && x != _root)
        {
            if (x == x->parent->left)
            {
                uncle = x->parent->right;

                if (uncle->color == RED)//case1
                {
                    uncle->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    uncle = x->parent->right;
                } else
                {
                    if (uncle->left->color == BLACK && uncle->right->color == BLACK)//case2
                    {
                        uncle->color = RED;
                        x = x->parent;
                    } else
                    {
                        if (uncle->right->color == BLACK)//case3
                        {
                            uncle->left->color = BLACK;
                            uncle->color = RED;
                            right_rotate(uncle);
                            uncle = x->parent->right;
                        }
                        uncle->color = x->parent->color;//case4
                        x->parent->color = BLACK;
                        uncle->right->color = BLACK;
                        left_rotate(x->parent);
                        x = _root;
                    }
                }
            } else
            {
                uncle = x->parent->left;

                if (uncle->color == RED)//case5
                {
                    uncle->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    uncle = x->parent->left;
                } else
                {
                    if (uncle->left->color == BLACK && uncle->right->color == BLACK)//case6
                    {
                        uncle->color = RED;
                        x = x->parent;
                    } else
                    {
                        if (uncle->left->color == BLACK)//case7
                        {
                            uncle->right->color = BLACK;
                            uncle->color = RED;
                            left_rotate(uncle);
                            uncle = x->parent->left;
                        }
                        uncle->color = x->parent->color;//case8
                        x->parent->color = BLACK;
                        uncle->left->color = BLACK;
                        right_rotate(x->parent);
                        x = _root;
                    }
                }
            }
        }
    }
    _root->color = BLACK;

    return;
}


void RBT::print(Node *w, int l)
{
    if (w != nullptr && w != NIL_NODE)
    {
        print(w->right, l + 1);
        for (int i = 0; i < l; i++)
            cout << "  ";
        cout << w->key;
        if (w->color == BLACK)
            cout << 'b' << endl;
        else
            cout << 'r' << endl;
        print(w->left, l + 1);
    }
}

// EOF
