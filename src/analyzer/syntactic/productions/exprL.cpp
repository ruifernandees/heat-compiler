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

bool exprL(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    //possibilidade 1 e 2
    if (tokens[*currentToken].content.compare("and") == 0
        || tokens[*currentToken].content.compare("or") == 0) {
        eat(currentToken);
        if (expr(tokens, currentToken)) {
            if (exprL(tokens, currentToken)) {
                return true;
            }
        }   
    }

    *currentToken = pastToken;

    // pode ser vazio
    return true;
}