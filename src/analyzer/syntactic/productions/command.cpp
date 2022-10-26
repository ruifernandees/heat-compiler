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
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    // possibilidade 1
    if (operation(tokens, currentToken)) {
        if (call_args(tokens, currentToken)) {return true;}
    }

    *currentToken = pastToken;

    // possibilidade 2 e 3
    if (primary(tokens, currentToken)) {
        int pstToken = *currentToken;
        
        // 2
        if (tokens[*currentToken].content.compare(".") == 0) {
            if (eat(tokens, currentToken)) {
                if (operation(tokens, currentToken)) {
                    if (call_args(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }

        *currentToken = pstToken;

        // 3
        if (tokens[*currentToken].content.compare("::") == 0) {
            if (eat(tokens, currentToken)) {
                if (operation(tokens, currentToken)) {
                    if (call_args(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 4
    if (tokens[*currentToken].content.compare("super") == 0) {
        if (eat(tokens, currentToken)) {
            if (call_args(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    return false;
}