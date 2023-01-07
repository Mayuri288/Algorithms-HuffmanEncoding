#include "utility.h"
#include "run_all.h"
class CharCode
{
public:
    char character;
    string encoding;
    CharCode(char ch, string str) : character(ch), encoding(move(str)) {}
    bool operator<(const CharCode &x) const
    {
        return this->character < x.character;
    }
};
vector<CharCode> writeEncodingToCodes(const string &inputFile, vector<CharCode>
                                                           &codes)
{
    ifstream fin(inputFile);
    string s;
    while (getline(fin, s))
    {
        if (s[0] == 'L' && s[1] == 'F')
        {
            codes.emplace_back(static_cast<char>(10), s.substr(3, s.length()));
        }
        else
        {
            codes.emplace_back(s[0], s.substr(2, s.length()));
        }
    }
    fin.close();
    return codes;
}
int searchCharacter(vector<CharCode> &count, char value)
{
    int x = 0;
    int y = count.size() - 1;
    while (x <= y)
    {
        int i = (x + y) / 2;
        if (count[i].character == value)
            return i;
        else if (count[i].character < value)
            x = i + 1;
        else
            y = i - 1;
    }
    return -1;
}

void huffmanEncoding(const string &inputFile, const string &outputFile,
                     vector<CharCode> &codes)
{
    ifstream fin(inputFile);
    ofstream fout(outputFile);
    char character;
    while (fin.get(character))
    {
        int index = searchCharacter(codes, character);
        fout << codes[index].encoding;
    }
    fin.close();
    fout.close();
}

int main3a()
{
    vector<CharCode> codes;

    codes=writeEncodingToCodes("codetable.txt",codes);
    huffmanEncoding("clear.txt", "coded.txt", codes);
    return 0;
}