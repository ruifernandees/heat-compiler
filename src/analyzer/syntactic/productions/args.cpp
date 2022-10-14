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


bool args(vector<Token> tokens, int* currentToken) {
    arg(tokens, currentToken);
    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(tokens, currentToken);

    // pode ser vazio
    arg(tokens, currentToken);
}