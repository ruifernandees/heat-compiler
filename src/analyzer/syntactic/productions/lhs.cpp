#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
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

bool lhs1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (variable(tokens, currentToken)) {return true;}
    return false;
}

bool lhs2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2 e 3
    if (primary(tokens, currentToken)) {
        int pstToken = *currentToken;

        // poss 2
        if (verify_content(tokens, currentToken, "[")) {
            tentarLHSLer1(tokens, currentToken);
            if (verify_content(tokens, currentToken, "]")) {
                return true;
            }
        }

        *currentToken = pstToken;
        
        // poss 3
        if (verify_content(tokens, currentToken, ".")) {
            if (identifier(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool lhs(vector<Token> tokens, int* currentToken) {
    return verify_productions(tokens, currentToken, {lhs1, lhs2});
}