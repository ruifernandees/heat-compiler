#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <stack>

#include "../../bnf/types.h"

using namespace std;

typedef struct scope {
    string name;
    string type;
} Scope;

typedef struct var_scope {
    string name;
    int value;
    Scope scope;
} var_scope;

int search_var(vector<var_scope> symbols_table, string var_name, string scope_name) {
    int i = 0;
    for (i = 0; i < symbols_table.size(); i++) {
        if (symbols_table[i].name.compare(var_name) == 0 && symbols_table[i].scope.name.compare(scope_name) == 0) 
            return i;
    }

    return -1;
}

void atribuir(vector<var_scope>* st, vector<Token> tokens, int* pos_tk, int pos_st)
{
    var_scope var = st->at(pos_st);
    
    int valor = 0, idx = 0;
    // cout << "pos_st:" << pos_st << "\n";

    while (tokens[*pos_tk].type.compare(DELIMITER) != 0) {
        if (tokens[*pos_tk].type.compare(IDENTIFIER) == 0) {
            idx = search_var(*st, var.name, var.scope.name);
            if (idx == -1) {
                cout << "ERRO: Variável " << tokens[*pos_tk].content << "não declarada no escopo " << var.scope.name << "\n";
                exit(1);
            }
            else {
                var.value = st->at(idx).value;
            }
        }
        else if (tokens[*pos_tk].type.compare(NUMBER) == 0) {
            var.value = stoi(tokens[*pos_tk].content);
        }

        // ideia: escolher a funcao adequada segundo o operador. o problema está nas operações mais complexas
        // outra ideia: já que é uma atribuição, atualizar o valor da variavel em pos_var a cada num/identificador lido
        // assim voce pode realizar operacoes com a propria variavel principal pq é só ir acumulando
        *pos_tk = *pos_tk + 1;
    }
    cout << "valor de {" << var.name << "}: " << var.value << "\n";
        
    st->at(pos_st) = var;
}

vector<vector<Token>> catch_lines(vector<Token> tokens)
{
    vector<vector<Token>> comandos;
    vector<Token> linha;
    for (auto token : tokens)
    {
        if (token.type.compare(DELIMITER) == 0)
        {
            comandos.push_back(linha);
            linha.clear();
        }
        else
        {
            linha.push_back(token);
        }
    }

    return comandos;
}

void semanticAnalyzer(vector<Token> tokens, vector<var_scope> tabela) {
    vector<vector<Token>> comandos = catch_lines(tokens);

    cout << "comandos" << endl;
    for (auto c : comandos)
    {
        //cout << c.;
    }
}