#include <string>
#include <cstring>
#include <vector>

#pragma once

#include "../../bnf/types.h"

typedef vector<bool (*)(vector<Token>, int*)> FunctionCallbackArray;

using namespace std;

void semanticAnalyzer(vector<Token> tokens, vector<var_scope> tabela);
