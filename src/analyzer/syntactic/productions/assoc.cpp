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

bool assoc1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (arg(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, "=>")) {
            if (arg(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool assoc(vector<Token> tokens, int* currentToken) {
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(assoc1);
    return verify_productions(tokens, currentToken, prodVector);
}