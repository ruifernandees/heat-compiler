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

bool variable(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    // possibilidade 1
    if (varname(tokens, currentToken)) {
        return true;
    }

    *currentToken = pastToken;

    // possibilidade 2 e 3
    if (tokens[*currentToken].content.compare("nil") == 0 ||
        tokens[*currentToken].content.compare("self") == 0) {
        eat(tokens, currentToken);
        return true;
    }

    *currentToken = pastToken;

    return false;
}
