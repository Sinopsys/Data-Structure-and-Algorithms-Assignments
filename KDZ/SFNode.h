//
// Created by kirill on 22.11.16.
//

#ifndef KDZ_SFNODE_H
#define KDZ_SFNODE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;

class SFNode
{
private:
    char symbol;
    int frequency;
    vector<bool> _code;
public:
    SFNode(char in_symbol, int in_frequency);

    SFNode(){}

    void set_c(char c);

    void set_n(int n);

    char getsymbols(void);

    int getFrequency(void);

    vector<bool> getCode(void);

    void addCode(bool in_code);
};


#endif //KDZ_SFNODE_H
