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


bool funcaoMLHSComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        eat(currentToken);
        if (mlhs_item(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}


void tentarMLHSLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (mlhs_item(tokens, currentToken)) {
        while(funcaoMLHSComAsterisco(tokens, currentToken)) {}
        return;
    }

    *currentToken = pstToken;
    return;
}


void tentarMLHSLer3(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (lhs(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarMLHSLer2(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        tentarMLHSLer3(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}


bool mlhs(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (mlhs_item(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(",") == 0) {
            eat(currentToken);

            tentarMLHSLer1(tokens, currentToken);
            tentarMLHSLer2(tokens, currentToken);
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (lhs(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}
