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

void scope_type(vector<Token> tokens, vector<Scope> keywords, stack<Scope> *escopos, int* i) {
    for (auto key: keywords) {
        if (tokens[*i].content.compare(key.name) == 0) {
            if (key.name.compare("def") == 0 || (key.name.compare("class") == 0)) {
                escopos->push({tokens[*i+1].content, key.type});
                *i = *i + 2;
                return;
            }
            escopos->push({key});
            return;
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

    for (int i = 0; i < tokens.size(); i++) {
        scope_type(tokens, block_keys, &escopos, &i);

        if (tokens[i].type.compare(IDENTIFIER) == 0) {
            if (escopos.size() == 0) {
                symbols_table.push_back({tokens[i].content, 0, {"padrao", "padrao"}, -1});
            } 
            else {
                symbols_table.push_back({tokens[i].content, 0, {escopos.top().name, escopos.top().type}, -1});
            }
        }
        
        if (tokens[i].content.compare("end") == 0) {
            escopos.pop();
        }

    }

    return symbols_table;

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