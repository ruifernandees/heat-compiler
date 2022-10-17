#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool literal(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1
    if (tokens[*currentToken].type.compare(NUMBER) == 0)
    {
        return false;
    }
    
    *currentToken = pastToken;

    // possibilidade 2
    if (symbol(tokens, currentToken)) {return true;}

    *currentToken = pastToken;

    return false;
}
