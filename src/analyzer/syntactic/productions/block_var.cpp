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

bool block_var(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    lhs(tokens, currentToken);
    eat(currentToken);

    // possibilidade 2
    mlhs(tokens, currentToken);
}
