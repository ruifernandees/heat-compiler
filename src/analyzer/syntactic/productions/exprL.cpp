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

bool exprL1(vector<Token> tokens, int* currentToken)
{
    //possibilidade 1 e 2
    if (verify_content(tokens, currentToken, "and") || verify_content(tokens, currentToken, "or")) {
        if (expr(tokens, currentToken)) {
            if (exprL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool exprL(vector<Token> tokens, int* currentToken)
{
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(exprL1);

    if (verify_productions(tokens, currentToken, prodVector)) {
        return true;
    }
    // pode ser vazio
    return true;
}