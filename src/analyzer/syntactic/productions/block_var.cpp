#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
// include "./index.cpp"

#pragma once

using namespace std;

bool block_var(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1
    if (lhs(tokens, currentToken)){
        return true;
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (mlhs(tokens, currentToken)) {
        return true;
    }

    *currentToken = pastToken;

    return false;
}
