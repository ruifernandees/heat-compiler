#include <string>
#include <cstring>
#include <vector>

using namespace std;

#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

typedef struct aux {
    string content;
    string type;    
} Token;

void lexicalAnalyzer(vector<string> script);

#endif