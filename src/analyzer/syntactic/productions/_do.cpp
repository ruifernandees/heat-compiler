#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool _do(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (term(tokens, currentToken)) {
        return true;
    }

    // possibilidade 2
    if (tokens[*currentToken].content.compare("do") == 0) {
        eat(currentToken);
        return true;
    }

    // possibilidade 3
    if (term(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("do") == 0) {
            eat(currentToken);
            return true;
        }
    }

}
