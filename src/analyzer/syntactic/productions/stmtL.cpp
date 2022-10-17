#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool stmtL(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // 1 possibilidade
    if (tokens[*currentToken].content.compare("if") == 0) {
        eat(currentToken);
        if (expr(tokens, currentToken)) {
            if (stmtL(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;
    
    // 2 possibilidade
    if (tokens[*currentToken].content.compare("while") == 0) {
        eat(currentToken);
        if (expr(tokens, currentToken)) {
            if (stmtL(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    // 3 possibidade (vazio)
    return true;
}