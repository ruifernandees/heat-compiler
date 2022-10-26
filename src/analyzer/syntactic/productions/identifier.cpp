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

bool identifier(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;
    if (tokens[*currentToken].type.compare(IDENTIFIER) == 0) {
        if (eat(tokens, currentToken)) return true;
    }

    *currentToken = pastToken;

    return false;
}
