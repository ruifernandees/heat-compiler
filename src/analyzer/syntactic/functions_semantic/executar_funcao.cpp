#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../semantic-analyzer.h"

vector<string> executar_funcao(vector<var_scope> *st, vector<function_scope> *functions, function_scope function, vector<vector<string>> valores_parametros, vector<vector<Token>> comandos, int linha_funcao)
{
    Scope escopo_atual = {function.name, "function"};

    // add parametros
    bool parentesis = false, retorno = false;
    int parametro = 0;

    vector<string> value = {};

    for (auto c : comandos[linha_funcao])
    {
        if (parentesis)
        {
            // adicionar os parametros na tabela de simbolos
            if (c.type.compare(IDENTIFIER) == 0)
            {
                int id = search_var(*st, c.content, escopo_atual.name);
                st->at(id).value = valores_parametros[parametro];
                parametro++;
            }
        }

        if (c.content.compare("(") == 0)
        {
            parentesis = true;
        }
        else if (c.content.compare(")") == 0)
        {
            parentesis = false;
        }
    }

    for (int i = linha_funcao+1; i < comandos.size(); i++)
    {
        for (int j = 0; j < comandos[i].size(); j++)
        {
            if (retorno)
            {
                // TA FALTANDO CHAMADA DE FUNCAO IGUAL NO ATRIBUIR
                if (comandos[i][j].type.compare(IDENTIFIER) == 0)
                {
                    /*if (j + 1 < tokens.size() && tokens[j+1].type.compare(IDENTIFIER) == 0)
                    {
                        call_fn(tokens, comandos, functions, st, linha, &j, escopo_atual);
                    }*/

                    int id = search_var(*st, comandos[i][j].content, escopo_atual.name);

                    if (id == -1) {
                        cout << "variavel nao existente no retorno da funcao: " << comandos[i][j].content << endl;
                        exit(0);
                    } else {
                        // vetor vazio, nao aconteceu atribuicao
                        if (st->at(id).value.size() == 0)
                        {
                            cout << "variavel nao existente no retorno da funcao: " << comandos[i][j].content << endl;
                            exit(0);
                        }

                        string v = "";
                        for (string c : st->at(id).value) {
                            v += c;
                        }
                        value.push_back(v);
                    }
                }
                else if (comandos[i][j].type.compare(OPERATOR) == 0 || comandos[i][j].type.compare(NUMBER) == 0) {
                    value.push_back(comandos[i][j].content);
                }
                else
                {
                    retorno = false;
                }
            }

            if (comandos[i][j].content.compare("=") == 0)
            {
                atribuir(st, comandos[i], comandos, functions, i, escopo_atual, j);
            }
            else if (comandos[i][j].content.compare("return") == 0)
            {
                retorno = true;
            }
            else if (comandos[i][j].content.compare("end") == 0)
            {
                //cout << "end function" << endl;
                cout << "function (" << function.name << ") RETURN value: ";

                for (auto v : value)
                {
                    cout << v << " ";
                }
                cout << endl;

                return value;
            }
        }
        cout << endl;
    }

    return value;
}