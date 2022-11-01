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

bool operation1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1, 2 e 3
    if (identifier(tokens, currentToken)) {
        int pstToken = *currentToken;

        // possibilidade 2
        if (verify_content(tokens, currentToken, "!")) {
            return true;
        }

        *currentToken = pstToken;

        // possibilidade 3
        if (verify_content(tokens, currentToken, "?")) {
            return true;
        }

        *currentToken = pstToken;

        // possibilidade 1
        return true;
    }
    return false;
}

bool operation(vector<Token> tokens, int* currentToken) {
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(operation1);
    return verify_productions(tokens, currentToken, prodVector);
}