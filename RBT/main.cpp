#include <iostream>
#include "RBT.h"

int main()
{
    int count = 10;
    RBT a;
    int key;
    std::string value;
    for (int i = 0; i < count; ++i)
    {
        std::cin >> key;
        a.insert(key);
        a.print(a.getRoot(), 1);
    }
    for (int i = 0; i < count; i++)
    {
        std::cin >> key;
        a.del(key);
        a.print(a.getRoot(), 1);
    }
    return 0;
}

// EOF
