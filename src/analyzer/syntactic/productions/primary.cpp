#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./compstmt.cpp"
#include "./primaryL.cpp"
#include "./literal.cpp"
#include "./args.cpp"
#include "./assocs.cpp"
#include "./block_var.cpp"
#include "./expr.cpp"
#include "./then.cpp"
#include "_do.cpp"
#pragma once

using namespace std;

bool primary(vector<Token> tokens, int* currentToken) 
{
    // possibilidade 1
    if (tokens[*currentToken].content.compare("("))
        return false;
    eat(currentToken);
    compstmt(tokens, currentToken);
    if (tokens[*currentToken].content.compare(")"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);
    
    // possibilidade 2
    literal(tokens, currentToken);
    eat(currentToken);
    primaryL(tokens, currentToken);
    eat(currentToken);

    // possibilidade 3
    variable(tokens, currentToken);
    eat(currentToken);
    primaryL(tokens, currentToken);

    // possibilidade 4
    if (tokens[*currentToken].content.compare("::"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);
    eat(currentToken);

    // possibilidade 5
    if (tokens[*currentToken].content.compare("["))
        return false;
    eat(currentToken);
    args(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("]"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);
    eat(currentToken);

    // possibilidade 6
    if (tokens[*currentToken].content.compare("{"))
        return false;
    eat(currentToken);
    args(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("}"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);
    eat(currentToken);

    // possibilidade 7
    if (tokens[*currentToken].content.compare("{"))
        return false;
    eat(currentToken);
    assocs(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("}"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);
    eat(currentToken);

    // possibilidade 8
    if (tokens[*currentToken].content.compare("return"))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("("))
        return false;
    eat(currentToken);

    call_args();
    eat(currentToken);

    if (tokens[*currentToken].content.compare(")"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);

    // possibilidade 9
    function(tokens, currentToken);
    eat(currentToken);
    primaryL(tokens, currentToken);
    eat(currentToken);

    // possibilidade 10
    function(tokens, currentToken);
    if (tokens[*currentToken].content.compare("{"))
        return false;
    eat(currentToken);
    
    if (tokens[*currentToken].content.compare("|"))
        return false;
    eat(currentToken);
    block_var(tokens, currentToken);
    if (tokens[*currentToken].content.compare("|"))
        return false;
    eat(currentToken);
    compstmt(tokens, currentToken);
    eat(currentToken);
    if (tokens[*currentToken].content.compare("}"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);
    
    // possiblidade 10
    if (tokens[*currentToken].content.compare("if"))
        return false;
    eat(currentToken);
    expr(tokens, currentToken);
    then(tokens, currentToken);
    compstmt(tokens, currentToken);
    // (elsif EXPR THEN COMPSTMT)* que a foda
    if (tokens[*currentToken].content.compare("else"))
        return false;
    eat(currentToken);
    compstmt(tokens, currentToken);
    if (tokens[*currentToken].content.compare("end"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);

    // possibilidade 11
    if (tokens[*currentToken].content.compare("while"))
        return false;
    eat(currentToken);
    expr(tokens, currentToken);
    _do(tokens, currentToken);
    compstmt(tokens, currentToken);
    if (tokens[*currentToken].content.compare("end"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);

    // possibilidade 11
    if (tokens[*currentToken].content.compare("case"))
        return false;
    eat(currentToken);
    compstmt(tokens, currentToken);
    //(when WHEN_ARGS THEN COMPSTMT)+
    if (tokens[*currentToken].content.compare("else"))
        return false;
    eat(currentToken);
    compstmt(tokens, currentToken);
    eat(currentToken);
    if (tokens[*currentToken].content.compare("end"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);

    // possibilidade 12 
    if (tokens[*currentToken].content.compare("for"))
        return false;
    eat(currentToken);
    block_var(tokens, currentToken);
    eat(currentToken);
    if (tokens[*currentToken].content.compare("in"))
        return false;
    eat(currentToken);
    expr(tokens, currentToken);
    eat(currentToken);
    _do(tokens, currentToken);
    eat(currentToken);
    compstmt(tokens, currentToken);
    eat(currentToken);
    if (tokens[*currentToken].content.compare("end"))
        return false;
    eat(currentToken);
    primaryL(tokens, currentToken);

    // possibilidade 13
    if (tokens[*currentToken].content.compare("begin"))
        return false;
    eat(currentToken);
    compstmt(tokens, currentToken);
    // [rescue [ARGS] DO COMPSTMT]+
    
}