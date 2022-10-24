#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool mlhs(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (mlhs_item(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(",") == 0) {
            eat(currentToken);

            tentarLer1(tokens, currentToken);
            tentarLer2(tokens, currentToken);
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

bool funcaoComAsterisco(vector<Token> tokens, int* currentToken) {
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

void tentarLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (mlhs_item(tokens, currentToken)) {
        while(funcaoComAsterisco(tokens, currentToken)) {}
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer2(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        tentarLer3(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer3(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (lhs(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}