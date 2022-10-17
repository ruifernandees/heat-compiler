#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "delimiters.h"
#include "types.h"

using namespace std;

vector<string> delimiters;

void initializeDelimitersVector() {
    delimiters.push_back("(");
    delimiters.push_back(")");
    delimiters.push_back("[");
    delimiters.push_back("]");
    delimiters.push_back("{");
    delimiters.push_back("}");
    delimiters.push_back(";");
    delimiters.push_back(",");
    delimiters.push_back("\n");
}

bool isADelimiter(string word) {
    initializeDelimitersVector();
    for (int i = 0; i < delimiters.size(); i++){
        if (word.compare(delimiters[i]) == 0) return true;
    }
    return false;
}

