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


bool funcaoArglistComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
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
    if (verify_content(tokens, currentToken, ",")) {
        if (verify_content(tokens, currentToken, "*")) {
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

    if (verify_content(tokens, currentToken, ",")) {
        if (verify_content(tokens, currentToken, "&")) {
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

    if (verify_content(tokens, currentToken, "&")) {
        if (identifier(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

bool arglist1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (identifier(tokens, currentToken)) {
        // varios ou vazio
        while (funcaoArglistComAsterisco(tokens, currentToken)) {}

        tentarArglistLer1(tokens, currentToken);
        tentarArglistLer3(tokens, currentToken);

        return true;
    }
    return false;
}

bool arglist2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (verify_content(tokens, currentToken, "*")) {
        if (identifier(tokens, currentToken)) {
            tentarArglistLer3(tokens, currentToken);
            return true;
        }
    }

    return false;
}

bool arglist(vector<Token> tokens, int* currentToken) {
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(arglist1);
    prodVector.push_back(arglist2);

    if (verify_productions(tokens, currentToken, prodVector)) {
        return true;
    }

    // possibilidade 3
    tentarArglistLer5(tokens, currentToken);

    // pode gerar vazio tbm (graças a regra 3)
    return true;
}
