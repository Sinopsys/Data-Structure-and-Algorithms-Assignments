#include <cstdlib>
#include "binary_tree.h"
//
// Created by kirill on 11.11.16.
//

template<class T>
T BinaryTree<T>::find(int key)
{
    if (head == NULL || key == head->key)
    {
        return head;
    }
    if (key < head->key)
    {
        head = head->left;
        return find(key);
    } else
    {
        head = head->right;
        return find(key);
    }
}

template<class T>
void BinaryTree::insert(int key, T value)
{
    key = NULL;

}

template<class T>
void BinaryTree::remove(int key)
{

}

template<class T>
BinaryTree::~BinaryTree()
{

}

template<class T>
void BinaryTree::TraverseNode(BinaryTree::Node *start, T (*func)(T))
{

}


/**
 *     EOF
 */
