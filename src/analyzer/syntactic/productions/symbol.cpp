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

bool symbol1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1 e 2
    if (verify_content(tokens, currentToken, ":")) {
        int pstToken = *currentToken;

        // possibilidade 1
        if (fname(tokens, currentToken)) {
            return true;
        }

        *currentToken = pstToken;

        // possibilidade 2
        if (varname(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool symbol(vector<Token> tokens, int* currentToken)
{
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(symbol1);
    return verify_productions(tokens, currentToken, prodVector);
}
