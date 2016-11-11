//
// Created by kirill on 01.11.16.
//

#include "linked_list.h"
#include <stdexcept>

using std::out_of_range;
using std::logic_error;

LinkedList::Node *LinkedList::get_node(int index)
{
    Node *current = head;
    int count = 0;
    // go through the list
    while (current != NULL)
    {
        if (count == index)
            return (current);
        ++count;
        current = current->next;
    }
    return nullptr;
}

LinkedList *LinkedList::create_from_array(int *source, int size)
{
    LinkedList *lsit = new LinkedList();
    // copy from array
    for (int i = 0; i < size; ++i)
    {
        lsit->push_back(source[i]);
    }
    return lsit;
}

LinkedList::~LinkedList()
{
    // create a temp node to store the next
    Node *temp = nullptr;
    while (head != nullptr)
    {
        temp = head->next;
        // delete the prev node
        delete head;
        // update
        head = temp;
    }
    delete temp;
}

int LinkedList::get(int index)
{
    if (!(index >= 0 && index <= size))
    {
        throw out_of_range("Index out of bounds");
    }
    int res = get_node(index)->value;
    return res;
}

int LinkedList::front()
{
    int size = LinkedList::size;
    Node *head = LinkedList::head;
    if (size <= 0)
    {
        throw logic_error("Logic error: empty list.");
    }
    return head->value;
}

int LinkedList::back()
{
    int size = LinkedList::size;
    Node *tail = LinkedList::tail;
    if (size <= 0)
    {
        throw logic_error("Logic error: empty list.");
    }
    return tail->value;
}

void LinkedList::push_back(int value)
{
    insert(LinkedList::size, value);
}

void LinkedList::push_front(int value)
{
    insert(0, value);
}

void LinkedList::pop_back()
{
    int size = LinkedList::size;
    if (size <= 0)
    {
        throw logic_error("Logic error: empty list.");
    }
    erase(size - 1);
}

void LinkedList::pop_front()
{
    int size = LinkedList::size;
    if (size <= 0)
    {
        throw logic_error("Logic error: empty list.");
    }
    erase(0);
}

void LinkedList::insert(int index, int value)
{
    if (!(index >= 0 && index <= LinkedList::size))
    {
        throw out_of_range("Index out of bounds");
    }
    if (!LinkedList::tail && !LinkedList::head)
    {
        Node *newNode = new Node(value);
        LinkedList::tail = newNode;
        LinkedList::head = LinkedList::tail;
        ++LinkedList::size;
        return;
    }
    // when we need to add it to the front
    if (index == 0)
    {
        Node *newNode = new Node(value);
        newNode->prev = nullptr;
        Node *head = LinkedList::head;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        LinkedList::head = head;
        ++LinkedList::size;
    }
        // to the end
    else if (index == LinkedList::size)
    {
        LinkedList::insert(LinkedList::tail, value);
    }
        // otherwise
    else
    {
        Node *newNode = LinkedList::get_node(index);
        LinkedList::insert(newNode->prev, value);
    }
}

void LinkedList::erase(int index)
{
    if (!(index >= 0 && index <= LinkedList::size))
    {
        throw out_of_range("Index out of bounds");
    }
    // just erase the node
    LinkedList::erase(get_node(index));
}

void LinkedList::insert(LinkedList::Node *prev, int value)
{
    // new temp node
    Node *newNdoe = new LinkedList::Node(value);
    Node *tail = LinkedList::tail;

    // initialize it to be bwtween prev and netx
    newNdoe->prev = prev;
    newNdoe->next = prev->next;


    if (prev->next != nullptr)
    {
        (*prev->next).prev = newNdoe;
    }

    prev->next = newNdoe;
    if (prev == tail)
    {
        tail = newNdoe;
    }

    if (tail != nullptr)
    {
        LinkedList::tail = tail;
    }
    ++LinkedList::size;
}

void reassign(LinkedList::Node *src, LinkedList::Node *dest)
{
    dest->next = src->next;
    dest->prev = src->prev;
    dest->value = src->value;
}

void LinkedList::erase(LinkedList::Node *node)
{
    Node *tail = LinkedList::tail;
    Node *hrad = LinkedList::head;

// clear data
    if (node->prev != nullptr)
    {
        (*node->prev).next = node->next;
    }
    if (node->next)
    {
        (*node->next).prev = node->prev;
    }
    if (node == tail)
    {
        tail = node->prev;
    }
    if (node == hrad)
    {
        hrad = node->next;
    }
    LinkedList::tail = tail;
    LinkedList::head = hrad;

    delete node;
    --LinkedList::size;
}

int LinkedList::get_size()
{
    return LinkedList::size;
}

bool LinkedList::empty()
{
    return LinkedList::size == 0;
}

void LinkedList::clear()
{
    while (LinkedList::size != 0)
    {
        LinkedList::pop_back();
    }

}

void LinkedList::sort()
{
    Node *curr = head;
    Node *next;
    while (curr != nullptr && curr->next != nullptr)
    {
        next = curr->next;
        while (next)
        {
            if (curr->value > next->value)
            {
                std::swap(next->value, curr->value);
            }
            next = next->next;
        }
        curr = curr->next;
    }
}

int LinkedList::find_first(int value)
{
    Node *head = LinkedList::head;
    int count = 0;
    bool res = false;
    while (head != nullptr)
    {
        if (head->value == value)
        {
            res = true;
            break;
        };
        head = head->next;
        ++count;
    }
    return res ? count : LinkedList::size;
}

// EOF
