#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <stack>

#include "syntactic-analyzer.h"

#include "./productions/_index.cpp"

using namespace std;

int search_var(vector<var_scope> symbols_table, string var_name, string scope_name) {
    int i = 0;
    cout << "COMPARANDO" << endl;
    for (i = 0; i < symbols_table.size(); i++) {
        cout << i << "["<<symbols_table[i].name << "] [" << symbols_table[i].scope.name << "]"<< endl;
        cout << i << "["<<var_name << "] [" << scope_name << "]"<< endl;
        if (symbols_table[i].name.compare(var_name) == 0 && symbols_table[i].scope.name.compare(scope_name) == 0) 
            return i;
    }
    cout << "END" << endl;

    return -1;
}

void atribuir(vector<var_scope>* st, vector<Token> tokens, stack<Scope> *escopos, int i)
{
    // x = 23
    int idx = search_var(*st, tokens[i-1].content, escopos->top().name);

    vector<string> value;
    cout << "token: " << tokens[i+1].content << endl;

    for (int j = i + 1; j < tokens.size(); j++)
    {
        value.push_back(tokens[j].content);
        cout << "token: " << tokens[j].content << endl;
    }


    st->at(idx).value = value;

    //st->at(idx).value = tokens[i+1].content;
}

void scope_type(vector<Token> tokens, vector<Scope> keywords, stack<Scope> *escopos, int* i) {
    for (auto key: keywords) {
        if (tokens[*i].content.compare(key.name) == 0) {
            if (key.name.compare("def") == 0) {
                escopos->push({tokens[*i+1].content, key.type});
                *i = *i + 2;
                return;
            }
            escopos->push({key});
            return;
        }
    }
}

void see_commands(vector<var_scope>* st, vector<Token> tokens, stack<Scope> *escopos)
{
    vector<Scope> block_keys = {{"def", "function"}, {"class", "class"}, {"if", "if"}, {"elsif", "elsif"}, {"else", "else"}, {"for", "for"}, {"while", "while"}, 
    {"begin", "try"}, };

    for (int i = 0; i < tokens.size(); i++)
    {
        scope_type(tokens, block_keys, escopos, &i);

        if (tokens[i].content.compare("end") == 0)
        {
            escopos->pop();
        }

        if (tokens[i].content.compare("=") == 0)
        {
            atribuir(st, tokens, escopos, i);
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

void semantic(vector<Token> tokens, vector<var_scope> tabela) {
    vector<vector<Token>> comandos = catch_lines(tokens);

    cout << "comandos" << endl;
    for (int i = 0; i < comandos.size(); i++)
    {
        cout << "linha " << i << endl;
        for (auto c : comandos[i])
        {
            cout << c.content << " ";
        }
        cout << endl;
    }
    
    stack<Scope> escopos;
    escopos.push({"padrao", "padrao"});
    for (auto comando : comandos)
    {
        see_commands(&tabela, comando, &escopos);
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
}