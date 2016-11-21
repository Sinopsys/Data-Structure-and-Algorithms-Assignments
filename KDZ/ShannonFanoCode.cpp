//
// Created by kirill on 13.11.16.
//

#include "ShannonFanoCode.h"
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <codecvt>
#include "Table.h"
#include "SFNode.h"

using std::map;
using std::list;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;


void printSFNode(SFNode in_symbols)
{
    cout << "symbols: " << in_symbols.getsymbols();
    cout << " Freq: " << in_symbols.getFrequency();
    cout << " Code: ";
    for (int i = 0; i < in_symbols.getCode().size(); ++i)
    {
        cout << in_symbols.getCode()[i];
    }
    cout << endl;
}

void ShannonFanoCode::encode(int in_begin, int in_end)
{
    if (in_begin >= in_end)
    {
        return;
    }

    if (in_begin == in_end - 1)
    {
        symbols[in_begin].addCode(0);
        symbols[in_end].addCode(1);
        return;
    }

    int highPtr = in_begin; // highPtr will go downward
    int lowPtr = in_end;
    int highSum = symbols[highPtr].getFrequency();
    int lowSum = symbols[lowPtr].getFrequency();

    // move the highPtr down and lowPtr up until highSum and lowSum close
    while (highPtr != lowPtr - 1)
    {
        if (highSum > lowSum)
        {
            lowPtr--;
            lowSum += symbols[lowPtr].getFrequency();
        } else
        {
            highPtr++;
            highSum += symbols[highPtr].getFrequency();
        }
    }

    int i;
    for (i = in_begin; i <= highPtr; i++)
    {
        symbols[i].addCode(0);
    }
    for (i = lowPtr; i <= in_end; i++)
    {
        symbols[i].addCode(1);
    }

    encode(in_begin, highPtr);
    encode(lowPtr, in_end);
}


void ShannonFanoCode::decode(string src, string dest)
{

}

ShannonFanoCode::~ShannonFanoCode()
{

}

void ShannonFanoCode::proceed()
{
    map<char, int> m;
    ifstream myfile("input.txt");
    char c;
    while (!myfile.eof())
    {
        char tmp = (char) myfile.get();
        if (tmp != EOF)
            c = tmp;
        else
            break;
        ++m[c];
    }

    list<SFNode> lst;
    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        SFNode tmp;
        tmp.set_c(itr->first);
        tmp.set_n(itr->second);
        lst.push_back(tmp);
    }
    lst.sort(Compare());

    std::vector<SFNode> v{std::make_move_iterator(std::begin(lst)),
                          std::make_move_iterator(std::end(lst))};

    symbols = v;

    encode(0, (int) symbols.size() - 1);

    printf("\n\n");
    for_each(symbols.begin(), symbols.end(), printSFNode);

}
