//
// Created by kirill on 05.12.16.
//

#include "kmp.h"
#include <vector>

using std::string;
using std::vector;

// returns helper-vector with info about suffixes that match prefixes
//
vector<int> configure_pattern(string);

std::vector<int> *find_substrings(std::string &source, std::string &substring)
{
    int i = 0, j = 0;
    vector<int> vec = configure_pattern(substring);

    //result vector
    //
    vector<int> *res = new vector<int>;
    while (i != source.length())
    {
        // if it is a match then go to the second pair
        //
        if (substring[j] == source[i])
        {
            ++i;
            ++j;
        }
            // else get j back to the index of prev pos in help vec
            //
        else
        {
            j = vec[j - 1];

            // if it is a match again then move further in the string
            //
            if (substring[j] != source[i])
            {
                ++i;
            }
            continue;
        }
        // found substring!
        //
        if (j == substring.length())
        {
            //
            // add start index of substring
            res->push_back(i - j);
            //
            // add end index of substring
//            res->push_back((int) pattern.length() - 1 + i - j);
        }
    }
    return res;
}

vector<int> configure_pattern(string pattern)
{
    vector<int> vec(pattern.length());

    // first value of the vector is always 0 so i = 1
    //
    int i = 1, j = 0;

    // move through the pattern
    //
    while (i != pattern.length())
    {
        if (pattern[i] == pattern[j])
        {
            // initialize vector's ith position with the length of matching prefix
            //
            vec[i] = j + 1;

            // move to the next letters
            //
            ++i;
            ++j;

            // get j back to the position with the match or to the 0 else
            //
            while (pattern[i] != pattern[j] && j != 0)
            {
                j = vec[j - 1];
            }
        } else
        {
            // if it's not a match the just go to the next letter
            //
            ++i;
        }
    }
    return vec;
}