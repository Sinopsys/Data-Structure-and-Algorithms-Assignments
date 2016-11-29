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


//region Huffnan helpers
/**
 * Node class for Huffman algo
 */
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

/**
 * Comparator for Nodes in Huffman algo
 */
struct Compare
{
    bool operator()(Node *l, Node *r) const
    {
        return l->get_n() < r->get_n();
    }
};

//
// a temp vector
vector<bool> code;
//
// root Node for Huffman tree
Node *root;
//
// table of frequencies (for Huffman)
map<char, int> freq;
//endregion


//region SF helpers
struct node
{
    char ch;
    float p;
};

static int node_compare(const void *n1, const void *n2)
{
    const node a = *(node *) n1;
    const node b = *(node *) n2;
    if (a.p < b.p) return 1;
    else if (a.p > b.p) return -1;
    return 0;
}

int probTableSize;
node *probTable;
//endregion


map<char, vector<bool> > table;


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


void shannonFano(int start, int stop)
{
    int i, splitIndex;
    float prob, fullProb, halfProb;

    if (start == stop)
    {
        return;
    } else if (stop - start == 1)
    {
        table[probTable[start].ch].push_back(0);
        table[probTable[stop].ch].push_back(1);
    } else
    {
        fullProb = 0;
        for (i = start; i <= stop; ++i)
        {
            fullProb += probTable[i].p;
        }
        prob = 0;
        splitIndex = -1;
        halfProb = fullProb * 0.5f;
        for (i = start; i <= stop; ++i)
        {
            prob += probTable[i].p;
            if (prob <= halfProb)
            {
                table[probTable[i].ch].push_back(0);
            } else
            {
                table[probTable[i].ch].push_back(1);
                if (splitIndex < 0)
                { splitIndex = i; }
            }
        }
        if (splitIndex < 0)
        {
            splitIndex = start + 1;
        }

        shannonFano(start, splitIndex - 1);
        shannonFano(splitIndex, stop);
    }
}


void encodeSF(string in, string out)
{
    map<char, int> freqs;
    ifstream inp(in);

    char ch;
    int total = 0;
    while ((ch = (char) inp.get()) != EOF)
    {
        freqs[ch]++;
        total++;
    }
    probTableSize = (int) freqs.size();

    probTable = new node[probTableSize];
    float ftot = float(total);

    int i = 0;
    for (auto fi = freqs.begin(); fi != freqs.end(); ++fi, ++i)
    {
        probTable[i].ch = fi->first;
        probTable[i].p = float(fi->second) / ftot;
    }
    qsort(probTable, (size_t) probTableSize, sizeof(node), node_compare);

    shannonFano(0, probTableSize - 1);

    ofstream outp(out, std::ios::binary | std::ios::out);

    outp.write(((char *) &total), sizeof(int));

    outp.write(((char *) &probTableSize), sizeof(int));

    for (i = 0; i < probTableSize; i++)
    {
        outp.write((&probTable[i].ch), sizeof(char));
        outp.write(((char *) &probTable[i].p), sizeof(float));
    }

    inp.clear();
    inp.seekg(0);

    int count = 0;
    char buf = 0;
    while (!inp.eof())
    {
        char c = (char) inp.get();
        vector<bool> x = table[c];
        for (const auto &xx:x)
        {
            buf = buf | xx << (BYTE - count - 1);
            count++;
            if (count == BYTE)
            {
                count = 0;
                outp << buf;
                buf = 0;
            }
        }
    }
    if (count != 0)
        outp << buf;


    table.clear();
    delete[] probTable;

    outp.close();
    inp.close();
}

bool isInTable(vector<bool> in)
{
    for (const auto &i:table)
    {
        if (i.second == in)
            return true;
    }
    return false;
}

char getchar(vector<bool> in)
{
    for (const auto &i : table)
    {
        if (i.second == in)
            return i.first;
    }
    return -1;
}

void decodeSF(string from, string dest)
{
    char ch;
    float p;
    int total;
    int tsize;

    ifstream fr(from, std::ios::binary | std::ios::in);


    fr.read((char *) (&total), sizeof(int));
    fr.read((char *) (&tsize), sizeof(int));


    probTable = new node[tsize];
    for (int i = 0; i < tsize; i++)
    {
        fr.read((&ch), sizeof(char));
        fr.read((char *) (&p), sizeof(float));
        probTable[i].ch = ch;
        probTable[i].p = p;
    }

    shannonFano(0, tsize - 1);


    ofstream de(dest, std::ios::binary | std::ios::out);

    string accum = "";

    string res = "";

    int count = 0;
    char byte;
    byte = (char) fr.get();
    vector<bool> tmp;
    while (!fr.eof())
    {
        bool b = (bool) (byte & (1 << (BYTE - count++ - 1)));
        if (b)
            tmp.push_back(1);
        else
            tmp.push_back(0);
        if (isInTable(tmp))
        {
            res += getchar(tmp);
            tmp.clear();
        }
        if (count == BYTE)
        {
            count = 0;
            byte = (char) fr.get();
        }
    }

    de.write(res.c_str(), total);


    de.close();
    fr.close();
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
