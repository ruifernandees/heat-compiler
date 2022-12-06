#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <stack>

#include "syntactic-analyzer.h"

#include "./productions/_index.cpp"

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

// vector<var_scope> tabela_de_simbolos(vector<Token> tokens)
// {
//     vector<var_scope> symbols_table;

//     vector<Scope> block_keys = {{"def", "function"}, {"class", "class"}, {"if", "if"}, {"elsif", "elsif"}, {"else", "else"}, {"for", "for"}, {"while", "while"}, 
//     {"begin", "try"}, };
    
//     stack<Scope> escopos;
    
//     Scope padrao = newScope("padrao", "padrao");

//     for (int i = 0; i < tokens.size(); i++) {
//         scope_type(tokens, block_keys, &escopos, &i);

//         if (tokens[i].type.compare(IDENTIFIER) == 0) {
//             if (escopos.size() == 0) {
//                 symbols_table.push_back({tokens[i].content, {"padrao", "padrao"}});
//             } 
//             else {
//                 symbols_table.push_back({tokens[i].content, {escopos.top().name, escopos.top().type}});
//             }
//         }
        
//         if (tokens[i].content.compare("end") == 0) {
//             escopos.pop();
//         }

//     }

//     return symbols_table;

// }

int search_var(vector<var_scope> symbols_table, string var_name, string scope_name) {
    int i = 0;
    for (i = 0; i < symbols_table.size(); i++) {
        if (symbols_table[i].name.compare(var_name) == 0 && symbols_table[i].scope.name.compare(scope_name) == 0) 
            return i;
    }

    return -1;
}

int somar();
int subtrair();
int multiplicar();
int dividir();

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

vector<var_scope> tabela_de_simbolos1111(vector<Token> tokens)
{
    int pos = 0;
    vector<var_scope> symbols_table;

    vector<Scope> block_keys = {{"def", "function"}, {"class", "class"}, {"if", "if"}, {"elsif", "elsif"}, {"else", "else"}, {"for", "for"}, {"while", "while"}, 
    {"begin", "try"}, };
    
    stack<Scope> escopos;
    
    Scope padrao = {"padrao", "padrao"};
    for (int i = 0; i < tokens.size(); i++) {
        scope_type(tokens, block_keys, &escopos, &i);

        if (tokens[i].type.compare(IDENTIFIER) == 0) {            
            if (escopos.size() == 0) {
                pos = search_var(symbols_table, tokens[i].content, "padrao");
                if (pos == -1) {
                    symbols_table.push_back({tokens[i].content, 0, {"padrao", "padrao"}});
                    pos = symbols_table.size() - 1;
                }
                ++i;
                if (tokens[i].content.compare("=") == 0) {
                    atribuir(&symbols_table, tokens, &i, pos);
                }
                
            } 
            else {
                pos = search_var(symbols_table, tokens[i].content, escopos.top().name);
                if (pos == -1)
                    symbols_table.push_back({tokens[i].content, 0, {escopos.top().name, escopos.top().type}});
            }    
            // if (pos == -1) 
            //     symbols_table.push_back({tokens[i].name}, 0, "padrao");
            // else {
                
            // }


            // while (tokens[i].type.compare(DELIMITER) != 0) {
            // }
            
            
            
        }
        
        if (tokens[i].content.compare("end") == 0) {
            escopos.pop();
        }

    }

    return symbols_table;

}

void syntacticAnalyzer(vector<Token> tokens) {
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
        vector<var_scope> tabela = tabela_de_simbolos1111(tokens);
        cout << "TABELA DE SÍMBOLOS: \n";
        for (auto entry: tabela) {
            cout << entry.name << "=" << entry.value << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
        }
    }
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