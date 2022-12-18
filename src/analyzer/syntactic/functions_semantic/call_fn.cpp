#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../semantic-analyzer.h"

void call_fn(vector<Token> tokens, vector<vector<Token>> comandos, vector<function_scope> *functions, vector<var_scope> *st, int linha, int *current_token, Scope escopo_atual)
{
    int qnt_parametros = 0;
    vector<var_scope> parametros;

    int i = *current_token + 1;
    while (i < tokens.size())
    {
        if (tokens[i].type.compare(IDENTIFIER) == 0)
        {
            int id = search_var(*st, tokens[i].content, escopo_atual.name);
            if (id == -1) {
                cout << "variavel " << tokens[i].content << " nao existente passada na funcao" << endl;
                exit(0);
            }
            qnt_parametros++;
            parametros.push_back(st->at(id));
        }
        i = i + 1;
    }

    if (existe(functions, tokens[*current_token].content, linha, escopo_atual, qnt_parametros))
    {
        cout << "existe a funcao " << tokens[*current_token].content << endl;

        int idf = search_function(*functions, tokens[*current_token].content, escopo_atual.name, qnt_parametros);
        executar_funcao(st, functions, functions->at(idf), parametros, comandos, idf);
    }
    else
    {
        // ERRO
        cout << "nao existe a funcao " << tokens[*current_token].content << endl;
    }

    *current_token = i;
}