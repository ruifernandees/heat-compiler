#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool compstmt(vector<Token> tokens, int* currentToken) {
    if (stmt(tokens, currentToken)) {
        // existe ou nao
        while(funcaoComAsterisco(tokens, currentToken)) {}

        term(tokens, currentToken);
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