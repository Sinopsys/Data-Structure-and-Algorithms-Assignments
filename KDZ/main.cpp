// region includes, usings, defines..
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <cstring>

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
// endregion

// region Description
/**
 * @TITLE:      КДЗ-1 по дисциплине Алгоритмы и Структуры Данных
 * @STUDENT:    Куприянов Кирилл
 * @GROUP:      БПИ 151
 * @DATE:       28.11.2016
 * @IDE:        CLion 2016.3
 * @OS:         UBUNTU 16.04 LTS
 * @IMPLEMENTED:аргументы командной строки, архив-е и разархив-е
 *              обоими алгоритмами, словом, всё.
 *

 *  How to run: '-d' - dearchive
 *  NOTE: I really think that it's better to write "huff", not "haff", but
 *  I had to, because the task demanded so.
 *  Moreover, I am sure, that Mr.Fano won't like the way I name the extension
 *  of the encoded file ("shan"). If I had a possibility to name the extension as I want to,
 *  I would name it "sf".

 * ./a.out haff input.txt encoded.haff
 * ./a.out haff input.txt
 * ./a.out haff -d encoded.haff
 * ./a.out haff -d encoded.haff decoded.txt
 *
 * ./a.out shan input.txt encoded.shan
 * ./a.out shan input.txt
 * ./a.out shan -d encoded.shan
 * ./a.out shan -d encoded.shan decoded.txt
 */
// endregion

//region Huffnan helpers
/**
 * Node class (for BT) for Huffman algo
 */
class Node
{
private:
    // number of occurrences
    //
    int _n;

    // character
    //
    char _c;

    // pointers to left and right childs
    //
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

    // default ctor
    //
    Node()
    { _left = _right = nullptr; }

    //ctor to initialize left and right child nodes
    //
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
// temp vector
vector<bool> code;
//
// root Node for Huffman tree
Node *root;
//
// table of frequencies (for Huffman)
map<char, int> freq;
//endregion

//region SF helpers

// Node struct for Shannon-Fano algorithm
//
struct node
{
    // character
    //
    char ch;

