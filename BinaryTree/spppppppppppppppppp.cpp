// Artem Abramov 151
#include <vector>
#include <stdexcept>

template<typename T>
void BinaryTree<T>::insert(int key, T value) {
    size++;
    Node *nd = new Node(key, value);
    Node *y = nullptr;
    Node *x = head;
    // find place to insert
    while (x) {
        y = x;
        if (key == x->key) throw std::logic_error("Key already exists");
        if (key < x->key) x = x->left;
        else x = x->right;
    }
    // if tree was empty, insert as root
    if (! y) head = nd;
    else {
        // else insert into tree
        if (key < y->key) y->left = nd;
        else y->right = nd;
    }
}


template<typename T>
void BinaryTree<T>::remove(int key) {
    // Need to find these two nodes
    Node *rm = nullptr;
    Node *parent = nullptr;
    // find the node with key and its parent node
    Node *cur = head;
    while (cur) {
        if (key == cur->key) {
            rm = cur;
            break;
        }
        else {
            parent = cur;
            // advance current
            if (key < cur->key) cur = cur->left;
            else cur = cur->right;
        }
    }
    if (rm == nullptr) {
        throw std::logic_error("Given key does not exist");
    }
    // Successor of p
    Node *succ;
    // Parent of succ
    Node *succ_p;
    // when has no left child.
    if (rm->left == nullptr) {
        if (parent == nullptr) head = rm->right;
        else if (rm == parent->left) parent->left = rm->right;
        else parent->right = rm->right;
    }
    // when has no right child
    else if (rm->right == nullptr) {
        if (parent == nullptr) head = rm->left;
        else if (rm == parent->left) parent->left = rm->left;
        else parent->right = rm->left;
    }
    // when has two children.
    // in this case, the succ of node rm cannot have a left child.
    else {
        // find new successor node
        succ = rm->right;
        succ_p = rm;
        while (succ->left != nullptr) {
            succ_p = succ;
            succ = succ->left;
        }
        // move node rm parents to point to node succ.
        if (parent == nullptr) head = succ;
        else if (rm == parent->left) parent->left = succ;
        else parent->right = succ;
        // drop connections to old node succ
        if (succ == succ_p->left) succ_p->left = succ->right;
        else succ_p->right = succ->right;
        // move node succ into position of node rm
        succ->left = rm->left;
        succ->right = rm->right;
    }
    // change size
    delete rm;
    size--;
}

template<typename T>
T BinaryTree<T>::find(int key) {
    Node *cur = head;
    while (cur) {
        if (key == cur->key) return cur->value;
        else if (key < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    throw std::range_error("Key does not exist");
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    using namespace std;
    vector<Node*> stack = vector<Node*>();
    Node *last = nullptr;
    Node *cur = head;
    // travel left
    while (cur) {
        stack.push_back(cur);
        cur = cur->left;
    }
    while (stack.size() > 0) {
        cur = stack[stack.size()-1];
        stack.pop_back();
        // should we expand right
        if (cur->right && (cur->right != last)) {
            stack.push_back(cur);
            cur = cur->right;
            // find leftmost node in right subtree
            while (cur) {
                stack.push_back(cur);
                cur = cur->left;
            }
        }
        else {
            // we just came from there or it does not exist
            delete cur;
            last = cur;
        }
    }
}


template<typename T>
void BinaryTree<T>::TraverseNode(Node *start, T (*func)(T)) {
    if (start) {
        TraverseNode(start->left);
        func(start->value);
        TraverseNode(start->right);
    }
}
