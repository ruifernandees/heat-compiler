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

vector<string> fnameOperators;

void initializefnameOperatorsVector() {
    fnameOperators.push_back("..");
    fnameOperators.push_back("==");
    fnameOperators.push_back("..");
    fnameOperators.push_back("==");
    fnameOperators.push_back("===");
    fnameOperators.push_back(">");
    fnameOperators.push_back(">=");
    fnameOperators.push_back("<");
    fnameOperators.push_back("<=");
    fnameOperators.push_back("+");
    fnameOperators.push_back("-");
    fnameOperators.push_back("*");
    fnameOperators.push_back("/");
    fnameOperators.push_back("%");
    fnameOperators.push_back("+@");
    fnameOperators.push_back("-@");
    fnameOperators.push_back("[]");
    fnameOperators.push_back("[]=");
    fnameOperators.push_back("@");
    fnameOperators.push_back("@@");
}

bool isAnfnameOperator(string operato) {
    if (fnameOperators.size() == 0) { 
        initializefnameOperatorsVector();
    }
    for (int i = 0; i < fnameOperators.size(); i++){
        if (operato.compare(fnameOperators[i]) == 0) return true;
    }
    return false;
}

bool fname(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    // possibilidade 1
    if (identifier(tokens, currentToken)) {return true;}

    *currentToken = pastToken;

    // outras possibilidades
    if (isAnfnameOperator(tokens[*currentToken].content)) {
        if (eat(tokens, currentToken)) return true;
    }

    *currentToken = pastToken;

    return false;
}
