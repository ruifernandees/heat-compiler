#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool arglist(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (identifier(tokens, currentToken)) {
        // varios ou vazio
        while (funcaoComAsterisco(tokens, currentToken)) {}

        if (tentarLer1(tokens, currentToken)) {
            tentarLer2(tokens, currentToken);
        }
        tentarLer3(tokens, currentToken);

        return true;
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            tentarLer4(tokens, currentToken);
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 3
    tentarLer5(tokens, currentToken);

    // pode gerar vazio tbm (graças a regra 3)
    return true;
}

bool funcaoComAsterisco(vector<Token> tokens, int* currentToken) {
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

bool tentarLer1(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;
    if (tokens[*currentToken].content.compare(",")) {
        eat(currentToken);
        if (tokens[*currentToken].content.compare("*")) {
            eat(currentToken);
            return true;
        }
    }

    *currentToken = pstToken;
    return false;
}

void tentarLer2(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;
    if (identifier(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer3(vector<Token> tokens, int *currentToken)
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

void tentarLer4(vector<Token> tokens, int *currentToken)
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

void tentarLer5(vector<Token> tokens, int *currentToken)
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