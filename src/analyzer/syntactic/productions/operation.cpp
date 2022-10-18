#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool operation(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1, 2 e 3
    if (identifier(tokens, currentToken)) {
        int pstToken = *currentToken;

        // possibilidade 2
        if (tokens[*currentToken].content.compare("!") == 0) {
            eat(currentToken);
            return true;
        }

        // possibilidade 3
        if (tokens[*currentToken].content.compare("?") == 0) {
            eat(currentToken);
            return true;
        }

        *currentToken = pstToken;

        // possibilidade 1
        return true;
    }

    *currentToken = pastToken;

    return false;
}