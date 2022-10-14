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


bool mlhs_item(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    lhs(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("("))
        return false;
    eat(tokens, currentToken);
    mlhs(tokens, currentToken);
    if (tokens[*currentToken].content.compare(")"))
        return false;
    eat(tokens, currentToken);
}