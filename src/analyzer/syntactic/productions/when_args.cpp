#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
// include "./index.cpp"
#include "./stmt.cpp"

#pragma once

using namespace std;

void tentarWhenArgsLer1(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        eat(tokens, currentToken);
        if (tokens[*currentToken].content.compare("*") == 0) {
            eat(tokens, currentToken);
            if (arg(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

bool when_args(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 WHEN ARGS" << endl;
    int pastToken = *currentToken;

    // 1 possibilidade
    if (args(tokens, currentToken)) {
        tentarWhenArgsLer1(tokens, currentToken);
        return true;
    }

    *currentToken = pastToken;

    // 2 possibilidade
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(tokens, currentToken);
        if (arg(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

