//
// Created by Nikita Marinosyan on 04.11.16.
//

#include "linked_list.h"
#include <cstdlib>
using namespace std;

LinkedList::Node* LinkedList::get_node(int index) {
    Node* current;
    if(size/2 < index) {
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
    }
    else {
        current = tail;
        for (int i = 0; i < size - index + 1; ++i) {
            current = current->prev;
        }
    }
    return current;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::push_back(int value) {

    if (tail != nullptr) {
        Node *new_node = new Node(value);
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    else {
        head = new Node(value);
        tail = head;
    }
    size += 1;
}

void LinkedList::clear() {
    Node* n = head;
    Node* new_n;
    while(n != nullptr) {
        new_n = n->next;
        delete n;
        n = new_n;
    }
    size = 0;
    tail = nullptr;
    head = nullptr;
}

LinkedList* LinkedList::create_from_array(int *source, int size) {

    LinkedList* linkedList;
    for (int i = 0; i < size; ++i) {
        linkedList->push_back(source[i]);
    }
    return linkedList;
}



