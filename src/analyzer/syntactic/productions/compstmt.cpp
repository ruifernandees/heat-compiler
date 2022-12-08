#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
// include "./index.cpp"

#pragma once

using namespace std;

bool funcaoCompstmtComAsterisco(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
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
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (term(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

bool compstmt1(vector<Token> tokens, int* currentToken)
{
    if (stmt(tokens, currentToken)) {
        while(funcaoCompstmtComAsterisco(tokens, currentToken)) {}

        // existe ou nao
        tentarCompstmtLer1(tokens, currentToken);
        return true;
    }
    return false;
}

bool compstmt(vector<Token> tokens, int* currentToken) {
    FunctionCallbackArray callback;
    callback.push_back(compstmt1);
    return verify_productions(tokens, currentToken, callback);
}

