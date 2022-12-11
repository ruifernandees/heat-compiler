#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <stack>

#include "syntactic-analyzer.h"

#include "./productions/_index.cpp"

using namespace std;

Scope newScope(string name, string type)
{
    Scope novo;
    novo.name = name;
    novo.type = type;

    return novo;
}

//verify content

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

bool findPositionInSymbolTableByContentAndSameScope(vector<var_scope> symbols_table, string tokenContent, Scope scope) {
    for (auto position : symbols_table) {
        if (
            position.name.compare(tokenContent) == 0 
            && position.scope.name.compare(scope.name) == 0
        ) {
            return true;
        }
    }
    return false;
}

int somar();
int subtrair();
int multiplicar();
int dividir();

void atribuir(vector<var_scope>* st, vector<Token> tokens, stack<Scope> *escopos, int i)
{
    // x = 23
    int idx = search_var(*st, tokens[i-1].content, escopos->top().name);
    //cout << "idx: " << idx << " st: " << st->at(idx).name << endl;
    st->at(idx).value = stoi(tokens[i+1].content);
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

vector<var_scope> tabela_de_simbolos(vector<Token> tokens)
{
    vector<var_scope> symbols_table;

    vector<Scope> block_keys = {{"def", "function"}, {"class", "class"}, {"if", "if"}, {"elsif", "elsif"}, {"else", "else"}, {"for", "for"}, {"while", "while"}, 
    {"begin", "try"}, };
    
    stack<Scope> escopos;
    Scope padrao = newScope("padrao", "padrao");
    escopos.push(padrao);

    for (int i = 0; i < tokens.size(); i++) {
        scope_type(tokens, block_keys, &escopos, &i);

        if (tokens[i].type.compare(IDENTIFIER) == 0) {
            if (!findPositionInSymbolTableByContentAndSameScope(symbols_table, tokens[i].content, escopos.top()))
            {
                symbols_table.push_back({tokens[i].content, 0, {escopos.top().name, escopos.top().type}});
            }
        }
        
        if (tokens[i].content.compare("end") == 0) {
            escopos.pop();
        }

    }

    return symbols_table;

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
        cout << entry.name << " | " << entry.value << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
    }
}

vector<var_scope> syntacticAnalyzer(vector<Token> tokens) {
    int currentToken = 0;

    Token token;
    token.content = "final";
    token.type = "FINAL";

    tokens.push_back(token);

    bool sem_erros = program(tokens, &currentToken);
    // cout << "currentToken: " << currentToken << "\n";
    cout << "DEU CERTO? " << sem_erros << endl;
    cout << "CurrentToken: " << currentToken << "\n";
    if (sem_erros) {
        vector<var_scope> tabela = tabela_de_simbolos(tokens);
        cout << "TABELA DE SIMBOLOS: \n";
        cout << "name"<< " | " << "value"<< " | " << "scope name"<< " [" << "scope type"<< "]\n";
        for (auto entry: tabela) {
            cout << entry.name << " | " << entry.value << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
        }

        // semantic(tabela);
        semantic(tokens, tabela);

        return tabela;
    }
    throw runtime_error("Wrong syntax");
}

bool program(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;

    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 PROGRAM" << endl;
    bool c = compstmt(tokens, currentToken);
    if (tokens[*currentToken].type.compare("FINAL") == 0) {
        return true;
    }
    return false;
}