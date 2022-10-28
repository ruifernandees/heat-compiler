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
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    // possibilidade 1 e 2
    if (lhs(tokens, currentToken)) {
        int pstToken = *currentToken;

        // 1
        if (verify_content(tokens, currentToken, "=")) {
            if (arg(tokens, currentToken)) {
                if (argL(tokens, currentToken)) {
                    return true;
                }
            }
        }

        *currentToken = pstToken;
        
        // 2
        if (op_asgn(tokens, currentToken)) {
            if (arg(tokens, currentToken)) {
                if (argL(tokens, currentToken)) {
                    return true;
                }
            }
        }

        *currentToken = pstToken;
    }

    *currentToken = pastToken;

    // possibilidade 3
    if (primary(tokens, currentToken)) {
        if (argL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 4 (+) e 5(=)

    if (verify_content(tokens, currentToken, "+") || verify_content(tokens, currentToken, "-")) {
        if (arg(tokens, currentToken)) {
            if (argL(tokens, currentToken)) {
                return true;
            } 
        }
    }

    *currentToken = pastToken;

    return false;
}
