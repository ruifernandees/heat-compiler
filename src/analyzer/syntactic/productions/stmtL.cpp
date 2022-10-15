#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool stmtL(vector<Token> tokens, int* currentToken)
{
    // 1 possibilidade
    if (tokens[*currentToken].content.compare("if") != 0)
    {
        return false;
    }
    eat(currentToken);
    expr(tokens, currentToken);

    stmtL(tokens, currentToken);
    
    // 2 possibilidade
    if (tokens[*currentToken].content.compare("while") != 0)
    {
        return false;
    }
    eat(currentToken);
    expr(tokens, currentToken);
    
    stmtL(tokens, currentToken);

    // 3 possibidade (vazio)
}