    // probability of occurrence
    //
    float p;
};

// comparator for nodes for Shannon-Fano algorithm
//
static int node_compare(const void *n1, const void *n2)
{
    const node a = *(node *) n1;
    const node b = *(node *) n2;
    if (a.p < b.p) return 1;
    else if (a.p > b.p) return -1;
    return 0;
}

// size of the table of probbilities
//
int probTableSize;

// the table itself
//
node *probTable;
//endregion

/** a common table of CODES
 * @param char - character
 * @param vector<bool> - it's code
 */
map<char, vector<bool> > table;

//region HUFFMAN algorithm implementation
/**
 * function to build a frequency table
 * @param vec <char> a sequence of characters, the base of the table
 * @return table of char frequencies in a given char vector
 */
map<char, int> getFreq(vector<char> vec)
{
    map<char, int> m;
    for (const auto &x: vec)
        m[x]++;
    return m;
}

/**
 * a function to build a table of codes traversing the tree
 * @param root root-node of the BT
 */
void buildTable(Node *root)
{
    // visit left
    //
    if (root->get_left() != nullptr)
    {
        code.push_back(0);
        buildTable(root->get_left());
    }
    // visit right
    //
    if (root->get_right() != nullptr)
    {
        code.push_back(1);
        buildTable(root->get_right());
    }
    // if we reached a leaf
    //
    if (root->get_left() == nullptr && root->get_right() == nullptr)
        table[root->get_c()] = code;

    // delete the first node
    //
    code.pop_back();
}

/**
 * a function to build a BT using the table of frequencies
 * @param table of frequencies
 */
void buildTree(map<char, int> table)
{
    // create a list - storage for Nodes
    //
    list<Node *> lst;

    // initialize all the nodes in a list
    //
    for (auto itr = table.begin(); itr != table.end(); ++itr)
    {
        Node *tmp = new Node();
        tmp->set_c(itr->first);
        tmp->set_n(itr->second);
        lst.push_back(tmp);
    }

    // build a tree by
    // 1. sorting the nodes
    // 2. taking the first 2 of them, creating a parent node
    // 3. adding parent to the list, pushbacking 2 prev children
    //
    while (lst.size() != 1)
    {
        lst.sort(Compare());
        Node *tmp_left = lst.front();
        lst.pop_front();
        Node *tmp_right = lst.front();
        lst.pop_front();
        lst.push_front(new Node(tmp_left, tmp_right));
    }

    // clearing resources
    //
    code.clear();
    root = lst.front();
    table.clear();
    buildTable(root);

    lst.clear();
}

/**
 * builds a vector of characters from a file
 * @param path to the file
 * @return vector of characters
 */
vector<char> getSymbols(string path)
{
    vector<char> vec;
    ifstream inputFile(path);

    // read char by char into vector
    //
    while (!inputFile.eof())
        vec.push_back((char) inputFile.get());

    // skip EOF character
    //
    vec.pop_back();

    // dispose the stream
    //
    inputFile.close();
    return vec;
}

/**
 * a function to encode file using Huffman algorithm
 * @param in path to the file that is supposed to be encoded
 * @param out output file name
 */
void encodeHuff(string in, string out)
{
    // opening streams
    //
    ifstream file_in(in);
    ofstream output(out, std::ios::binary | std::ios::out);

    // get all the symbols from the input file
    //
    vector<char> symbols = getSymbols(in);

    // build a frequency table
    //
    freq = getFreq(symbols);

    // in case the file is filled with 1 symbol
    //
    if (freq.size() == 1)
    {
        // write 1 - indicator that the file is filled with 1 symbol
        //
        int n = 1;
        output.write(((char *) &n), sizeof(int));

        // next, write the quantity of that symbol
        //
        int k = (int) symbols.size();
        output.write(((char *) &k), sizeof(int));

        // and that symbols
        //
        char c;
        for (int i = 0; i < symbols.size(); ++i)
        {
            c = symbols[i];
            output.write((&c), sizeof(char));
        }
        // return, because we are done with the file
        //
        return;
    }

    // building a tree based on the frequency table
    //
    buildTree(freq);

    // write length of the original file
    //
    int len_msg = (int) symbols.size();
    output.write(((char *) &len_msg), sizeof(int));

    // write the length of the frequency table (# of unique chars)
    //
    int len_freq = (int) freq.size() * 2;
    output.write(((char *) &len_freq), sizeof(int));

    // write the initial table of frequencies
    //
    for (auto i = freq.begin(); i != freq.end(); ++i)
    {
        output.write(((char *) &i->first), sizeof(char));
        output.write(((char *) &i->second), sizeof(int));
    }


    int count = 0;
    char buf = 0;

    // write the source file
    //
    while (!file_in.eof())
    {
        // take a symbol from input file
        //
        char c = (char) file_in.get();

        // get it's code
        //
        vector<bool> x = table[c];
        for (const auto &i:x)
        {
            // accumulate buf until count is 8
            //
            buf |= i << (BYTE - count - 1);
            count++;
            // when count is 8 write buf to file and reset it
            //
            if (count == BYTE)
            {
                count = 0;
                output << buf;
                buf = 0;
            }
        }
    }
    // in case the number of bits is not the multiple of 8,
    // just fill it till the end
    //
    if (count != 0)
        output << buf;

    // clearing the resources
    //
    file_in.close();
    output.close();

    symbols.clear();
}

/**
 * a function to dearchive file using Huffman algorithm
 * @param src  path to encoded source file
 * @param dest path to the dearchived file
 */
void decodeHuff(string src, string dest)
{
    // open streams
    ifstream from(src, std::ios::binary | std::ios::in);
    ofstream de(dest);

    // result string which will be put in the destination file
    //
    string res;

    // read the first byte, the length of the original file
    //
    int len_msg;
    from.read(((char *) &len_msg), sizeof(int));

    // if we have len_msg = 1 then we have only 1 unique symbol
    //
    if (len_msg == 1)
    {
        // read how many of that symbol we have
        //
        int how_many;
        from.read(((char *) &how_many), sizeof(int));

        // write that many of it to the output file
        //
        char c;
        for (int i = 0; i < how_many; ++i)
        {
            from.read((&c), sizeof(char));
            de << c;
        }
        // and return, because we're done with the file
        return;
    }

    // here the len_msg != 1 thus we go ahead and read the next byte
    // which is the length of the frequency table
    int len_freq;
    from.read(((char *) &len_freq), sizeof(int));

    // read and initialize table of frequencies
    //
    map<char, int> m;
    for (int i = 0; i < len_freq / 2; ++i)
    {
        char tmp_char;
        int tmp_int;
        from.read((&tmp_char), sizeof(char));
        from.read(((char *) &tmp_int), sizeof(int));
        m[tmp_char] = tmp_int;
    }

    // build tree using the frequency table
    //
    buildTree(m);

    // get the root
    //
    Node *p = root;

    int count = 0;
    char byte;
    byte = (char) from.get();
    while (!from.eof())
    {
        // get the bit
        //
        bool b = (bool) (byte & (1 << (BYTE - count++ - 1)));

        //if it's 1 we visit the right child, else - left
        //
        if (b)
            p = p->get_right();
        else
            p = p->get_left();

        // when we reached a leaf, we get the char and write it to result string
        //
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

    // write the string to the output from 0 to the given length
    de.write(res.c_str(), len_msg);

    // closing the resources
    //
    from.close();
    de.close();
}
// endregion

// region SHANNON-FANO algorithm implementation

/**
 * process the SF algorithm, build the code table
 * @param start index from where the table of probabilities starts
 * @param stop index from where the table of probabilities ends
 */
void shannonFano(int start, int stop)
{
    // index of the splitting point
    //
    int splitIndex;

    // current probability, full (sum, always approx = 1), and half, which is full / 2
    //
    float prob, fullProb, halfProb;

    // in case we have 1 element just return
    //
    if (start == stop)
    {
        return;
    } else if (stop - start == 1)
    {
        // we have 2 elements, for the first goes 0, for the second 1
        //
        table[probTable[start].ch].push_back(0);
        table[probTable[stop].ch].push_back(1);
    } else
    {
        // count the full probability, it is always approx 1
        //
        fullProb = 0;
        for (int i = start; i <= stop; ++i)
        {
            fullProb += probTable[i].p;
        }

        prob = 0;
        splitIndex = -1;
        halfProb = fullProb * 0.5f;

        // find the partition
        //
        for (int i = start; i <= stop; ++i)
        {
            // accumulating the current probability
            prob += probTable[i].p;
            if (prob <= halfProb)
            {
                // if we are in the first part add 0
                //
                table[probTable[i].ch].push_back(0);
            } else
            {
                // else add 0
                //
                table[probTable[i].ch].push_back(1);
                if (splitIndex < 0)
                {
                    splitIndex = i;
                }
            }
        }
        if (splitIndex < 0)
        {
            splitIndex = start + 1;
        }

        // recursively call this function on the first partition and the second one
        //
        shannonFano(start, splitIndex - 1);
        shannonFano(splitIndex, stop);
    }
}

/**
 * a function to encode the input file using Shannon Fano algorithm
 * @param in path to the input file
 * @param out path to the output file
 */
void encodeSF(string in, string out)
{
    // table of frequencies
    //
    map<char, int> freqs;

    // opening the streams
    //
    ifstream inp(in);
    ofstream outp(out, std::ios::binary | std::ios::out);

    // get all the symbols from the input file
    //
    vector<char> symbols = getSymbols(in);

    // initialize total and freq table
    int total = 0;
    for (const auto &ch:symbols)
    {
        freqs[ch]++;
        total++;
    }
    probTableSize = (int) freqs.size();

    // in case we have the file which is filled with 1 character
    //
    if (probTableSize == 1)
    {
        // write 1 - the indicator
        //
        int n = 1;
        outp.write(((char *) &n), sizeof(int));

        // write number of repeats of that character
        //
        int k = (int) symbols.size();
        outp.write(((char *) &k), sizeof(int));

        // write that much of that char
        //
        char c;
        for (int i = 0; i < symbols.size(); ++i)
        {
            c = symbols[i];
            outp.write((&c), sizeof(char));
        }

        // return because we are done with the file
        //
        return;
    }

    // create a probability table
    //
    probTable = new node[probTableSize];

    // initialize the probability table
    //
    int i = 0;
    for (auto fi = freqs.begin(); fi != freqs.end(); ++fi, ++i)
    {
        probTable[i].ch = fi->first;
        probTable[i].p = float(fi->second) / (float) total;
    }

    // sort it in ascending order
    //
    qsort(probTable, (size_t) probTableSize, sizeof(node), node_compare);

    // create a code table
    //
    shannonFano(0, probTableSize - 1);

    //begin writing the output file.

    // write total # of chars in the source message
    //
    outp.write(((char *) &total), sizeof(int));

    // write the size of the table
    //
    outp.write(((char *) &probTableSize), sizeof(int));

    // write the table itself
    //
    for (i = 0; i < probTableSize; i++)
    {
        outp.write((&probTable[i].ch), sizeof(char));
        outp.write(((char *) &probTable[i].p), sizeof(float));
    }

    // return to the 0 position in the input file for future use
    //
    inp.clear();
    inp.seekg(0);

    int count = 0;
    char buf = 0;
    while (!inp.eof())
    {
        // get the character and it's code
        //
        char c = (char) inp.get();
        vector<bool> x = table[c];

        // split the message (in bits) by 8 and write those chunks
        //
        for (const auto &xx:x)
        {
            buf |= xx << (BYTE - count - 1);
            count++;
            if (count == BYTE)
            {
                count = 0;
                outp << buf;
                buf = 0;
            }
        }
    }
    // if the number of bits is not the multiple of 8 write the rest what we've got
    //
    if (count != 0)
        outp << buf;

    // clear the resources
    //
    table.clear();
    delete[] probTable;

    outp.close();
    inp.close();
}

// region some helpers

/**
 * a function to check the ocurrance of the input vector in the code table
 * @param in input vector
 * @return is input vector in code table
 */
bool isInTable(vector<bool> in)
{
    for (const auto &i:table)
    {
        if (i.second == in)
            return true;
    }
    return false;
}

/**
 * a function to return a char by given code
 * @param in vector (code)
 * @return char that has this code
 */
char getchar(vector<bool> in)
{
    for (const auto &i : table)
    {
        if (i.second == in)
            return i.first;
    }
    return -1;
}
// endregion

/**
 * a function to dearchive encoded file by Shannon Fano algorithm
 * @param from path to the source file
 * @param dest path to the output file
 */
void decodeSF(string from, string dest)
{
    char ch;
    float p;
    int total;
    int tsize;

    // opening streams
    //
    ifstream fr(from, std::ios::binary | std::ios::in);
    ofstream de(dest);

    // read the total size of the original message
    //
    fr.read((char *) (&total), sizeof(int));

    // in case we have a file that is filled with 1 letter
    //
    if (total == 1)
    {
        // read how many of that char do we have
        //
        int how_many;
        fr.read(((char *) &how_many), sizeof(int));

        // and write that many to the decoded file
        //
        char c;
        for (int i = 0; i < how_many; ++i)
        {
            fr.read((&c), sizeof(char));
            de << c;
        }
        // return, because we are done with the file
        //
        return;
    }

    // read the next byte - the length of the probability table
    //
    fr.read((char *) (&tsize), sizeof(int));

    // create and initialize the probability table
    //
    probTable = new node[tsize];
    for (int i = 0; i < tsize; i++)
    {
        fr.read((&ch), sizeof(char));
        fr.read((char *) (&p), sizeof(float));
        probTable[i].ch = ch;
        probTable[i].p = p;
    }

    // build the code table
    //
    shannonFano(0, tsize - 1);

    // result string that will be written to the output file
    //
    string res = "";

    int count = 0;
    char byte;
    byte = (char) fr.get();
    vector<bool> tmp;
    while (!fr.eof())
    {
        // get the bit
        //
        bool b = (bool) (byte & (1 << (BYTE - count++ - 1)));

        // add the current bit to the temp vector
        //
        tmp.push_back(b);

        // gradually check if it exists in table and if it is
        // add char of given code to the result value
        //
        if (isInTable(tmp))
        {
            res += getchar(tmp);
            tmp.clear();
        }

        // if we took 8 bits go ahead to the next 8
        //
        if (count == BYTE)
        {
            count = 0;
            byte = (char) fr.get();
        }
    }

    // write the result string to the output file
    //
    de.write(res.c_str(), total);

    // closing the resources
    //
    de.close();
    fr.close();
}
//endregion

// region main function

/**
 * Function to determine the starting positions of
 * file extention in it's name
 * @param file name with extention
 * @return index of extention
 */
int getCutNum(string inp)
{
    for (int i = (int) inp.size() - 1; i >= 0; --i)
        if (inp[i] == '.')
            return i;
    return (int) inp.size();
}

int main(int argc, char *argv[])
{
    // name of the first file
    //
    string name1;

    // name of the second file
    //
    string name2;

    // ---implementing a command line args logic ---
    //
    if (strcmp(argv[1], "haff") == 0)
    {
        if (strcmp(argv[2], "-d") == 0)
        {
            name1 = argv[3];
            if (argc > 4)
                name2 = argv[4];
            else
                name2 = name1.substr(0, (unsigned int) getCutNum(name1)) + "-unz-h.txt";

            decodeHuff(name1, name2);
        } else
        {
            name1 = argv[2];
            if (argc > 3)
                name2 = argv[3];
            else
                name2 = name1.substr(0, (unsigned int) getCutNum(name1)) + ".haff";
            encodeHuff(name1, name2);
        }
    } else if (strcmp(argv[1], "shan") == 0)
    {
        if (strcmp(argv[2], "-d") == 0)
        {
            name1 = argv[3];
            if (argc > 4)
                name2 = argv[4];
            else
                name2 = name1.substr(0, (unsigned int) getCutNum(name1)) + "-unz-s.txt";

            decodeSF(name1, name2);
        } else
        {
            name1 = argv[2];
            if (argc > 3)
                name2 = argv[3];
            else
                name2 = name1.substr(0, (unsigned int) getCutNum(name1)) + ".shan";
            encodeSF(name1, name2);
        }
    }

    return 0;
}
// endregion

// EOF
