//
// Created by kirill on 22.11.16.
//

#include "SFNode.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;

SFNode::SFNode(char in_symbol, int in_frequency)
{
    symbol = in_symbol;
    frequency = in_frequency;
}

char SFNode::getsymbols(void)
{
    return symbol;
}

int SFNode::getFrequency(void)
{
    return frequency;
}

vector<bool> SFNode::getCode(void)
{
    return _code;
}

void SFNode::addCode(bool in_code)
{
    _code.push_back(in_code);
}

void SFNode::set_c(char c)
{
    symbol = c;
}

void SFNode::set_n(int n)
{
    frequency = n;
}
