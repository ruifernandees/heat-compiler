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


bool funcaoArglistComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare(",")) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

void tentarArglistLer2(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;
    if (identifier(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}


void tentarArglistLer1(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;
    if (tokens[*currentToken].content.compare(",")) {
        eat(currentToken);
        if (tokens[*currentToken].content.compare("*")) {
            eat(currentToken);
            tentarArglistLer2(tokens, currentToken);
            return;
        }
    }


    *currentToken = pstToken;
    return;
}


void tentarArglistLer3(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare(",")) {
        eat(currentToken);
        if (tokens[*currentToken].content.compare("&")) {
            eat(currentToken);
            if (identifier(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarArglistLer4(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        eat(currentToken);
        if (tokens[*currentToken].content.compare("&") == 0) {
            eat(currentToken);
            if (identifier(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarArglistLer5(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("&") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

bool arglist(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (identifier(tokens, currentToken)) {
        // varios ou vazio
        while (funcaoArglistComAsterisco(tokens, currentToken)) {}

        tentarArglistLer1(tokens, currentToken);
        tentarArglistLer3(tokens, currentToken);

        return true;
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            tentarArglistLer4(tokens, currentToken);
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 3
    tentarArglistLer5(tokens, currentToken);

    // pode gerar vazio tbm (graças a regra 3)
    return true;
}
