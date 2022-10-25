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

    Token token;
    token.content = "final";
    token.type = "FINAL";
    bool sem_erros = program(tokens, &currentToken);
    cout << "DEU CERTO? " << sem_erros << endl;
}

bool program(vector<Token> tokens, int* currentToken) {
    compstmt(tokens, currentToken);
    if (tokens[*currentToken].type.compare("FINAL") == 0) {
        return true;
    }
    return false;
}