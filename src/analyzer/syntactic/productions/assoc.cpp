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


bool assocs(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    arg(tokens, currentToken);

    // varios ou vazio
    if (tokens[*currentToken].content.compare("=>"))
        return false;
    eat(currentToken);

    arg(tokens, currentToken);
}