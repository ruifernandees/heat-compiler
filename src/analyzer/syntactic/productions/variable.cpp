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

bool variable1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (varname(tokens, currentToken)) {
        return true;
    }
    return false;
}

bool variable2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2 e 3
    if (verify_content(tokens, currentToken, "nil") || verify_content(tokens, currentToken, "self")) {
        return true;
    }
    return false;
}

bool variable(vector<Token> tokens, int* currentToken)
{
    return verify_productions(tokens, currentToken, {variable1, variable2});
}
