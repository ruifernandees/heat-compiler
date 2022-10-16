#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool arglist(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    if (identifier(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(",") == 0)
            eat(currentToken);
            return true;
    }

    // varios ou vazio
    identifier(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);
    if (tokens[*currentToken].content.compare("*"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare(",") == 0) {
                eat(currentToken);
            }

        }
    }

        


    

    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);

    // possibilidade 3
    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);
}