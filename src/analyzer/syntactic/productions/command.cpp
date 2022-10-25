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

bool command(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1
    if (operation(tokens, currentToken)) {
        if (call_args(tokens, currentToken)) {return true;}
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(".") == 0) {
            eat(currentToken);
            if (operation(tokens, currentToken)) {
                if (call_args(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibildade 3
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("::") == 0) {
            eat(currentToken);
            if (operation(tokens, currentToken)) {
                if (call_args(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 4
    if (tokens[*currentToken].content.compare("super") == 0) {
        eat(currentToken);
        if (call_args(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}