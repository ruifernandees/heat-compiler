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

void scope_type(vector<var_scope> *symbols_table, vector<Token> tokens, vector<function_scope> *functions, vector<Scope> keywords, stack<Scope> *escopos, int* i) {
    for (auto key: keywords) {
        if (tokens[*i].content.compare(key.name) == 0) {
            if (key.name.compare("def") == 0) {
                string name_function = tokens[*i+1].content;
                *i = *i + 2; // pular o nome da funcao e parentesis
                int qnt_parametros = 0;
                while (tokens[*i].content.compare(")") != 0)
                {
                    if (tokens[*i].type.compare(IDENTIFIER) == 0)
                    {
                        symbols_table->push_back({tokens[*i].content, {}, {name_function, key.type}});
                        qnt_parametros++;
                    }
                    *i = *i + 1;
                }

                functions->push_back({-1, name_function, qnt_parametros, escopos->top()});
                escopos->push({name_function, key.type});
                return;
            }
            escopos->push({key});
            return;
        }
    }
}

vector<var_scope> tabela_de_simbolos(vector<Token> tokens, vector<function_scope> *functions)
{
    vector<var_scope> symbols_table;

    vector<Scope> block_keys = {{"def", "function"}, {"class", "class"}, {"if", "if"}, {"elsif", "elsif"}, {"else", "else"}, {"for", "for"}, {"while", "while"}, 
    {"begin", "try"}, };
    
    stack<Scope> escopos;
    Scope padrao = newScope("padrao", "padrao");
    escopos.push(padrao);

    for (int i = 0; i < tokens.size(); i++) {
        scope_type(&symbols_table, tokens, functions, block_keys, &escopos, &i);
    
        if (tokens[i].content.compare("=") == 0) {
            if (!findPositionInSymbolTableByContentAndSameScope(symbols_table, tokens[i-1].content, escopos.top()))
            {
                vector<string> p;
                symbols_table.push_back({tokens[i-1].content, p, {escopos.top().name, escopos.top().type}});
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
    if (sem_erros) {
        cout << "Análise sintática concluida com sucesso\n";

        vector<function_scope> functions;
        vector<var_scope> tabela = tabela_de_simbolos(tokens, &functions);
        cout << "TABELA DE SIMBOLOS: \n";
        cout << "name"<< " | " << "value"<< " | " << "scope name"<< " [" << "scope type"<< "]\n";
        for (auto entry: tabela) {
            cout << entry.name << " | ";
            for (auto value : entry.value)
            {
                cout << value << " ";
            }
            cout << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
        }

        cout << "FUNCTIONS" << endl;
        for (auto entry: functions) {
            cout << entry.name << " | " << entry.qnt_argumentos << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
        }

        // semantic(tabela);
        semantic(tokens, tabela, functions);

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