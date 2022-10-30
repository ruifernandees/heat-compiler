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

bool varname1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (global(tokens, currentToken)) {
        return true;
    }
    return false;
}

bool varname2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (verify_content(tokens, currentToken, "@")) {
        if (identifier(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool varname3(vector<Token> tokens, int* currentToken)
{
    // possibilidade 3
    if (identifier(tokens, currentToken)) {
        return true;
    }
    return false;
}

bool varname(vector<Token> tokens, int* currentToken) {
    return verify_productions(tokens, currentToken, {varname1, varname2, varname3});
}