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

bool expr1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (mlhs(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, "=")) {
            if (mrhs(tokens, currentToken)) {
                if (exprL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool expr2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (verify_content(tokens, currentToken, "return")) {
        if (call_args(tokens, currentToken)) {
            if (exprL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool expr3(vector<Token> tokens, int* currentToken)
{
    //possibilidade 3
    if (verify_content(tokens, currentToken, "not")) {
        if (expr(tokens, currentToken)) {
            if (exprL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool expr4(vector<Token> tokens, int* currentToken)
{
    //possibilidade 4
    if (command(tokens, currentToken)) {
        if (exprL(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool expr5(vector<Token> tokens, int* currentToken)
{
    // possibilidade 5
    if (verify_content(tokens, currentToken, "!")) {
        if (command(tokens, currentToken)) {
            if (exprL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool expr6(vector<Token> tokens, int* currentToken)
{
    //possibilidade 6
    if (arg(tokens, currentToken)) {
        if (exprL(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool expr(vector<Token> tokens, int* currentToken) {
    FunctionCallbackArray callback;
    callback.push_back(expr1);
    callback.push_back(expr2);
    callback.push_back(expr3);
    callback.push_back(expr4);
    callback.push_back(expr5);
    callback.push_back(expr6);
    return verify_productions(tokens, currentToken, callback);
}
