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

bool call1(vector<Token> tokens, int* currentToken)
{
    // 1 possibilidade
    if (Function(tokens, currentToken)) {return true;}
    return false;
}

bool call2(vector<Token> tokens, int* currentToken)
{
    // 2 possibilidade
    if (command(tokens, currentToken)) {return true;}
    return false;
}

bool call(vector<Token> tokens, int* currentToken)
{
    FunctionCallbackArray callback;
    callback.push_back(call1);
    callback.push_back(call2);
    return verify_productions(tokens, currentToken, callback);
}