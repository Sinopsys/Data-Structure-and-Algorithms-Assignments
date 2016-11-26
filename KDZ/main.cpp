#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>

#define BYTE 8

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

    ~Node()
    {
        delete _left;
        delete _right;
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
Node *root;
map<char, int> freq;


map<char, int> getFreq(vector<char> vec)
{
    map<char, int> m;
    for (const auto &x: vec)
        m[x]++;
    return m;
}

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


void buildTree(map<char, int> table)
{
    list<Node *> lst;
    for (auto itr = table.begin(); itr != table.end(); ++itr)
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
    code.clear();
    root = lst.front();
    table.clear();
    buildTable(root);

    lst.clear();
}


vector<char> getSymbols(string path)
{
    vector<char> list;
    ifstream inputFile(path, std::ios::binary);

    while (!inputFile.eof())
        list.push_back((char) inputFile.get());

    list.pop_back();
    inputFile.close();
    return list;
}


void encodeHuff(string in, string out)
{
    ifstream file_in(in);
    ofstream output(out, std::ios::binary);

    vector<char> symbols = getSymbols(in);

    // case of 1 letter
    if (symbols.size() == 1)
    {
        int n = 1;
        output.write(((char *) &n), sizeof(int));
        char c;
        c = (char) file_in.get();
        output.write((&c), sizeof(char));
        return;
    }

    freq = getFreq(symbols);
    buildTree(freq);

    int len_msg = (int) symbols.size();
    output.write(((char *) &len_msg), sizeof(int));

    int len_freq = (int) freq.size() * 2;
    output.write(((char *) &len_freq), sizeof(int));


    for (auto i = freq.begin(); i != freq.end(); ++i)
    {
        output.write(((char *) &i->first), sizeof(char));
        output.write(((char *) &i->second), sizeof(int));
    }


    int count = 0;
    char buf = 0;


    while (!file_in.eof())
    {
        char c = (char) file_in.get();
        vector<bool> x = table[c];
        for (const auto &i:x)
        {
            buf = buf | i << (BYTE - count - 1);
            count++;
            if (count == 8)
            {
                count = 0;
                output << buf;
                buf = 0;
            }
        }
    }
    if (count != 0)
        output << buf;

    file_in.close();
    output.close();

    symbols.clear();
}


void decodeHuff(string src, string dest)
{
    ifstream from(src, std::ios::binary);
    ofstream de(dest);
    string res;

    int len_msg;
    from.read(((char *) &len_msg), sizeof(int));

    // case of 1 letter
    if (len_msg == 1)
    {
        char c;
        from.read((&c), sizeof(char));
        de << c;
        return;
    }

    int len_freq;
    from.read(((char *) &len_freq), sizeof(int));

    map<char, int> m;
    for (int i = 0; i < len_freq / 2; ++i)
    {
        char tmp_char;
        int tmp_int;
        from.read((&tmp_char), sizeof(char));
        from.read(((char *) &tmp_int), sizeof(int));
        m[tmp_char] = tmp_int;
    }

//    for (const auto &i:m)
//    {
//        cout << i.first << ':' << i.second << endl;
//    }

    buildTree(m);
    Node *p = root;

    int count = 0;
    char byte;
    byte = (char) from.get();
    while (!from.eof())
    {
        bool b = (bool) (byte & (1 << (BYTE - count++ - 1)));
        if (b)
            p = p->get_right();
        else
            p = p->get_left();
        if (p->get_left() == nullptr && p->get_right() == nullptr)
        {
            res += p->get_c();
            p = root;
        }
//        ++count;
        if (count == BYTE)
        {
            count = 0;
            byte = (char) from.get();
        }
    }

    de.write(res.c_str(), len_msg);

    from.close();
    de.close();
}


int main()
{
    int choice;

    cout << "1.File archiving " << endl;
    cout << "2.De-archive the file \n" << endl;
    cout << "Make your choice: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            encodeHuff("input.txt", "output.bin");
            cout << "\nFile was saved with name: 'output.bin' \n" << endl;
            cout << "..exiting.." << endl;
            break;
        case 2:
            decodeHuff("output.bin", "out.txt");
            cout << "\nDe-archiving successful \nFile was saved with name: 'out.txt' \n" << endl;
            cout << "..exiting.." << endl;
            break;
        default:
            cout << "\nYou made a wrong choice!" << endl;
            cout << "..exiting.." << endl;
            break;
    }

    return 0;
}

// EOF
