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

bool arg(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    lhs(tokens, currentToken);

    if (tokens[*currentToken].content.compare("=") != 0) {
        return false;
    }
    eat(currentToken);
    
    // possibilidade 2
    lhs(tokens, currentToken);

    op_asgn(tokens, currentToken);

    arg(tokens, currentToken);
    
    argL(tokens, currentToken);

    // possibilidade 3
    primary(tokens, currentToken);

    argL(tokens, currentToken);
    
    // possibilidade 4
    if (tokens[*currentToken].content.compare("+") != 0) {
        return false;
    }
    eat(currentToken);

    arg(tokens, currentToken);

    argL(tokens, currentToken);

    // possibilidade 5
    if (tokens[*currentToken].content.compare("-") != 0) {
        return false;
    }
    eat(currentToken);

    arg(tokens, currentToken);
    
    argL(tokens, currentToken);
}
