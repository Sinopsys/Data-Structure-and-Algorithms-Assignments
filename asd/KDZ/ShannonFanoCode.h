//
// Created by kirill on 13.11.16.
//

#ifndef KDZ_SHANNONFANOCODE_H
#define KDZ_SHANNONFANOCODE_H


#include "Node.h"
#include "SFNode.h"
#include <string>

using std::string;

class ShannonFanoCode
{
private:
    struct Compare
    {
        bool operator()(SFNode l, SFNode r) const
        {
            return l.getFrequency() > r.getFrequency();
        }
    };
    vector<SFNode> symbols;
public:
    void encode(int in_begin, int in_end);

    void decode(string src, string dest);

    void proceed();


    ~ShannonFanoCode();
};


#endif //KDZ_SHANNONFANOCODE_H
