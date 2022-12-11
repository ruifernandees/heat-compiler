#include <string>
#include <cstring>
#include <vector>


#pragma once

#define NULL_ID_RECURSIVE -1
#include "../../bnf/types.h"

typedef vector<bool (*)(vector<Token>, int*)> FunctionCallbackArray;

using namespace std;

typedef struct scope {
    string name;
    string type;
} Scope;


typedef struct var_scope {
    string name;
    vector<string> value;
    Scope scope;
    int idRecursive = NULL_ID_RECURSIVE;
} var_scope;


vector<var_scope> syntacticAnalyzer(vector<Token> tokens);

bool program(vector<Token> tokens, int* currentToken);
bool compstmt(vector<Token> tokens, int* currentToken);
bool stmt(vector<Token> tokens, int* currentToken);
bool stmtL(vector<Token> tokens, int* currentToken);
bool expr(vector<Token> tokens, int* currentToken);
bool exprL(vector<Token> tokens, int* currentToken);
bool call(vector<Token> tokens, int* currentToken);
bool command(vector<Token> tokens, int* currentToken);
bool Function(vector<Token> tokens, int* currentToken);
bool functionL(vector<Token> tokens, int* currentToken);
bool func2(vector<Token> tokens, int* currentToken);
bool arg(vector<Token> tokens, int* currentToken);
bool argL(vector<Token> tokens, int* currentToken);
bool primary(vector<Token> tokens, int* currentToken);
bool primaryL(vector<Token> tokens, int* currentToken);
bool primaryM(vector<Token> tokens, int* currentToken);
bool when_args(vector<Token> tokens, int* currentToken);
bool then(vector<Token> tokens, int* currentToken);
bool _do(vector<Token> tokens, int* currentToken);
bool block_var(vector<Token> tokens, int* currentToken);
bool mlhs(vector<Token> tokens, int* currentToken);
bool mlhs_item(vector<Token> tokens, int* currentToken);
bool lhs(vector<Token> tokens, int* currentToken);
bool mrhs(vector<Token> tokens, int* currentToken);
bool call_args(vector<Token> tokens, int* currentToken);
bool args(vector<Token> tokens, int* currentToken);
bool argdecl(vector<Token> tokens, int* currentToken);
bool arglist(vector<Token> tokens, int* currentToken);
bool assocs(vector<Token> tokens, int* currentToken);
bool assoc(vector<Token> tokens, int* currentToken);
bool variable(vector<Token> tokens, int* currentToken);
bool literal(vector<Token> tokens, int* currentToken);
bool term(vector<Token> tokens, int* currentToken);
bool op_asgn(vector<Token> tokens, int* currentToken);
bool symbol(vector<Token> tokens, int* currentToken);
bool fname(vector<Token> tokens, int* currentToken);
bool operation(vector<Token> tokens, int* currentToken);
bool varname(vector<Token> tokens, int* currentToken);
bool global(vector<Token> tokens, int* currentToken);
bool identifier(vector<Token> tokens, int* currentToken);