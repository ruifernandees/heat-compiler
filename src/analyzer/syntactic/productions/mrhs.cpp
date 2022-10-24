#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool mrhs(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (args(tokens, currentToken)) {
        tentarLer1(tokens, currentToken);
        return true;
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (arg(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

void tentarLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        eat(currentToken);
        if (tokens[*currentToken].content.compare("*") == 0) {
            eat(currentToken);
            if (arg(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}