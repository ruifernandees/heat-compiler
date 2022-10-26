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
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    //possibilidade 1 e 2
    if (tokens[*currentToken].content.compare("and") == 0
        || tokens[*currentToken].content.compare("or") == 0) {
        eat(tokens, currentToken);
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