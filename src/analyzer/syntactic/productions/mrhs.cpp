#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
// include "./index.cpp"

#pragma once

using namespace std;


void tentarMRHSLer1(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        if (eat(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare("*") == 0) {
                if (eat(tokens, currentToken)) {
                    if (arg(tokens, currentToken)) {
                        return;
                    }

                }
            }

        }
    }

    *currentToken = pstToken;
    return;
}


bool mrhs(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 MRHS" << endl;
    int pastToken = *currentToken;

    // possibilidade 1
    if (args(tokens, currentToken)) {
        tentarMRHSLer1(tokens, currentToken);
        return true;
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") == 0) {
        if (eat(tokens, currentToken)) {
            if (arg(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    return false;
}
