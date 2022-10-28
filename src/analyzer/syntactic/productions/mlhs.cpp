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


bool funcaoMLHSComAsterisco(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
        if (mlhs_item(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}


void tentarMLHSLer1(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (mlhs_item(tokens, currentToken)) {
        while(funcaoMLHSComAsterisco(tokens, currentToken)) {}
        return;
    }

    *currentToken = pstToken;
    return;
}


void tentarMLHSLer3(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (lhs(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarMLHSLer2(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "*")) {
        tentarMLHSLer3(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}


bool mlhs(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 MLHS" << endl;
    int pastToken = *currentToken;

    // possibilidade 1
    if (mlhs_item(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, ",")) {
            tentarMLHSLer1(tokens, currentToken);
            tentarMLHSLer2(tokens, currentToken);
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (verify_content(tokens, currentToken, "*")) {
        if (lhs(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}
