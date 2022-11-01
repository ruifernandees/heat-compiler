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

bool _do1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1 e 3
    if (term(tokens, currentToken)) {
        int pstToken = *currentToken;

        // possibilidade 3
        if (verify_content(tokens, currentToken, "do")) {
            return true;
        }

        *currentToken = pstToken;

        // possibilidade 1
        return true;
    }

    return false;
}

bool _do2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (verify_content(tokens, currentToken, "do")) {
        return true;
    }

    return false;
}

bool _do(vector<Token> tokens, int* currentToken)
{
    return verify_productions(tokens, currentToken, {_do1, _do2});
}
