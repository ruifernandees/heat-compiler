#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

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


bool argL(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    if (isAnArgLOperator(tokens[*currentToken].content)) {
        eat(currentToken);
        if (arg(tokens, currentToken)) {
            if (argL(tokens, currentToken)) {
                return true;
            } 
        }
    }

    *currentToken = pastToken;

    // vazio
    return true;
}