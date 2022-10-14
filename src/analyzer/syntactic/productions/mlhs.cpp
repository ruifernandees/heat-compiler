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


bool mlhs(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    mlhs_item(tokens, currentToken);
    if (tokens[*currentToken].content.compare(",") != 0) {
        return false;
    }
    eat(currentToken);
    mlhs_item(tokens, currentToken);
    if (tokens[*currentToken].content.compare(",") != 0) {
        return false;
    }
    eat(currentToken);
    // pode ser vazio VV
    mlhs_item(tokens, currentToken);
    if (tokens[*currentToken].content.compare("*") != 0) {
        return false;
    }
    eat(currentToken);
    lhs(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") != 0) {
        return false;
    }
    eat(currentToken);

    lhs(tokens, currentToken);
}