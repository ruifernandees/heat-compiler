#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"

#pragma once

using namespace std;

vector<string> argLOperators;

void initializeArgLOperatorsVector() {
    argLOperators.push_back("..");
    argLOperators.push_back("...");
    argLOperators.push_back("+");
    argLOperators.push_back("-");
    argLOperators.push_back("*");
    argLOperators.push_back("**");
    argLOperators.push_back("/");
    argLOperators.push_back("%");
    argLOperators.push_back(">");
    argLOperators.push_back(">=");
    argLOperators.push_back("<");
    argLOperators.push_back("<=");
    argLOperators.push_back("==");
    argLOperators.push_back("===");
    argLOperators.push_back("**=");
    argLOperators.push_back("**=");
    argLOperators.push_back("!=");
    argLOperators.push_back("&&");
    argLOperators.push_back("||");
}

bool isAnArgLOperator(string operato) {
    if (argLOperators.size() == 0) { 
        initializeArgLOperatorsVector();
    }
    for (int i = 0; i < argLOperators.size(); i++){
        if (operato.compare(argLOperators[i]) == 0) return true;
    }
    return false;
}

bool argL1(vector<Token> tokens, int* currentToken)
{
    if (isAnArgLOperator(tokens[*currentToken].content)) {
        if (eat(tokens, currentToken)) {
            if (arg(tokens, currentToken)) {
                if (argL(tokens, currentToken)) {
                    return true;
                } 
            }
        }
    }
    return false;
}

bool argL(vector<Token> tokens, int* currentToken)
{
    FunctionCallbackArray callback;
    callback.push_back(argL1);
    if (verify_productions(tokens, currentToken, callback)){
        return true;
    }
    // vazio
    return true;
}