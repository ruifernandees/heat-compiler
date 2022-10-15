#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool stmt(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;
    // 1 possibilidade
    if (call(tokens, currentToken)) {
      if (tokens[*currentToken].content.compare("do") != 0)
      {
          return false;
      }
      eat(currentToken);

      if (tokens[*currentToken].content.compare("|") != 0)
      {
          return false;
      }
      eat(currentToken);

      block_var(tokens, currentToken);

      if (tokens[*currentToken].content.compare("|") != 0)
      {
          return false;
      }
      eat(currentToken);

      compstmt(tokens, currentToken);
      if (tokens[*currentToken].content.compare("end") != 0)
      {
          return false;
      }
      eat(currentToken);

      stmtL(tokens, currentToken);
      return true;
    }


    // 2 possibilidade
    if (begin(tokens, currentToken)) {
      if (tokens[*currentToken].content.compare("{") != 0)
      {
          return false;
      }
      eat(currentToken);
      compstmt(tokens, currentToken);
      if (tokens[*currentToken].content.compare("}") != 0)
      {
          return false;
      }
      eat(currentToken);
      stmtL(tokens, currentToken);
      return true;
    }
    
    // 3 possibilidade
    end(tokens, currentToken);
    if (tokens[*currentToken].content.compare("{") != 0)
    {
        return false;
    }
    eat(currentToken);
    compstmt(tokens, currentToken);
    if (tokens[*currentToken].content.compare("}") != 0)
    {
        return false;
    }
    eat(currentToken);
    stmtL(tokens, currentToken);

    // 4 possibilidade
    lhs(tokens, currentToken);
    if (tokens[*currentToken].content.compare("=") != 0)
    {
        return false;
    }
    eat(currentToken);
    
    command(tokens, currentToken);
    if (tokens[*currentToken].content.compare("do") != 0)
    {
        return false;
    }
    eat(currentToken);

    if (tokens[*currentToken].content.compare("|") != 0)
    {
        return false;
    }
    eat(currentToken);

    block_var(tokens, currentToken);

    if (tokens[*currentToken].content.compare("|") != 0)
    {
        return false;
    }
    eat(currentToken);

    compstmt(tokens, currentToken);
    
    if (tokens[*currentToken].content.compare("end") != 0)
    {
        return false;
    }
    eat(currentToken);
    
    stmtL(tokens, currentToken);

    // 5 possibilidade
    expr(tokens, currentToken);
    stmtL(tokens, currentToken);
}