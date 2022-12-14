#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
// include "./index.cpp"

#pragma once

using namespace std;

bool stmtL1(vector<Token> tokens, int* currentToken)
{
    // 1 possibilidade
    if (verify_content(tokens, currentToken, "if") || verify_content(tokens, currentToken, "while")) {
        if (expr(tokens, currentToken)) {
            if (stmtL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool stmtL(vector<Token> tokens, int* currentToken)
{
    if (verify_productions(tokens, currentToken, {stmtL1})) {
        return true;
    }
    // 3 possibidade (vazio)
    return true;
}