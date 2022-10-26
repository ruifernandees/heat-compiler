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
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    try
    {
        cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 PROGRAM" << endl;
        compstmt(tokens, currentToken);
    }
    catch(const std::exception& e)
    {
        if (tokens[*currentToken].type.compare("FINAL") == 0) {
            return true;
        }
        return false;
        // std::cerr << e.what() << '\n';
    }
    return false;
}