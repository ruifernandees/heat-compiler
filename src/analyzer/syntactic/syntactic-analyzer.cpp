#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"

#include "./productions/_index.cpp"

using namespace std;

void syntacticAnalyzer(vector<Token> tokens) {
    int currentToken = 0;

    //token.content = "$"; <- temos na BNF
    //token.type = "final";
    bool sem_erros = program(tokens, &currentToken);
    cout << sem_erros << endl;
}

bool program(vector<Token> tokens, int* currentToken) {
    return compstmt(tokens, currentToken);
    // if (tokens[*currentToken].content.compare("$") == 0)
    // {
    //     return true;
    // }
}