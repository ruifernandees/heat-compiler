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

void tentarLHSLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

bool lhs(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (variable(tokens, currentToken)) {return true;}

    *currentToken = pastToken;

    // possibilidade 2
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("[") == 0) {
            eat(currentToken);

            tentarLHSLer1(tokens, currentToken);
            
            if (tokens[*currentToken].content.compare("]")) {
                eat(currentToken);
                return true;
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 3
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(".") == 0) {
            eat(currentToken);
            if (identifier(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    return false;
}

