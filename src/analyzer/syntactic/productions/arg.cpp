#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool arg(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (lhs(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("=") == 0) {
            eat(currentToken);
            return true;
        }
        
        // poss 2
        else if (op_asgn(tokens, currentToken)) {
            if (arg(tokens, currentToken)) {
                if (argL(tokens, currentToken)) {
                    return true;
                }
            }
        } 
    }


    // possibilidade 3
    if (primary(tokens, currentToken)) {
        if (argL(tokens, currentToken))
            return true;
    }
    
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

    return false;
}
