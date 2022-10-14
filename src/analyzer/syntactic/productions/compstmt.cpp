#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./stmt.cpp"
#include "./term.cpp"
#include "./expr.cpp"

#pragma once

using namespace std;

bool compstmt(vector<Token> tokens, int* currentToken) {
    stmt(tokens, currentToken);
    eat(currentToken);

    // existe ou nao
    term(tokens, currentToken);
    *currentToken = *currentToken + 1;
    expr(tokens, currentToken);
    *currentToken = *currentToken + 1;
    
    term(tokens, currentToken);
}

