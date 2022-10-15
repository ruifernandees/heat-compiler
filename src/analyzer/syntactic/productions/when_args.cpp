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


bool when_args(vector<Token> tokens, int* currentToken) {
    // 1 possibilidade
    args(tokens, currentToken);
    if (tokens[*currentToken].content.compare(",") != 0) {
        return false;
    }
    eat(currentToken);
    if (tokens[*currentToken].content.compare("*") != 0) {
        return false;
    }
    eat(currentToken);
    arg(tokens, currentToken);

    // 2 possibilidade
    if (tokens[*currentToken].content.compare("*") != 0) {
        return false;
    }
    eat(currentToken);

    arg(tokens, currentToken);
}