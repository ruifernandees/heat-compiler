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

bool symbol(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1 e 2
    if (tokens[*currentToken].content.compare(":") == 0) {
        eat(currentToken);
        int pstToken = *currentToken;

        // possibilidade 1
        if (fname(tokens, currentToken)) {
            return true;
        }

        *currentToken = pastToken;

        // possibilidade 2
        if (varname(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}
