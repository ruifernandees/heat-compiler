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

bool symbol(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    identifier(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("..") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 3
    if (tokens[*currentToken].content.compare("==") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 4
    if (tokens[*currentToken].content.compare("===") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 5
    if (tokens[*currentToken].content.compare(">") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 6
    if (tokens[*currentToken].content.compare(">=") != 0) {
        return false;
    }
    eat(currentToken);
    
    // possibilidade 7
    if (tokens[*currentToken].content.compare("<") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 8
    if (tokens[*currentToken].content.compare("<=") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 9
    if (tokens[*currentToken].content.compare("+") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 10
    if (tokens[*currentToken].content.compare("-") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 11
    if (tokens[*currentToken].content.compare("*") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 12
    if (tokens[*currentToken].content.compare("/") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 13
    if (tokens[*currentToken].content.compare("%") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 14
    if (tokens[*currentToken].content.compare("+@") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 15
    if (tokens[*currentToken].content.compare("-@") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 16
    if (tokens[*currentToken].content.compare("[]") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 17
    if (tokens[*currentToken].content.compare("[]=") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 18
    if (tokens[*currentToken].content.compare("@") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 19
    if (tokens[*currentToken].content.compare("@@") != 0) {
        return false;
    }
    eat(currentToken);
}
