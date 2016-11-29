#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <algorithm>

using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;


class elements
{
public:
    int ascii;
    int prob;
    string code;
};

bool compare(const elements a, const elements b)
{
    return a.prob > b.prob;
}

void shannon_fano(vector<elements> &, int, int);

bool is_in_codes(string in, vector<elements> &data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        if (data[i].code == in)
            return true;
    }
    return false;
}

int main()
{
    ifstream in("input.txt");
    int len = 0, unique = 0;
    map<char, int> m;
    char ch;
    while ((ch = (char) in.get()) != EOF)
    {
        ++len;
        m[ch]++;
    }
    unique = (int)m.size();

    
    vector<elements> data(len);
    for (int i = 0; i < len; i++)
        data[i].ascii = i, data[i].prob = 0, data[i].code = "";
    char c;
    while ((c = (char) in.get()) != EOF)
    {
        int ascii = (int) c;
        data[ascii].prob++;
        len++;
    }

    sort(data.begin(), data.end(), compare);

    for (unique = 0; unique < len; unique++)
        if (data[unique].prob == 0.0f)
            break;
    shannon_fano(data, 0, unique);

    ofstream out("output.bin", std::ios::binary | std::ios::out);
    out.write(((char *) &len), sizeof(int));
    out.write(((char *) &unique), sizeof(int));
    for (int j = 0; j < unique; ++j)
    {
        int ch = data[j].ascii;
        int prob = data[j].prob;
        out.write(((char *) &ch), sizeof(int));
        out.write(((char *) &prob), sizeof(int));
    }

    in.clear();
    in.seekg(0);


    int count = 0;
    char buf;
    while (!in.eof())
    {
        char c = (char) in.get();
        string x;
        for (int i = 0; i < data.size(); ++i)
        {
            if (data[i].ascii == (int) c)
                x = data[i].code;
        }

        for (const auto &i:x)
        {
            buf = buf | i << (8 - count - 1);
            count++;
            if (count == 8)
            {
                count = 0;
                out << buf;
                buf = 0;
            }
        }
    }
    if (count != 0)
        out << buf;


    in.clear();
    in.seekg(0);
    out.clear();
    out.seekp(0);


    ifstream inp("output.bin", std::ios::binary | std::ios::in);
    ofstream outp("out.txt", std::ios::binary | std::ios::out);

    string res = "";
    int len_symb;
    int len_freq;
    inp.read((char *) &len_symb, sizeof(int));
    inp.read((char *) &len_freq, sizeof(int));
    data.clear();
    data = vector<elements>(len_symb);
    for (int l = 0; l < len_freq; ++l)
    {
        int ch, freq;
        inp.read((char *) &ch, sizeof(int));
        inp.read((char *) &freq, sizeof(int));
        data[l].prob = freq;
        data[l].ascii = ch;
    }

    shannon_fano(data, 0, len_freq);

//    for (int i = 0; i < len_freq; i++)
//        cout << (char) data[i].ascii << ':' << data[i].code << ' ';

    count = 0;
    char byte;
    byte = (char) inp.get();
    string tmp = "";
    while (!inp.eof())
    {
        bool b = (bool) (byte & (1 << (8 - count++ - 1)));
        tmp += (char) b;
        for (int i = 0; i < data.size(); ++i)
        {
            if (data[i].code == tmp)
            {
                cout << (char) data[i].ascii;
                tmp = "";
            }
        }
//        ++count;
        if (count == 8)
        {
            count = 0;
            byte = (char) inp.get();
        }
    }


    return 0;
}

void shannon_fano(vector<elements> &data, int start, int end)
{
    if (end - start == 1)
        return;
    if (end - start == 2)
    {
        data[start].code += "0";
        data[end - 1].code += "1";
        return;
    }
    int unique = 0;
    for (int i = start; i < end; i++)
        unique += data[i].prob;

    int partition = start;
    int min = 0, cur = data[start].prob;
    min = abs(cur - (unique - cur));
    for (int i = start + 1; i < end; i++)
    {
        cur += data[i].prob;
        int diff = abs(cur - (unique - cur));
        if (diff < min)
            min = diff, partition = i;
        else
            break;
    }
    int i;
    for (i = start; i <= partition; i++)
        data[i].code += "0";
    for (; i < end; i++)
        data[i].code += "1";
    shannon_fano(data, start, partition + 1);
    shannon_fano(data, partition + 1, end);
}
