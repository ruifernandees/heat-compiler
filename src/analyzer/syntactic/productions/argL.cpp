#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./expr.cpp"

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
bool isAnArgLOperator(string operator) {
    if (argLOperators.size() == 0) { 
        initializeArgLOperatorsVector();
    }
    for (int i = 0; i < argLOperators.size(); i++){
        if (operator.compare(argLOperators[i]) == 0) return true;
    }
    return false;
}


bool argL(vector<Token> tokens, int* currentToken)
{
    if (tokens[*currentToken].compare("$") == 0) return true;
    if (!isAnArgLOperator(tokens[*currentToken])) return false;
    eat(currentToken);
    arg(tokens, currentToken);
    argL(tokens, currentToken);
    return true;
}