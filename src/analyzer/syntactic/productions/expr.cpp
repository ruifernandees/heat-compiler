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
    eat(currentToken);

    if (tokens[*currentToken].content.compare("=") != 0) {
        return false;  
    }
    eat(currentToken);
    
    mrhs(tokens, currentToken);
    eat(currentToken);
    exprL(tokens, currentToken);
    eat(currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("return") != 0) {
        return false;
    }
    eat(currentToken);

    call_args(tokens, currentToken);
    eat(currentToken);
    exprL(tokens, currentToken);
    eat(currentToken);
    //possibilidade 3
    if (tokens[*currentToken].content.compare("not") != 0) {
        return false;
    }
    eat(currentToken);
    expr(tokens, currentToken);
    eat(currentToken);
    exprL(tokens, currentToken);
    eat(currentToken);

    //possibilidade 4
    command(tokens, currentToken);
    eat(currentToken);
    exprL(tokens, currentToken);
    eat(currentToken);

    // possibilidade 5
    if (tokens[*currentToken].content.compare("!") != 0) {
        return false;
    }
    eat(currentToken);
    command(tokens, currentToken);
    eat(currentToken);
    exprL(tokens, currentToken);
    eat(currentToken)
    
    //possibilidade 6
    arg(tokens, currentToken);
    eat(currentToken);
    exprL(tokens, currentToken);
    

}
