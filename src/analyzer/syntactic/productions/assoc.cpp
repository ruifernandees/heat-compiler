#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool assoc(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (arg(tokens, currentToken)) {
        return true;
    }

    // varios ou vazio
    if (tokens[*currentToken].content.compare("=>"))
        return false;
    eat(currentToken);

    arg(tokens, currentToken);
}