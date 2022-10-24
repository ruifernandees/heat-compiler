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

bool argdecl(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (tokens[*currentToken].content.compare("(") == 0) {
        eat(currentToken);
        if (arglist(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare(")") == 0) {
                eat(currentToken);
                return true;
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (arglist(tokens, currentToken))
        if (term(tokens, currentToken))
            return true;

    *currentToken = pastToken;

    return false;
}