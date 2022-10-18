#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"

using namespace std;

void syntacticAnalyzer(vector<Token> tokens) {
    int currentToken = 0;

    //token.content = "$"; <- temos na BNF
    //token.type = "final";
    program(tokens, &currentToken);
}

bool program(vector<Token> tokens, int* currentToken) {
    compstmt(tokens, currentToken);
    // if (tokens[*currentToken].content.compare("$") == 0)
    // {
    //     return true;
    // }
}