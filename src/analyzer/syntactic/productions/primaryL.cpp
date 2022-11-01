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


void tentarPrimaryLLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

bool primaryL1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (verify_content(tokens, currentToken, "::")) {
        if (identifier(tokens, currentToken)) {
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool primaryL2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (verify_content(tokens, currentToken, "[")) {
        tentarPrimaryLLer1(tokens, currentToken);

        if (verify_content(tokens, currentToken, "]")) {
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool primaryL(vector<Token> tokens, int* currentToken) {
    if (verify_productions(tokens, currentToken, {primaryL1, primaryL2})) {
        return true;
    }
    // 3 possibidade (vazio)
    return true;
}
