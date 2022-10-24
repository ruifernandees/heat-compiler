#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#pragma once

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"


using namespace std;

bool arg(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1
    if (lhs(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("=") == 0) {
            eat(currentToken);
            if (arg(tokens, currentToken)) {
                if (argL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // poss 2
    if (lhs(tokens, currentToken)) {
        if (op_asgn(tokens, currentToken)) {
            if (arg(tokens, currentToken)) {
                if (argL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 3
    if (primary(tokens, currentToken)) {
        if (argL(tokens, currentToken))
            return true;
    }

    *currentToken = pastToken;
    
    // possibilidade 4 (+) e 5(=)

    if (tokens[*currentToken].content.compare("+") == 0 
        || tokens[*currentToken].content.compare("-") == 0) {
        eat(currentToken);
        if (arg(tokens, currentToken)) {
            if (argL(tokens, currentToken)) {
                return true;
            } 
        }
    }

    *currentToken = pastToken;

    return false;
}
