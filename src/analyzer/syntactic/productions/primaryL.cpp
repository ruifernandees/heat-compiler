#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool primaryL(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (tokens[*currentToken].content.compare("::")) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("[")) {
        eat(currentToken);
        if (args(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare("]")) {
                eat(currentToken);
                if (primaryL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // 3 possibidade (vazio)

    return true;
}