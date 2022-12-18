#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../semantic-analyzer.h"


void atribuir(vector<var_scope>* st, vector<Token> tokens, vector<vector<Token>> comandos, vector<function_scope> *functions, int linha, Scope escopo_atual, int i)
{
    // x = 23
    int idx = search_var(*st, tokens[i-1].content, escopo_atual.name);

    vector<string> value;
    
    for (int j = i + 1; j < tokens.size(); j++)
    {
        if (tokens[j].type.compare(IDENTIFIER) == 0)
        {
            /*if (j + 1 < tokens.size() && tokens[j+1].type.compare(IDENTIFIER) == 0)
            {
                call_fn(tokens, comandos, functions, st, linha, &j, escopo_atual);
            }*/

            int id = search_var(*st, tokens[j].content, escopo_atual.name);

            if (id == -1) {
                cout << "erro atribuindo variavel nao existente" << endl;
                return;
            } else {
                // vetor vazio, nao aconteceu atribuicao
                if (st->at(id).value.size() == 0)
                {
                    cout << "erro atribuindo variavel nao existente" << endl;
                    return;
                }

                string v = "";
                for (string c : st->at(id).value) {
                    v += c;
                }
                value.push_back(v);
            }
        }
        else {
            value.push_back(tokens[j].content);
        }
    }

    st->at(idx).value = value;

    //st->at(idx).value = tokens[i+1].content;
}