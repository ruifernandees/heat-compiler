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

bool argdecl1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (verify_content(tokens, currentToken, "(")) {
        if (arglist(tokens, currentToken)) {
            if (verify_content(tokens, currentToken, ")")) {
                if (tokens[*currentToken].content[0] == '\n') {
                    if (eat(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool argdecl2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (arglist(tokens, currentToken)) {
        if (term(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool argdecl(vector<Token> tokens, int* currentToken) {
    FunctionCallbackArray callback;
    callback.push_back(argdecl1); 
    callback.push_back(argdecl2);
    return verify_productions(tokens, currentToken, callback);
}