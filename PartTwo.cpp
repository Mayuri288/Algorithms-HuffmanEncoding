#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "run_all.h"
/// <summary>
/// data in a node.
/// </summary>
struct node {
	std::string character;
	int freq;
	node* left;
	node* right;
};

/// <summary>
/// data of encoded node for output
/// </summary>
struct encoded {
	std::string character;
	std::string binaryEncoding;
};

//function prototype
node* newNode(std::string character, int freq, node* left, node* right);
std::vector<node*> getInput(std::string filepath);
void buildHuffmanTree(std::vector<node*> input);
bool compareFreq(node* a, node* b);
bool compareChar(encoded* a, encoded* b);
void traverseTree(node* curr, std::string encoding);
void writeOutput();

//global var root node and curr node.
node* root = NULL;
std::vector<encoded*> output;


/// <summary>
/// main function
/// </summary>
/// <returns></returns>
int main2() {
	std::vector<node*> input = getInput("freq.txt");
	buildHuffmanTree(input);
	traverseTree(root, "");
	writeOutput();
	return 0;
}

/// <summary>
/// creates and return a new node
/// </summary>
/// <param name="character">character data of the node</param>
/// <param name="freq">freq data of the node</param>
/// <param name="left">pointer to the left node</param>
/// <param name="right">pointer to the right node</param>
/// <returns>returns the node created</returns>
node* newNode(std::string character, int freq, node* left, node* right) {
	node* newNode = new node;
	newNode->character = character;
	newNode->freq = freq;
	newNode->left = left;
	newNode->right = right;
	return newNode;
}

/// <summary>
/// reads the input file and store all info to a vector
/// </summary>
/// <param name="filepath">path of the file</param>
/// <returns>returns the vector that has the info stored</returns>
std::vector<node*> getInput(std::string filepath) {
	std::vector<node*> input;
	std::ifstream inputFile;
	inputFile.open("freq.txt");
	while (!inputFile.eof()) {
		try {
			std::string temp;
			std::string character;
			int freq;
			getline(inputFile, temp);
			if (temp[0] == ' ') {
				character = " ";
				freq = stoi(temp);
			}
			else {
				character = temp.substr(0, temp.find(" "));
				freq = stoi(temp.substr(temp.find(" "), temp.length() - 1));
			}
			node* newHuffmanNode = newNode(character, freq, NULL, NULL);
			input.push_back(newHuffmanNode);
		}
		catch (...) {
			std::cout << "Reading an invalid input, skipped" << std::endl;
		}
	}
	return input;
}

/// <summary>
/// function for comparing the node frequency data
/// </summary>
/// <param name="a">pointer to node a</param>
/// <param name="b">pointer to node b</param>
/// <returns>returns if a's freq is less than b's freq</returns>
bool compareFreq(node* a, node* b) {
	return a->freq < b->freq;
}

/// <summary>
/// funciton to compare the char of the encoded huffman node.
/// turns the char into ascii value and sort it.
/// </summary>
/// <param name="a">pointer to node a </param>
/// <param name="b">pointer to node b</param>
/// <returns>returns if a's char ascii value is less than b's char ascii 
bool compareChar(encoded* a, encoded* b) {
	int avalue = 0;
	int bvalue = 0;
	if (a->character == "LF") {
		avalue = 10;
	}
	else {
		char charA = a->character[0];
		avalue = int(charA);
	}
	if (b->character == "LF") {
		int bvalue = 10;
	}
	else {
		char charB = b->character[0];
		bvalue = int(charB);
	}
	return avalue < bvalue;
}

/// <summary>
/// take the input vector and build the huffman tree base on it
/// </summary>
/// <param name="input">input vector from freq.txt</param>
void buildHuffmanTree(std::vector<node*> input) {
	if (input.size() != 1) {
		std::sort(input.begin(), input.end(), compareFreq);
		node* left = input.at(0);
		node* right = input.at(1);
		node* newHuffNode = newNode("", left->freq + right->freq, left, right);
		input.erase(input.begin(), input.begin() + 2);
		input.push_back(newHuffNode);
		root = newHuffNode;
		buildHuffmanTree(input);
	}
}

/// <summary>
/// traverse the huffman tree and append it's results to a vector 
/// along with the encoding information
/// </summary>
/// <param name="curr">current node that it's on</param>
/// <param name="encoding">encoding information</param>
void traverseTree(node* curr, std::string encoding) {
	if (curr->left != NULL) {
		encoding += '0';
		traverseTree(curr->left, encoding);
		encoding = encoding.substr(0, encoding.length() - 1);
	}
	if (curr->right != NULL) {
		encoding += "1";
		traverseTree(curr->right, encoding);
		encoding = encoding.substr(0, encoding.length() - 1);
	}
	if (curr->character != "") {
		encoded* eNode = new encoded;
		eNode->binaryEncoding = encoding;
		eNode->character = curr->character;
		output.push_back(eNode);
	}
}

/// <summary>
/// write the output to "codetable.txt"
/// </summary>
void writeOutput() {
	std::sort(output.begin(), output.end(), compareChar);
	std::ofstream outputFile;
	outputFile.open("codetable.txt");
	for (int i = 0; i < output.size(); i++) {
		outputFile << output.at(i)->character << " " << output.at(i) -> binaryEncoding << "\n";
	}
	outputFile.close();
}
