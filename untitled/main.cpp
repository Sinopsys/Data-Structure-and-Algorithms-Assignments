#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>

using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;

class Node
{
private:
    int _n;
    char _c;
    Node *_left, *_right;
public:
    int get_n()
    { return _n; }

    char get_c()
    { return _c; }

    void set_n(int n)
    { this->_n = n; }

    void set_c(char c)
    { this->_c = c; }

    Node *get_left()
    { return _left; }

    Node *get_right()
    { return _right; }

    Node()
    { _left = _right = nullptr; }

    Node(Node *left, Node *right)
    {
        _left = left;
        _right = right;
        _n = left->_n + right->_n;
    }
};


struct Compare
{
    bool operator()(Node *l, Node *r) const
    {
        return l->get_n() < r->get_n();
    }
};


vector<bool> code;
map<char, vector<bool> > table;

void buildTable(Node *root)
{
    if (root->get_left() != nullptr)
    {
        code.push_back(0);
        buildTable(root->get_left());
    }

    if (root->get_right() != nullptr)
    {
        code.push_back(1);
        buildTable(root->get_right());
    }

    if (root->get_left() == nullptr && root->get_right() == nullptr)
        table[root->get_c()] = code;

    code.pop_back();
}


Node *root;


void encodeHuff(string in, string out)
{

    map<char, int> m;
    ifstream myfile(in);
    char c;
    while (true)
    {
        char tmp = (char) myfile.get();
        if (tmp != EOF)
            c = tmp;
        else
            break;
        ++m[c];
    }


    list<Node *> lst;
    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        Node *tmp = new Node();
        tmp->set_c(itr->first);
        tmp->set_n(itr->second);
        lst.push_back(tmp);
    }

    while (lst.size() != 1)
    {
        lst.sort(Compare());
        Node *tmp_left = lst.front();
        lst.pop_front();
        Node *tmp_right = lst.front();
        lst.pop_front();
        lst.push_front(new Node(tmp_left, tmp_right));
    }

    root = lst.front();
    buildTable(root);


    myfile.clear();
    myfile.seekg(0);

    ofstream output(out);

    int count = 0;
    char buf = 0;

//    for (auto i = table.begin(); i != table.end(); ++i)
//    {
//        cout << i->first << ": ";
//        for (int j = 0; j < i->second.size(); ++j)
//        {
//            cout << i->second[j];
//        }
//        cout << endl;
//    }

    while (!myfile.eof())
    {
        c = (char) myfile.get();
        vector<bool> x = table[c];
        for (int n = 0; n < x.size(); ++n)
        {
            buf = buf | x[n] << (7 - count);
            count++;
            if (count == 8)
            {
                count = 0;
                output << buf;
                buf = 0;
            }
        }
    }

    myfile.close();
    output.close();

    m.clear();
    lst.clear();


}


void decodeHuff(string src, string dest)
{
    ifstream from(src);
    ofstream de(dest);

    Node *p = root;
    int count = 0;
    char byte;
    byte = (char) from.get();
    while (!from.eof())
    {
        bool b = (bool) (byte & (1 << (7 - count)));
        if (b)
            p = p->get_right();
        else
            p = p->get_left();
        if (p->get_left() == nullptr && p->get_right() == nullptr)
        {
            de << p->get_c();
            p = root;
        }
        count++;
        if (count == 8)
        {
            count = 0;
            byte = (char) from.get();
        }
    }
    from.close();
}


int main()
{
    setlocale(LC_ALL, "Russian");
    encodeHuff("input.txt", "output.bin");
    decodeHuff("output.bin", "out.txt");
    return 0;
}


// EOF
