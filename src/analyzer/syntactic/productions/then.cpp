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

bool then1(vector<Token> tokens, int* currentToken)
{
    // 1 e 3 possibilidade
    if (term(tokens, currentToken)) {
        int pstToken = *currentToken;

        // 3 possibilidade
        if (verify_content(tokens, currentToken, "then")) {
            return true;
        }

        *currentToken = pstToken;

        // 1 possibilidade
        return true;
    }
    return false;
}

bool then2(vector<Token> tokens, int* currentToken)
{
    // 2 possibilidade
    if (verify_content(tokens, currentToken, "then")) {
        return true;
    }
    return false;
}

bool then(vector<Token> tokens, int* currentToken) {
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(then1);
    prodVector.push_back(then2);
    return verify_productions(tokens, currentToken, prodVector);
}