#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
// include "./index.cpp"
#include "./stmt.cpp"

#pragma once

using namespace std;

void tentarWhenArgsLer1(vector<Token> tokens, int* currentToken)
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

bool when_args1(vector<Token> tokens, int* currentToken)
{
    // 1 possibilidade
    if (args(tokens, currentToken)) {
        tentarWhenArgsLer1(tokens, currentToken);
        return true;
    }
    return false;
}

bool when_args2(vector<Token> tokens, int* currentToken)
{
    // 2 possibilidade
    if (verify_content(tokens, currentToken, "*")) {
        if (arg(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool when_args(vector<Token> tokens, int* currentToken) {
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(when_args1);
    prodVector.push_back(when_args2);
    return verify_productions(tokens, currentToken, prodVector);
}

