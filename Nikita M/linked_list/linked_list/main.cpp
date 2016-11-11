#include <iostream>
#include "linked_list.h"

int main() {
    int source[5] = {1,2,3,4,5};
    LinkedList::create_from_array(source, 5);
    return 0;
}