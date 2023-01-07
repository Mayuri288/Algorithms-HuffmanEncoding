#include <bitset>
#include "utility.h"
#include "run_all.h"

class CharCode_part4
{
public:
    char character;
    string encoding;
    CharCode_part4(char ch, string str) : character(ch), encoding(move(str)) {}
    bool operator<(const CharCode_part4& x) const
    {
        return this->character < x.character;
    }
};
vector<CharCode_part4> writeEncodingToCodes_part4(const string& inputFile, vector<CharCode_part4>
    & codes)
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
int searchCharacter(vector<CharCode_part4>& count, char value)
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

string huffmanEncoding_part4(const string& inputFile, vector<CharCode_part4>& codes)
{
    ifstream fin(inputFile);
    char character;
    string encoded = "";
    while (fin.get(character))
    {
        int index = searchCharacter(codes, character);
        encoded += codes[index].encoding;
    }
    return encoded;
}


void convert_to_bytes(string encoded) {
    ofstream output("codedalt.txt", ios::binary | ios::out);
    unsigned char bits_buffer = NULL;
    int counter = 0;
    for (int i = 0; i < encoded.size(); i++) {
        if (encoded[i] == '1') {
            bits_buffer |= (1 << 7 - counter);
        }
        
        counter++;
        if (counter == 8) {
            bitset<8> byte(bits_buffer);
            output << bits_buffer;
            bits_buffer = NULL;
            counter = 0;
        }
    }
    if (counter != 0) {
        output << bits_buffer;
    }
    output.close();
}

int main4a() {
    vector<CharCode_part4> codes;
    codes = writeEncodingToCodes_part4("codetable.txt", codes);
    string encoded = huffmanEncoding_part4("clear.txt", codes);
    convert_to_bytes(encoded);
	return 0;
}