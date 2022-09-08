#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

vector<string> readFile(string filename) {
    string line;
    vector<string> lines;
    ifstream fileToRead(filename);
    if (fileToRead.is_open()) {
        while (getline(fileToRead, line)) {
            lines.push_back(line);
        }
        fileToRead.close();
        return lines;
    }
    throw runtime_error("Could not read file");
}