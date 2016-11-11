/**@file
 * =====================================================================================
 *
 *       Filename:  linked_list.cpp
 *
 *    Description:  Implementation for QueenProblem
 *
 *        Version:  1.0
 *        Created:  10/22/2016 12:29:30 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Artem Abramov (aa), tematibr@gmail.com
 *
 * =====================================================================================
 */

#include "linked_list.h"
#include <stdexcept>

/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup static_func Static functions from the header
 *  @{
 */

/**
 * Static factory function to create linked list filled with
 */
LinkedList* LinkedList::create_from_array(int* source, int size) {
    LinkedList* list = new LinkedList();
    // copy elements
    while (size--) list->push_front(source[size]);
    // return new
    return list;
}

/** @} */ // end doxygroup

/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup public_funcs Public functions that must be implemented.
 *  @{
 */

/**
 * Getting node element of the list with specified index
 */
LinkedList::Node* LinkedList::get_node(int index) {
    Node* cur = nullptr;
    if (index > LinkedList::size / 2) {
        // serach from right
        cur = LinkedList::tail;
        // Count the number of steps to backtrack
        int i = LinkedList::size - index - 1;
        while (i--) cur = cur->prev;
    } else {
        // search from left
        cur = LinkedList::head;
        while (index--) cur = cur->next;
    }
    // return node or nullptr if index out of range
    return cur;
}



/**
 * Destructor of the list.
 */
LinkedList::~LinkedList() {
    Node* cur = LinkedList::head;
    if (cur == nullptr) {
        // if there is nothing to clear
        return;
    }
    Node* next = cur->next;
    // travel one by one and erase
    while (next) {
        delete cur;
        cur = next;
        next = cur->next;
    }
    // erase the last one
    delete cur;
}

/**
 * Getting integer element of the list with specified index
 */
int LinkedList::get(int index) {
    if (index < 0 || index > LinkedList::size-1) {
        throw std::out_of_range("Bad index");
    }
    return LinkedList::get_node(index)->value;
}

/**
 * Returns a value of the first element in the list container.
 */
int LinkedList::front() {
    if (LinkedList::size < 1) {
        throw std::logic_error("List is empty");
    }
    return LinkedList::head->value;
}

/**
 * Returns a value of the last element in the list container.
 */
int LinkedList::back() {
    if (LinkedList::size < 1) {
        throw std::logic_error("List is empty");
    }
    return LinkedList::tail->value;
}

/**
 * Add element at the end
 */
void LinkedList::push_back(int value) {
    LinkedList::insert(LinkedList::size, value);
}

/**
 * Add element at the front
 */
void LinkedList::push_front(int value) {
    LinkedList::insert(0, value);
}

/**
 * Delete last element
 */
void LinkedList::pop_back() {
    if (LinkedList::size < 1) {
        throw std::logic_error("List is empty");
    }
    LinkedList::erase(LinkedList::size-1);
}

/**
 * Delete first element
 */
void LinkedList::pop_front() {
    if (LinkedList::size < 1) {
        throw std::logic_error("List is empty");
    }
    LinkedList::erase(0);
}

/**
 * The container is extended by inserting new elements before the element at the specified position.
 */
void LinkedList::insert(int index, int value) {
    if (index < 0 || index > LinkedList::size) {
        throw std::out_of_range("Bad index");
    }
    // list has no elements
    if (LinkedList::tail == nullptr && LinkedList::head == nullptr) {
        // make new node
        LinkedList::tail = new Node(value);
        // set up head as well
        LinkedList::head = LinkedList::tail;
        LinkedList::size++;
        return;
    }
    // must actually prepend element to list
    if (index == 0) {
        // if no, prev member, than its start node
        Node* headnew = new Node(value);
        headnew->prev = nullptr;
        headnew->next = LinkedList::head;
        // set up the change of head
        LinkedList::head->prev = headnew;
        LinkedList::head = headnew;
        // change size
        LinkedList::size++;
    } else if (index == LinkedList::size) {
        // becasue the "node" insert(), actually does post-insert
        LinkedList::insert(LinkedList::tail, value);
    } else {
        // find the node by index
        Node* after_node = LinkedList::get_node(index);
        // because the "node" insert(), actually does post-insert
        LinkedList::insert(after_node->prev, value);
    }
}

/**
 * Removes from the list container a single element (position)
 */
void LinkedList::erase(int index) {
    if (index < 0 || index > LinkedList::size-1) {
        throw std::out_of_range("Bad index");
    }
    // find the node to erase
    Node* node = LinkedList::get_node(index);
    // if not null, erase it
    if (node) LinkedList::erase(node);
}

/**
 * The container is extended by inserting new elements after the element at the specified position.
 */
void LinkedList::insert(Node* prev, int value) {
    // make new
    Node* node = new LinkedList::Node(value);
    // connect this, "new node should be located between prev and prev->next"
    node->prev = prev;
    node->next = prev->next;
    // rewire others,
    if (prev->next) prev->next->prev = node;
    prev->next = node;
    // if this is tail, we need extra logic, make new tail
    if (prev == LinkedList::tail) LinkedList::tail = node;
    LinkedList::size++;
}

/**
 * Removes from the list container a single element (position)
 */
void LinkedList::erase(Node* node) {
    // clear side nodes
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    // if this is tail or head, we need extra logic
    if (node == LinkedList::tail) LinkedList::tail = node->prev;
    if (node == LinkedList::head) LinkedList::head = node->next;
    // clear the current node
    delete node;
    LinkedList::size--;
}

/**
 * Returning size of the list, i.e. number of elements in the list.
 */
int LinkedList::get_size() {
    return LinkedList::size;
}

/**
 * Test whether container is empty
 */
bool LinkedList::empty() {
    return LinkedList::size == 0;
}

/**
 * Removes all elements from the list container (which are destroyed), and leaving the container with a size of 0.
 */
void LinkedList::clear() {
    while(LinkedList::size) LinkedList::pop_back();
}

/**
 * Sorts the elements in the list.
 */
void LinkedList::sort() {
    Node* start = LinkedList::head;
    Node *left, *right, *e, *end;
    int insize = 1;
    int nmerges, lsize, rsize, i;
    // check if anything to sort
    if (start == nullptr) {
        return;
    }
    while (true) {
        left = start;
        start = nullptr;
        end = nullptr;
        //  count number of merges we must do later (in this round)
        nmerges = 0;
        while (left) {
            // there is a merge to do
            nmerges++;
            // step insize places along from left
            right = left;
            lsize = 0;
            for (i = 0; i < insize; i++) {
                lsize++;
                right = right->next;
                if (right == nullptr) break;
            }

            // if right hasn't fallen off end, we have two lists to merge
            rsize = insize;

            // now we have two lists; merge them
            while (lsize > 0 || (rsize > 0 && right)) {

                // decide whether next element of merge comes from left or right
                if (lsize == 0) {
                    // left is empty; e must come from right.
                    e = right;
                    right = right->next;
                    rsize--;
                } else if (rsize == 0 || !right) {
                    // right is empty; e must come from left.
                    e = left;
                    left = left->next;
                    lsize--;
                } else if ((left->value - right->value) <= 0) {
                    // First element of left is lower (or same), e must come from left.
                    e = left;
                    left = left->next;
                    lsize--;
                } else {
                    // First element of right is lower; e must come from right.
                    e = right;
                    right = right->next;
                    rsize--;
                }

                // add the next element to the merged start
                if (end) {
                    end->next = e;
                } else {
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
        if (nmerges <= 1) {
            LinkedList::head = start;
            Node* cur = start;
            while (cur->next) cur=cur->next;
            LinkedList::tail = cur;
            return;
        }
        // Otherwise repeat, merging lists twice the size
        insize *= 2;
    }
}

/**
 * Returns first index at the list which contains such value
 */
int LinkedList::find_first(int value) {
    Node* cur = LinkedList::head;
    int index = 0;
    while (cur) {
        if (cur->value == value) return index;
        cur = cur->next;
        index++;
    }
    // the comment to the function says: "Should returns tail in case if it is no such value in list"
    // Since we can not return "tail", we return the size
    // In my opinion this function should return -1, when the element is not found
    return LinkedList::size;
}

/** @} */ // end doxygroup
