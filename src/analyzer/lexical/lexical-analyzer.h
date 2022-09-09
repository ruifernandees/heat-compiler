#include <string>
#include <cstring>
#include <vector>

#pragma once

using namespace std;

typedef struct aux {
    string content;
    string type;    
} Token;

void lexicalAnalyzer(vector<string> script);
