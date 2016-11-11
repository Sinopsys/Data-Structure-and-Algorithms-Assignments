//
// Created by kirill on 01.11.16.
//

#include "linked_list.h"
#include <stdexcept>

using std::out_of_range;
using std::logic_error;

LinkedList::Node *LinkedList::get_node(int index)
{
    Node *cur;
    Node *head = LinkedList::head;
    Node *tail = LinkedList::tail;
    int size = LinkedList::size;
    if (index <= size / 2)
    {
        cur = head;
        while (index != 0)
        {
            cur = cur->next;
            --index;
        }
    } else
    {
        cur = tail;
        int i = size - index - 1;
        while (i != 0)
        {
            cur = cur->prev;
            --i;
        }
    }
    return cur;
}

LinkedList *LinkedList::create_from_array(int *source, int size)
{
    LinkedList *lsit = new LinkedList();
    while (size != 0)
    {
        lsit->push_front(source[size]);
        --size;
    }
    return lsit;
}

LinkedList::~LinkedList()
{
    Node *cur = LinkedList::head;
    while (cur->next != nullptr)
    {
        delete cur;
        cur = cur->next;
    }
    delete cur;
}

int LinkedList::get(int index)
{
    if (!(index >= 0 && index <= LinkedList::size))
    {
        throw out_of_range("Index out of bounds");
    }
    int res = LinkedList::get_node(index)->value;
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
    LinkedList::insert(LinkedList::size, value);
}

void LinkedList::push_front(int value)
{
    LinkedList::insert(0, value);
}

void LinkedList::pop_back()
{
    int size = LinkedList::size;
    if (size <= 0)
    {
        throw logic_error("Logic error: empty list.");
    }
    LinkedList::erase(size - 1);
}

void LinkedList::pop_front()
{
    int size = LinkedList::size;
    if (size <= 0)
    {
        throw logic_error("Logic error: empty list.");
    }
    LinkedList::erase(0);
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
    if (index == 0)
    {
        Node *newNode = new Node(value);
        newNode->prev = nullptr;
        Node *head = LinkedList::head;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        LinkedList::head = head;
        LinkedList::size++;
    } else if (index == LinkedList::size)
    {
        LinkedList::insert(LinkedList::tail, value);
    } else
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
    LinkedList::erase(LinkedList::get_node(index));
}

void LinkedList::insert(LinkedList::Node *prev, int value)
{
    Node *newNdoe = new LinkedList::Node(value);
    Node *tail = LinkedList::tail;
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
    Node *start = LinkedList::head;
    Node *left, *right, *e, *end;
    int insize = 1;
    int nmerges, lsize, rsize, i;
    // check if anything to sort
    if (start == nullptr)
    {
        return;
    }
    while (true)
    {
        left = start;
        start = nullptr;
        end = nullptr;
        //  count number of merges we must do later (in this round)
        nmerges = 0;
        while (left)
        {
            // there is a merge to do
            nmerges++;
            // step insize places along from left
            right = left;
            lsize = 0;
            for (i = 0; i < insize; i++)
            {
                lsize++;
                right = right->next;
                if (right == nullptr) break;
            }

            // if right hasn't fallen off end, we have two lists to merge
            rsize = insize;

            // now we have two lists; merge them
            while (lsize > 0 || (rsize > 0 && right))
            {

                // decide whether next element of merge comes from left or right
                if (lsize == 0)
                {
                    // left is empty; e must come from right.
                    e = right;
                    right = right->next;
                    rsize--;
                } else if (rsize == 0 || !right)
                {
                    // right is empty; e must come from left.
                    e = left;
                    left = left->next;
                    lsize--;
                } else if ((left->value - right->value) <= 0)
                {
                    // First element of left is lower (or same), e must come from left.
                    e = left;
                    left = left->next;
                    lsize--;
                } else
                {
                    // First element of right is lower; e must come from right.
                    e = right;
                    right = right->next;
                    rsize--;
                }

                // add the next element to the merged start
                if (end)
                {
                    end->next = e;
                } else
                {
                    start = e;
                }

                // Maintain reverse pointers in a doubly linked start.
                e->prev = end;
                end = e;
            }
            // now left has stepped `insize' places along, and right has too
            left = right;
        }

        end->next = NULL;
        // If we have done only one merge, we're finished.
        // allow for nmerges==0, the empty start case
        if (nmerges <= 1)
        {
            LinkedList::head = start;
            Node *cur = start;
            while (cur->next) cur = cur->next;
            LinkedList::tail = cur;
            return;
        }
        // Otherwise repeat, merging lists twice the size
        insize *= 2;
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


