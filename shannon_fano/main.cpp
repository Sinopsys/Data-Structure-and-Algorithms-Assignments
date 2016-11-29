#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>

#define BYTE 8
using namespace std;



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
map<char, vector<bool> > table;

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


int main(int argc, char **argv)
{
    int i = 1;
    int dFlag = 0;
    string inputFilename;
    string outputFilename;

/**
 * ./a.out haff inp.txt out.haff
 * ./a.out haff inp.txt
 * ./a.out haff -d out.haff
 * ./a.out haff -d out.haff decod.txt
 *
 * ./a.out sf inp.txt out.shan
 * ./a.out sf inp.txt
 * ./a.out sf -d out.shan
 * ./a.out sf -d out.shan decod.txt
 */
    if (strcmp(argv[i], "-d") == 0)
    {
        dFlag = 1;
        i++;
    }

    inputFilename = argv[i];
    i++;

    if (i < argc)
    {
        outputFilename = argv[i];
    } else
    {
        if (dFlag)
        {
            outputFilename = "output.txt";
        } else
        {
            outputFilename = "output.sf";
        }
    }

    if (!dFlag)
    {
        encodeSF(inputFilename, outputFilename);
    } else
    {
        decodeSF(inputFilename, outputFilename);
    }


    return 0;
}
