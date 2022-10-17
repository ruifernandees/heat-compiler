#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool assocs(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    if (assoc(tokens, currentToken))
        return true;
    
    // varios ou vazio
    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    assoc(tokens, currentToken);
}