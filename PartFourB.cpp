#include "utility.h"
#include "run_all.h"
class Node {
public:
    Node(int frequency, char ch);
    Node* left, * right;
    int frequency;
    char character;
    string huffmancode;
    int getfrequency()const;
    char getChar();
    string getcode();
    bool operator<(const Node& n) const;
};

Node::Node(int frequency, char ch) {
    frequency = frequency;
    character = ch;
    left = NULL;
    right = NULL;
    huffmancode = "";
}

int Node::getfrequency() const {
    return frequency;
}

char Node::getChar() {
    return character;
}

string Node::getcode() {
    return huffmancode;
}

bool Node::operator<(const Node& n) const {
    return(this->getfrequency() < n.getfrequency());
}


//build a huffman tree
void HuffmanTree(Node* n, string code, char c) {
    if (code.length() == 0) { //leaf node
        n->character = c;
    }
    if (code[0] == '0') {
        if (n->left == NULL) {
            n->left = new Node(0, '\0');
        }
        HuffmanTree(n->left, code.substr(1, code.length() - 1), c);
    }
    else if (code[0] == '1') {
        if (n->right == NULL) {
            n->right = new Node(0, '\0');
        }
        HuffmanTree(n->right, code.substr(1, code.length() - 1), c);
    }

}


void FillTree(const string& codetable, Node* n) {
    ifstream file(codetable);

    if (!file.is_open()) {
        cout << "Unable to open file" << codetable << endl;
    }
    string hcode; //store huffman code
    string line;
    char ch; //store character
    while (file) {
        try {
            getline(file, line);
            if ((line[0] == 'L') && (line[1] == 'F')) { // dealing with LF character
                ch = static_cast<char>(10);
                hcode = line.substr(3, line.length() - 3);
            }
            else {
                ch = line[0];
                hcode = line.substr(2, line.length() - 2);
            }

            HuffmanTree(n, hcode, ch);
        }
        catch (...) {
            
        }
    }
    file.close();
}


void DecodeFile(const string coded, const string& decodedfile, Node* n) {
    ofstream Decodedfile(decodedfile);//output file

    Node* Node = n;
    char bit;
    char leafnode;
    for (int i = 0; i < coded.length(); i++){
        bit = coded[i];
        if ((bit != '0') && (bit != '1'))
            continue;

        if (Node->left != NULL && bit == '0') {
            Node = Node->left;
        }
        if (Node->right != NULL && bit == '1') {
            Node = Node->right;
        }
        if (Node->left == NULL && Node->right == NULL) { // reach the leafnode 
            leafnode = Node->getChar();
            Node = n;
            if (leafnode == static_cast<char>(10)) {
                Decodedfile << endl;
            }
            else{
                Decodedfile << leafnode;
            }
        }
    }
    Decodedfile.close();
}

string read_bits(string filename){
    using bits_in_byte = std::bitset<8>;
    using byte = unsigned char;
    string bitstring;
    ifstream file(filename, std::ios::binary);

    char c;
    while (file.get(c))
        bitstring += bits_in_byte(byte(c)).to_string();

    return bitstring;
}



int main4b() {
   Node* n = new Node(0, '\0');
   FillTree("codetable.txt", n);
   string bits = read_bits("codedalt.txt");
   DecodeFile(bits, "decodedalt.txt", n);
   return 0;
}