#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./stmt.cpp"

#pragma once

using namespace std;


bool argdecl(vector<Token> tokens, int* currentToken) {
    
    // possibilidade 1
    if (tokens[*currentToken].content.compare("(") == 0) {
        eat(currentToken);
        if (arglist(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare(")") == 0) {
                eat(currentToken);
                return true;
            }
        }
    }

    // possibilidade 2
    if (arglist(tokens, currentToken))
        return term(tokens, currentToken);
}