#include <iostream>
#include <vector>
#include <list>
#include <map>

using std::string;
using std::vector;
using std::list;
using std::map;
using std::cout;
using std::cin;
using std::endl;

class Node
{
public:
    int a;
    char c;
    Node *left, *right;
};

int main()
{
    string s = "asdaaaaadds";
    map<char, int> m;
    for (int i = 0; i < s.length(); ++i)
    {
        char c = s[i];
        ++m[c];
    }

    map<char, int>::iterator itr;
    for (itr = m.begin(); itr != m.end(); ++itr)
    {
        cout << itr->first << ": " << itr->second << endl;
    }
    return 0;
}