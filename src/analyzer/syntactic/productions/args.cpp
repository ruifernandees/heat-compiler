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


bool funcaoArgsComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
        if (arg(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

bool args1(vector<Token> tokens, int* currentToken)
{
    if (arg(tokens, currentToken)) {
        while (funcaoArgsComAsterisco(tokens, currentToken)) {}
        return true;
    }
    return false;
}

bool args(vector<Token> tokens, int* currentToken) {
    return verify_productions(tokens, currentToken, {args1});
}
