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

bool call(vector<Token> tokens, int* currentToken)
{
    // 1 possibilidade
    function(tokens, currentToken);
    eat(currentToken);
    // 2 possibilidade
    command(tokens, currentToken);
    eat(currentToken);
    //3 possibilidade
    arg(tokens, currentToken);
    eat(currentToken);
    //4
    primary(tokens, currentToken);

    
}