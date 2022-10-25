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
    int pastToken = *currentToken;
    if (tokens[*currentToken].type.compare(IDENTIFIER) == 0) {
        eat(currentToken);
        return true;
    }

    *currentToken = pastToken;

    return false;
}
