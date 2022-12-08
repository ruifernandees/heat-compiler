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

bool term1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (verify_content(tokens, currentToken, ";")) {        
        return true;
    }
    return false;
}

bool term2(vector<Token> tokens, int* currentToken)
{
    if (tokens[*currentToken].content[0] == '\n') {
        if (eat(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool term(vector<Token> tokens, int* currentToken) {
    FunctionCallbackArray callback;
    callback.push_back(term1);
    callback.push_back(term2);
    return verify_productions(tokens, currentToken, callback);
}