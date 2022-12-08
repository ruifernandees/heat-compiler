#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#pragma once

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"

using namespace std;

bool arg1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1 e 2
    if (lhs(tokens, currentToken)) {
        int pstToken = *currentToken;

        // 1
        if (verify_content(tokens, currentToken, "=")) {
            if (arg(tokens, currentToken)) {
                if (argL(tokens, currentToken)) {
                    return true;
                }
            }
        }

        *currentToken = pstToken;
        
        // 2
        if (op_asgn(tokens, currentToken)) {
            if (arg(tokens, currentToken)) {
                if (argL(tokens, currentToken)) {
                    return true;
                }
            }
        }

        *currentToken = pstToken;
    }
    return false;
}

bool arg3(vector<Token> tokens, int* currentToken)
{
    // possibilidade 3
    if (primary(tokens, currentToken)) {
        if (argL(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool arg4(vector<Token> tokens, int* currentToken)
{
    // possibilidade 4 (+) e 5(-)
    if (verify_content(tokens, currentToken, "+") || verify_content(tokens, currentToken, "-")) {
        if (arg(tokens, currentToken)) {
            if (argL(tokens, currentToken)) {
                return true;
            } 
        }
    }
    return false;
}

bool arg(vector<Token> tokens, int* currentToken)
{
    FunctionCallbackArray callback;
    callback.push_back(arg1);
    callback.push_back(arg3);
    callback.push_back(arg4);
    return verify_productions(tokens, currentToken, callback);
}
