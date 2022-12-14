#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
// include "./index.cpp"

#pragma once

using namespace std;

bool literal1(vector<Token> tokens, int* currentToken)
{
    if (tokens[*currentToken].type.compare(NUMBER) == 0) {
        if (eat(tokens, currentToken)) return true;
    }
    return false;
}

bool literal2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (symbol(tokens, currentToken)) {return true;}
    return false;
}

bool literal(vector<Token> tokens, int* currentToken)
{
    return verify_productions(tokens, currentToken, {literal1, literal2});
}
