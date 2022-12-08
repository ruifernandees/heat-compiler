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

bool block_var1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (lhs(tokens, currentToken)){
        return true;
    }
    return false;
}

bool block_var2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (mlhs(tokens, currentToken)) {
        return true;
    }
    return false;
}

bool block_var(vector<Token> tokens, int* currentToken)
{
    FunctionCallbackArray callback;
    callback.push_back(block_var1);
    callback.push_back(block_var2);
    return verify_productions(tokens, currentToken, callback);
}
