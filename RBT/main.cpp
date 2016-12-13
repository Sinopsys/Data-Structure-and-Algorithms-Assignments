#include <iostream>

using std::cin;
using std::cout;
using std::endl;


enum Color
{
    RED = 0,
    BLACK = 1
};

template<class T>
struct Node
{
    Node *left, *right, *parent;
    int key;
    T value;
    Color color;

    void delete_node()
    {
        if (left != NULL)
            left->delete_node();
        if (right != NULL)
            right->delete_node();
        if (parent == NULL)
            delete parent;
    }
};

template<class T>
class RBT
{
private:
    Node<T> *_root;
public:
    Node<T> *getRoot()
    {
        return _root;
    }

    RBT()
    {
        _root = 0;
    }

    static Node<T> *new_node(int key, T value);

    void left_rotate(Node<T> *x);

    void right_rotate(Node<T> *y);

    void insert(int key, T value);

    void insert_fixup(Node<T> *x);

    void del(int key);

    void del_fixup(Node<T> *x);

    Node<T> *get_successor(Node<T> *x);

    Node<T> *search(int key);

    void print(Node<T> *w, int l);

    void delete_tree();
};

template<class T>
// assign "" to the 5th parameter is T is a string
//
static Node<T> NIL = {0, 0, 0, 0, 0, BLACK};

#define NIL_NODE (&NIL<T>)

template<class T>
Node<T> *RBT<T>::new_node(int key, T value)
{
    Node<T> *node = new Node<T>();

    node->key = key;
    node->left = NIL_NODE;
    node->right = NIL_NODE;
    node->parent = NIL_NODE;
    node->color = RED;
    node->value = value;
    return node;
}

template<class T>
Node<T> *RBT<T>::search(int key)
{
    if (_root == NIL_NODE)
    {
        return NIL_NODE;
    } else
    {
        Node<T> *x = _root;

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

template<class T>
void RBT<T>::left_rotate(Node<T> *x)
{
    Node<T> *y = x->right;
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

template<class T>
void RBT<T>::right_rotate(Node<T> *y)
{
    Node<T> *x = y->left;
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

template<class T>
void RBT<T>::insert(int key, T value)
{
    Node<T> *z = new_node(key, value);

    if (_root == nullptr || _root == NIL_NODE)
    {
        _root = z;
        _root->color = BLACK;

        cout << "node inserted" << endl;
        return;
    } else
    {
        Node<T> *y = NIL_NODE;
        Node<T> *x = _root;
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
                cout << "key already exists" << endl;
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

template<class T>
void RBT<T>::insert_fixup(Node<T> *z)
{
    Node<T> *y = NIL_NODE;

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

template<class T>
Node<T> *RBT<T>::get_successor(Node<T> *x)
{
    if (x->right != NIL_NODE)
    {
        Node<T> *t = x->right;
        while (t->left != NIL_NODE)
        {
            t = t->left;
        }
        return t;
    } else
    {
        Node<T> *y = x->parent;
        while (y != NIL_NODE && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }
}

template<class T>
void RBT<T>::del(int key)
{
    Node<T> *z = search(key);

    if (z == NIL_NODE)
    {
        cout << "key doesn't exist!" << endl;
    } else
    {
        Node<T> *y = NIL_NODE;
        Node<T> *x = NIL_NODE;

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
        cout << "node deleted" << endl;
    }
    return;
}

template<class T>
void RBT<T>::del_fixup(Node<T> *x)
{
    Node<T> *uncle = NIL_NODE;
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
                // case1 for left
                //
                if (uncle->color == RED)
                {
                    uncle->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    uncle = x->parent->right;
                } else
                {
                    // case2 for left
                    //
                    if (uncle->left->color == BLACK && uncle->right->color == BLACK)
                    {
                        uncle->color = RED;
                        x = x->parent;
                    } else
                    {
                        // case3 for left
                        //
                        if (uncle->right->color == BLACK)
                        {
                            uncle->left->color = BLACK;
                            uncle->color = RED;
                            right_rotate(uncle);
                            uncle = x->parent->right;
                        }
                        // case4 for left
                        //
                        uncle->color = x->parent->color;
                        x->parent->color = BLACK;
                        uncle->right->color = BLACK;
                        left_rotate(x->parent);
                        x = _root;
                    }
                }
            } else
            {
                uncle = x->parent->left;

                // case1 for right
                //
                if (uncle->color == RED)
                {
                    uncle->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    uncle = x->parent->left;
                } else
                {
                    // case2 for right
                    //
                    if (uncle->left->color == BLACK && uncle->right->color == BLACK)
                    {
                        uncle->color = RED;
                        x = x->parent;
                    } else
                    {
                        // case3 for right
                        //
                        if (uncle->left->color == BLACK)
                        {
                            uncle->right->color = BLACK;
                            uncle->color = RED;
                            left_rotate(uncle);
                            uncle = x->parent->left;
                        }

                        // case4 for right
                        //
                        uncle->color = x->parent->color;
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

template<class T>
void RBT<T>::print(Node<T> *w, int l)
{
    if (w != nullptr && w != NIL_NODE)
    {
        print(w->right, l + 1);
        for (int i = 0; i < l; i++)
        {
            cout << "\t";
        }
        cout << w->key << "; " << w->value << "; ";
        if (w->color == BLACK)
        {
            cout << 'b' << endl;
        } else
        {
            cout << 'r' << endl;
        }
        print(w->left, l + 1);
    }
}

template<class T>
void RBT<T>::delete_tree()
{
    _root->delete_node();
}

int main()
{
    int count = 5;
    RBT<int> *a = new RBT<int>();
    int key;
    int value;
    for (int i = 0; i < count; ++i)
    {
        cin >> key;
        cin >> value;
        a->insert(key, value);
        a->print(a->getRoot(), 1);
        cout << endl;
    }
    for (int i = 0; i < count; i++)
    {
        cin >> key;
        a->del(key);
        a->print(a->getRoot(), 1);
        cout << endl;
    }
    a->delete_tree();
    return 0;
}

// EOF
