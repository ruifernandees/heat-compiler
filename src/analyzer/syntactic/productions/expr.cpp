#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./exprL.cpp"

#pragma once

using namespace std;


bool expr(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    mlhs(tokens, currentToken);

    if (tokens[*currentToken].content.compare("=") != 0) {
        return false;  
    }
    eat(currentToken);
    
    mrhs(tokens, currentToken);
    exprL(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("return") != 0) {
        return false;
    }
    eat(currentToken);

    call_args(tokens, currentToken);
    exprL(tokens, currentToken);
    //possibilidade 3
    if (tokens[*currentToken].content.compare("not") != 0) {
        return false;
    }
    eat(currentToken);

    expr(tokens, currentToken);
    exprL(tokens, currentToken);

    //possibilidade 4
    command(tokens, currentToken);
    exprL(tokens, currentToken);

    // possibilidade 5
    if (tokens[*currentToken].content.compare("!") != 0) {
        return false;
    }
    eat(currentToken);

    command(tokens, currentToken);
    exprL(tokens, currentToken);
    
    //possibilidade 6
    arg(tokens, currentToken);
    exprL(tokens, currentToken);
}
