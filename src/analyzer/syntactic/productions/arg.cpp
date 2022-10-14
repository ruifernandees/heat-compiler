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
    eat(currentToken);



    if (tokens[*currentToken].content.compare("=") != 0) {
        return false;
    }
    eat(currentToken);
    
    // possibilidade 2
    lhs(tokens, currentToken);
    eat(currentToken);

    op_asgn(tokens, currentToken);
    eat(currentToken);

    arg(tokens, currentToken);
    eat(currentToken);
    
    argL(tokens, currentToken);

    // possibilidade 3
    primary(tokens, currentToken);
    eat(currentToken);

    argL(tokens, currentToken);
    
    // possibilidade 4
    if (tokens[*currentToken].content.compare("+") != 0) {
        return false;
    }
    eat(currentToken);

    arg(tokens, currentToken);
    eat(currentToken);

    argL(tokens, currentToken);

    // possibilidade 5
    if (tokens[*currentToken].content.compare("-") != 0) {
        return false;
    }
    eat(currentToken);

    arg(tokens, currentToken);
    eat(currentToken);
    
    argL(tokens, currentToken);
}
