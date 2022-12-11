#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <stack>

#include "syntactic-analyzer.h"

#include "./productions/_index.cpp"
#include "./semantic-analyzer.cpp"

using namespace std;

Scope newScope(string name, string type)
{
    Scope novo;
    novo.name = name;
    novo.type = type;

    return novo;
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