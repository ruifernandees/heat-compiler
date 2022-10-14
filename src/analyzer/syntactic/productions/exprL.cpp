#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./expr.cpp"

#pragma once

using namespace std;

bool exprL(vector<Token> tokens, int* currentToken)
{
    //possibilidade 1
    if (tokens[*currentToken].content.compare("and") != 0) {
        return false;
    }
    eat(currentToken);
    expr(tokens, currentToken);
    eat(currentToken);
    exprL(tokens, currentToken);
    
    //possibilidade 2
    if (tokens[*currentToken].content.compare("or") != 0) {
        return false;
    }
    eat(currentToken);
    expr(tokens, currentToken);
    eat(currentToken);
    exprL(tokens, currentToken);

    
}