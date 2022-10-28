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
    if (verify_content(tokens, currentToken, "if") || verify_content(tokens, currentToken, "while")) {
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