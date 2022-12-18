#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <stack>

#include "syntactic-analyzer.h"
#include "semantic-analyzer.h"
#include "./functions_semantic/_index.cpp"

using namespace std;

void scope_type_semantic(vector<Token> tokens, vector<Scope> keywords, stack<Scope> *escopos, int* i, vector<function_scope> *functions, int linha) {
    for (auto key: keywords) {
        if (tokens[*i].content.compare(key.name) == 0) {
            if (key.name.compare("def") == 0) {

                int qnt_parametros = 0;
                int a = *i + 2;
                while (tokens[a].content.compare(")") != 0)
                {
                    if (tokens[a].type.compare(IDENTIFIER) == 0 || tokens[a].type.compare(NUMBER) == 0)
                    {
                        qnt_parametros++;
                    }
                    a = a + 1;
                }

                // procurar a funcao nesse escopo e mudar a linha
                int idf = search_function(*functions, tokens[*i+1].content, escopos->top().name, qnt_parametros);

                //cout << "idf: " << idf << " name: " << tokens[*i+1].content << " linha: " << linha;
                functions->at(idf).linha = linha;

                escopos->push({tokens[*i+1].content, key.type});
                *i = *i + 2;
                return;
            }
            escopos->push({key});
            return;
        }
    }
}

void see_commands(vector<var_scope>* st, vector<vector<Token>> comandos, vector<Token> tokens, int linha, stack<Scope> *escopos, vector<function_scope> *functions)
{
    vector<Scope> block_keys = {{"def", "function"}, {"class", "class"}, {"if", "if"}, {"elsif", "elsif"}, {"else", "else"}, {"for", "for"}, {"while", "while"}, 
    {"begin", "try"}, };

    for (int i = 0; i < tokens.size(); i++)
    {
        scope_type_semantic(tokens, block_keys, escopos, &i, functions, linha);

        if (tokens[i].content.compare("end") == 0)
        {
            escopos->pop();
        }

        else if (tokens[i].content.compare("=") == 0)
        {
            atribuir(st, tokens, comandos, functions, linha, escopos->top(), i);
        }

        else if (tokens[i].type.compare(IDENTIFIER) == 0)
        {
            if (i + 1 < tokens.size() && (tokens[i+1].type.compare(IDENTIFIER) == 0 || tokens[i+1].type.compare(NUMBER) == 0))
            {
                call_fn(tokens, comandos, functions, st, linha, &i, escopos->top());
            }
        }
    }
}

vector<vector<Token>> catch_lines(vector<Token> tokens)
{
    vector<vector<Token>> comandos;
    vector<Token> linha;
    for (auto token : tokens)
    {
        if (token.content.compare(";") == 0 || token.content.compare("\n") == 0)
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

void semantic(vector<Token> tokens, vector<var_scope> tabela, vector<function_scope> functions) {
    vector<vector<Token>> comandos = catch_lines(tokens);

    /*cout << "comandos" << endl;
    for (int i = 0; i < comandos.size(); i++)
    {
        cout << "linha " << i << endl;
        for (auto c : comandos[i])
        {
            cout << c.content << " ";
        }
        cout << endl;
    }*/
    
    stack<Scope> escopos;
    escopos.push({"padrao", "padrao"});
    for (int i = 0; i < comandos.size(); i++)
    {
        see_commands(&tabela, comandos, comandos[i], i, &escopos, &functions);
    }
    // atribuir(&tabela, tokens, &pos_token, pos_symbol_table);
    // cout << "🔌" << st->at(current_position_st).name << ", " << st->at(current_position_st).scope.name << ", " << st->at(current_position_st).value << endl;
    cout << "TABELA DE SIMBOLOS - SEMANTICO: \n";
    cout << "name"<< " | " << "value"<< " | " << "scope name"<< " [" << "scope type"<< "]\n";
    for (auto entry: tabela) {
        cout << entry.name << " | ";
        for (auto value : entry.value)
        {
            cout << value << " ";
        }
        cout << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
    }

    cout << "FUNCTIONS - SEMANTICO" << endl;
    for (auto entry: functions) {
        cout << "linha: " << entry.linha << " | " << entry.name << " | " << entry.qnt_argumentos << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
    }
}