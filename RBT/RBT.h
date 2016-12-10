////
//// Created by kirill on 09.12.16.
////
//
//#ifndef RBT_RBT_H
//#define RBT_RBT_H
//
//enum Color
//{
//    RED = 0,
//    BLACK = 1
//};
//
//struct Node
//{
//    Node *left, *right, *parent;
//    int key;
//    Color color;
//};
//
//class RBT
//{
//private:
//    Node *_root;
//public:
//    Node *getRoot()
//    {
//        return _root;
//    }
//
//    RBT()
//    {
//        _root = 0;
//    }
//
//    static Node *new_node(int key);
//
//    void left_rotate(Node *x);
//
//    void right_rotate(Node *y);
//
//    void insert(int key);
//
//    void insert_fixup(Node *x);
//
//    void del(int key);
//
//    void del_fixup(Node *x);
//
//    Node *get_successor(Node *x);
//
//    Node *tree_min(Node *x);
//
//    Node *search(int key);
//
//    void print(Node *w, int l);
//
//};
//
//#endif //RBT_RBT_H
//
//// EOF
