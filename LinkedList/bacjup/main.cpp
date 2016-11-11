#include "linked_list.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

//
//33 36 27 15 43 35
//-1
//100
//-1 1 1 5 33 54 55 100

int main()
{
    // Array
    int n = 6;
    int *arr = new int[n];
    for (int j = 0; j < n; ++j)
        arr[j] = rand() % 50;
//    for (int k = 0; k < n; ++k)
//        cout << arr[k] << " ";
//    cout << endl;

    // List #0
    LinkedList *list = LinkedList::create_from_array(arr, n);
    for (int i = 0; i < list->get_size(); ++i)
        cout << list->get(i) << " ";
    cout << endl;

    // List #1
    list->clear();
//    list->insert(0, 15);
//    list->insert(list->get_node(0), 8);
//    list->insert(0, 4);
    list->push_back(5);
    list->push_front(1);
    list->insert(list->get_size(), 33);
    list->insert(list->get_size() - 1, -1);
    list->insert(0, 55);
    list->insert(list->get_size(), 100);
    list->insert(list->get_node(0), 54);
    list->sort();
    list->push_back(1);
    list->sort();
    cout << list->front() << " " << endl;
    cout << list->back() << " " << endl;
    for (int i = 0; i < list->get_size(); ++i)
    {
        cout << list->get(i) << " ";
    }
    cout << endl;
    cout << list->find_first(1) << " " << endl;
    delete list;
    return 0;
}