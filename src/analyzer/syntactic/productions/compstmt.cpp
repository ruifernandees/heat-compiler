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

bool compstmt(vector<Token> tokens, int* currentToken) {
    if (stmt(tokens, currentToken)) {
        while(funcaoComAsterisco(tokens, currentToken)) {}

        // existe ou nao
        tentarCompstmtLer1(tokens, currentToken);
        return true;
    }

}

bool funcaoComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (term(tokens, currentToken)) {
        if (expr(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

void tentarCompstmtLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (term(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}