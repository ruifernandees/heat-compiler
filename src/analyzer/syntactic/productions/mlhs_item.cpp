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

bool mlhs_item1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (lhs(tokens, currentToken)) {return true;}
    return false;
}

bool mlhs_item2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (verify_content(tokens, currentToken, "(")) {
        if (mlhs(tokens, currentToken)) {
            if (verify_content(tokens, currentToken, ")")) {
                return true;
            }
        }
    }
    return false;
}

bool mlhs_item(vector<Token> tokens, int* currentToken)
{
    return verify_productions(tokens, currentToken, {mlhs_item1, mlhs_item2});
}