#include <iostream>
#include "HuffmanCode.h"
#include "ShannonFanoCode.h"

using std::cin;
using std::cout;
using std::string;

int main()
{
    bool good_input = false;
    unsigned char x;

    while (!good_input)
    {
        cout << string(50, '\n');
        cout << "Huffman (0) / Shannon - Fano (1):\t";
        cin >> x;
        if (!(x == '1' || x == '0'))
        {
            good_input = false;
            continue;
        }
        good_input = true;
    }

    HuffmanCode *hc = nullptr;
    ShannonFanoCode *sf = nullptr;
    if (x == '0')
    {
        hc = new HuffmanCode();
        hc->encode("input.txt", "output.bin");
        hc->decode("output.bin", "decoded.txt");
    } else
    {
        sf = new ShannonFanoCode();
        sf->proceed();
    }

    delete hc;
//    delete sf;
    return 0;
}
