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


void tentarMRHSLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
        if (verify_content(tokens, currentToken, "*")) {
            if (arg(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

bool mrhs1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (args(tokens, currentToken)) {
        tentarMRHSLer1(tokens, currentToken);
        return true;
    }
    return false;
}

bool mrhs2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (verify_content(tokens, currentToken, "*")) {
        if (arg(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool mrhs(vector<Token> tokens, int* currentToken) {
    FunctionCallbackArray callback; 
    callback.push_back(mrhs1);
    callback.push_back(mrhs2);
    return verify_productions(tokens, currentToken, callback);
}
