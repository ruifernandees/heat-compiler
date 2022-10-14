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

bool function(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1 tem os colchetes 
    // operation(tokens, currentToken);

    // possibilidade 2
    primary(tokens, currentToken);
    eat(currentToken);
    if (tokens[*currentToken].content.compare(".") != 0) {
        return false;
    }
    eat(currentToken);
    
    operation(tokens, currentToken);
    if (tokens[*currentToken].content.compare("(") != 0) {
        return false;
    }
    eat(currentToken);
    call_args(tokens, currentToken); 
    eat(currentToken);
    
    if (tokens[*currentToken].content.compare(")") != 0) {
        return false;
    }
    eat(currentToken);
    
    // possibilidade 3
    primary(tokens, currentToken);
    eat(currentToken);
    if (tokens[*currentToken].content.compare("::") != 0) {
        return false;
    }
    eat(currentToken);
    operation(tokens, currentToken);
    if (tokens[*currentToken].content.compare("(") != 0) {
        return false;
    }
    eat(currentToken);
    call_args(tokens, currentToken); 
    eat(currentToken);
    
    if (tokens[*currentToken].content.compare(")") != 0) {
        return false;
    }
    eat(currentToken);
    
    // possibilidade 4
    primary(tokens, currentToken);
    if (tokens[*currentToken].content.compare(".") != 0) {
        return false;
    }
    eat(currentToken);
    operation(tokens, currentToken);
    eat(currentToken);

    // possibilidade 5
    primary(tokens, currentToken);
    if (tokens[*currentToken].content.compare("::") != 0) {
        return false;
    }
    eat(currentToken);
    operation(tokens, currentToken);
    eat(currentToken);

    // possibilidade 6
    if (tokens[*currentToken].content.compare("super") != 0) {
        return false;
    }
    eat(currentToken);
    
    if (tokens[*currentToken].content.compare("(") != 0) {
        return false;
    }
    eat(currentToken);
    
    // possibilidade 7
    if (tokens[*currentToken].content.compare("super") != 0) {
        return false;
    }

}