#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

#pragma once

using namespace std;

vector<string> readFile(string filename) {
    string line;
    vector<string> lines;
    ifstream fileToRead(filename);
    if (fileToRead.is_open()) {
        while (getline(fileToRead, line)) {
            lines.push_back(line);
            lines.push_back("\n");
        }
        fileToRead.close();
        return lines;
    }
    throw runtime_error("Could not read file");
}