#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
// include "./index.cpp"

// Roda ai
// vou tentar
#pragma once

using namespace std;

bool functionL(vector<Token> tokens, int *currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1
    if (primaryL(tokens, currentToken)) {
        if (functionL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return true;
}