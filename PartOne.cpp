#include "utility.h"
#include <vector>
#include <algorithm>
#include "run_all.h"

vector<int> getInput(string filepath) {
	vector<int> input;
	ifstream inputFile;
	inputFile.open(filepath);
	while (!inputFile.eof()) {
		char c;
		inputFile.get(c);
		int ascVal = static_cast<int>(c);
		input.push_back(ascVal);
	}
	sort(input.begin(), input.end());
	return input;
}

void write(string filepath, vector<int> input) {
	int previous = -1;
	char c;
	int count = 1;
	ofstream outputFile;
	outputFile.open(filepath);
	for (int i = 0; i < input.size(); i++) {
		if (input.at(i) == previous) {
			count++;
		}
		else {
			if (i != 0) {
				if (previous == 10) {
					outputFile << "LF" << " " << count << endl;
				}
				else {
					outputFile << c << " " << count << endl;
				}
			}
			c = static_cast<char>(input.at(i));
			previous = input.at(i);
			count = 1;
		}
	}
	outputFile << c << " " << count;
	outputFile.close();
}

int main1() {
	vector<int> input = getInput("clear.txt");
	write("freq.txt", input);
	return 0;
}