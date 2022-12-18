#include <string>
#include <cstring>
#include <vector>


#pragma once

#define NULL_ID_RECURSIVE -1
#include "../../bnf/types.h"

typedef vector<bool (*)(vector<Token>, int*)> FunctionCallbackArray;

using namespace std;

void atribuir(vector<var_scope>* st, vector<Token> tokens, vector<vector<Token>> comandos, vector<function_scope> *functions, int linha, Scope escopo_atual, int i);
int search_var(vector<var_scope> symbols_table, string var_name, string scope_name);
void call_fn(vector<Token> tokens, vector<vector<Token>> comandos, vector<function_scope> *functions, vector<var_scope> *st, int linha, int *current_token, Scope escopo_atual);
bool existe(vector<function_scope> *functions, string name_function, int linha, Scope escopo_atual, int qnt_argumentos);
int search_function(vector<function_scope> functions_table, string function_name, string scope_name, int qnt_argumentos);
vector<string> executar_funcao(vector<var_scope> *st, vector<function_scope> *functions, function_scope function, vector<var_scope> parametros, vector<vector<Token>> comandos, int linha_funcao);