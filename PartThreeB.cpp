// part3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "utility.h"
#include "run_all.h"

class Nodes {
public:
    Nodes(int frequency, char ch);
    Nodes* left, * right;
    int frequency;
    char character;
    string huffmancode;
    int getfrequency()const;
    char getChar();
    string getcode();
    bool operator<(const Nodes& n) const;
};

Nodes::Nodes(int frequency, char ch) {
    frequency = frequency;
    character = ch;
    left = NULL;
    right = NULL;
    huffmancode = "";
}

int Nodes::getfrequency() const {
    return frequency;
}

char Nodes::getChar() {
    return character;
}

string Nodes::getcode() {
    return huffmancode;
}

bool Nodes::operator<(const Nodes& n) const {
    return(this->getfrequency() < n.getfrequency());
}


//build a huffman tree
void HuffmanTree(Nodes* n, string code, char c) {
    if (code.length() == 0) { //leaf node
        n->character = c;
    }
    if (code[0] == '0') {
        if (n->left == NULL) {
            n->left = new Nodes(0, '\0');
        }
        HuffmanTree(n->left, code.substr(1, code.length() - 1), c);
    }
    else if (code[0] == '1') {
        if (n->right == NULL) {
            n->right = new Nodes(0, '\0');
        }
        HuffmanTree(n->right, code.substr(1, code.length() - 1), c);
    }

}


void FillTree(const string& codetable, Nodes* n) {
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


void DecodeFile(const string& codedfile, const string& decodedfile, Nodes* n) {

    ifstream Codedfile(codedfile, ifstream::binary); // read in the encoded message
    ofstream Decodedfile(decodedfile);//output file

    if (Codedfile.is_open()) {
        Nodes* Node = n;
        char bit;
        char leafnode;
        while (!Codedfile.eof()) {
            bit = Codedfile.get();
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
        Codedfile.close();
        Decodedfile.close();
    }
    else {
        cout << "Unable to open file" << "codedfile" << endl;
    }
}


int main3b() {
    Nodes* n = new Nodes(0, '\0');
    FillTree("codetable.txt", n);
    DecodeFile("coded.txt", "decoded.txt", n);
    return 0;
}