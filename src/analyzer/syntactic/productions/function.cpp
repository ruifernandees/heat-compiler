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

void tentarFunctionLer2(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (call_args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}


void tentarFunctionLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("(") == 0) {
        eat(currentToken);

        tentarFunctionLer2(tokens, currentToken);
        if (tokens[*currentToken].content.compare(")") == 0) {
            eat(currentToken);
            return;
        }
    }

    *currentToken = pstToken;
    return;
}


bool Function(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1
    if (operation(tokens, currentToken)) {
        tentarFunctionLer1(tokens, currentToken);
        return true;
    }

    *currentToken = pastToken;

    // possibilidade 2 e 4
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(".") == 0) {
            eat(currentToken);
            if (operation(tokens, currentToken)) {
                int pstToken = *currentToken;

                // possibilidade 2
                if (tokens[*currentToken].content.compare("(") == 0) {
                    eat(currentToken);
                    tentarFunctionLer2(tokens, currentToken);
                    if (tokens[*currentToken].content.compare(")") == 0) {
                        eat(currentToken);
                        return true;
                    }
                }

                *currentToken = pstToken;

                // possibilidade 4
                return true;
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 3 e 5
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("::") == 0) {
            eat(currentToken);
            if (operation(tokens, currentToken)) {
                int pstToken = *currentToken;

                // possibilidade 3
                if (tokens[*currentToken].content.compare("(") == 0) {
                    eat(currentToken);
                    tentarFunctionLer2(tokens, currentToken);
                    if (tokens[*currentToken].content.compare(")") == 0) {
                        eat(currentToken);
                        return true;
                    }
                }

                *currentToken = pstToken;

                // possibilidade 5
                return true;
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 6 e 7
    if (tokens[*currentToken].content.compare("super") == 0) {
        eat(currentToken);

        int pstToken = *currentToken;

        // possibilidade 6
        if (tokens[*currentToken].content.compare("(") == 0) {
            eat(currentToken);
            tentarFunctionLer2(tokens, currentToken);
            if (tokens[*currentToken].content.compare(")") == 0) {
                eat(currentToken);
                return true;
            }
        }

        *currentToken = pstToken;

        // possibilidade 7
        return true;
    }

    *currentToken = pastToken;
    
    return false;
}
