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

bool global1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (verify_content(tokens, currentToken, "$")) {
        if (identifier(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool global2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (verify_content(tokens, currentToken, "$")) {
        if (verify_content(tokens, currentToken, "-")) {
            if (identifier(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool global(vector<Token> tokens, int* currentToken) {
    return verify_productions(tokens, currentToken, {global1, global2});
}