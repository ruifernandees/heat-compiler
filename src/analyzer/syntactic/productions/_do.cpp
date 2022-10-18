#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool _do(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1 e 3
    if (term(tokens, currentToken)) {
        int pstToken = *currentToken;

        // possibilidade 3
        if (tokens[*currentToken].content.compare("do") == 0) {
            eat(currentToken);
            return true;
        }

        *currentToken = pstToken;

        // possibilidade 1
        return true;
    }

    pastToken = *currentToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("do") == 0) {
        eat(currentToken);
        return true;
    }

    pastToken = *currentToken;

    return false;
}
