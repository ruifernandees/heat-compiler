#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool varname(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (global(tokens, currentToken)) {
        return true;
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("@") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 3
    if (identifier(tokens, currentToken)) {
        return true;
    }

    *currentToken = pastToken;

    return false;
}