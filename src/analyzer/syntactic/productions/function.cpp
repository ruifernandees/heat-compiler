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
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (call_args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarFunctionLer1(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "(")) {
        tentarFunctionLer2(tokens, currentToken);
        if (verify_content(tokens, currentToken, ")")) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}


bool Function(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    // possibilidade 1
    if (operation(tokens, currentToken)) {
        tentarFunctionLer1(tokens, currentToken);
        if (functionL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 2 e 4
    if (primaryM(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, ".")) {
            if (operation(tokens, currentToken)) {
                int pstToken = *currentToken;

                // possibilidade 2
                if (verify_content(tokens, currentToken, "(")) {
                    tentarFunctionLer2(tokens, currentToken);
                    if (verify_content(tokens, currentToken, ")")) {
                        if (functionL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }

                *currentToken = pstToken;

                // possibilidade 4
                if (functionL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 3 e 5
    if (primaryM(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, "::")) {
            if (operation(tokens, currentToken)) {
                int pstToken = *currentToken;

                // possibilidade 3
                if (verify_content(tokens, currentToken, "(")) {
                    tentarFunctionLer2(tokens, currentToken);
                    if (verify_content(tokens, currentToken, ")")) {
                        if (functionL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }

                *currentToken = pstToken;

                // possibilidade 5
                if (functionL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 6 e 7
    if (verify_content(tokens, currentToken, "super")) {
        int pstToken = *currentToken;

        // possibilidade 6
        if (verify_content(tokens, currentToken, "(")) {
            tentarFunctionLer2(tokens, currentToken);
            if (verify_content(tokens, currentToken, ")")) {
                if (functionL(tokens, currentToken)) {
                    return true;
                }
            }
        }

        *currentToken = pstToken;

        // possibilidade 7
        if (functionL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;
    
    return false;
}
