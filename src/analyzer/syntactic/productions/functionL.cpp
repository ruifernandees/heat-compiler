#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
// include "./index.cpp"

// Roda ai
// vou tentar
#pragma once

using namespace std;

bool functionL1(vector<Token> tokens, int *currentToken)
{
    // possibilidade 1
    if (primaryL(tokens, currentToken)) {
        if (func2(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool functionL(vector<Token> tokens, int *currentToken)
{
    if (verify_productions(tokens, currentToken, {functionL1})) {
        return true;
    }
    return true;
}