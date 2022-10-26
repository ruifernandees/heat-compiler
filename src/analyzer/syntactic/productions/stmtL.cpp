#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
// include "./index.cpp"

#pragma once

using namespace std;

bool stmtL(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    // 1 possibilidade
    if (tokens[*currentToken].content.compare("if") == 0) {
        if (eat(tokens, currentToken)) {
            if (expr(tokens, currentToken)) {
                if (stmtL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // 2 possibilidade
    if (tokens[*currentToken].content.compare("while") == 0) {
        if (eat(tokens, currentToken)) {
            if (expr(tokens, currentToken)) {
                if (stmtL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // 3 possibidade (vazio)
    return true;
}