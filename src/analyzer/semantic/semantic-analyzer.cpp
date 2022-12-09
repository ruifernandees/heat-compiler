#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <stack>

#include "../../bnf/types.h"

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

int search_var(vector<var_scope> symbols_table, string var_name, string scope_name) {
    int i = 0;
    for (i = 0; i < symbols_table.size(); i++) {
        if (symbols_table[i].name.compare(var_name) == 0 && symbols_table[i].scope.name.compare(scope_name) == 0) 
            return i;
    }

    return -1;
}

void atribuir(vector<var_scope>* st, vector<Token> tokens, int pos_st)
{
    // = st->at(pos_st);
    
    int valor = 0, idx = 0;
    // cout << "pos_st:" << pos_st << "\n";
    // POS_TK = 0
    // X = 1\n
    // X = 2
    int current_position_st = 0;
    var_scope var;
    for (auto token : tokens)
    {
        if (token.type.compare(IDENTIFIER) == 0) {
            cout << "IDENTIFIER " << endl;
            for (int i = 0; i < st->size(); i++) {
                if (token.content.compare(st->at(i).name) == 0)  {
                    current_position_st = i;
                    cout << "-> " << current_position_st << endl;
                    var = st->at(i);
                    break;
                }
            }
            cout << "AFTER IDENTIFIER " << endl;
            idx = search_var(*st, var.name, var.scope.name);
            if (idx == -1) {
                cout << "ERRO: Variável " << token.content << "não declarada no escopo " << var.scope.name << "\n";
                exit(1);
            }
            else {
                var.value = st->at(idx).value;
            }
        }
        else if (token.type.compare(NUMBER) == 0) {
            var.value = stoi(token.content);
        }
        else if (token.type.compare(KEYWORD) == 0) {
            cout << "KEYWORD " << token.content << endl;
        }

        // ideia: escolher a funcao adequada segundo o operador. o problema está nas operações mais complexas
        // outra ideia: já que é uma atribuição, atualizar o valor da variavel em pos_var a cada num/identificador lido
        // assim voce pode realizar operacoes com a propria variavel principal pq é só ir acumulando
    }
    cout << "valor de {" << var.name << "}: " << var.value << "\n";
    
    st->at(current_position_st) = var;
    cout << "[adasdas] " << st->at(current_position_st).name << ", " << st->at(current_position_st).scope.name << ", " << st->at(current_position_st).value << endl;
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

void semanticAnalyzer(vector<Token> tokens, vector<var_scope> tabela) {
    vector<vector<Token>> comandos = catch_lines(tokens);
    int pos_symbol_table = 0;
    int pos_token = 0;

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
    
    for (auto comando : comandos)
    {
        atribuir(&tabela, comando, pos_symbol_table);
    }
    // atribuir(&tabela, tokens, &pos_token, pos_symbol_table);
    // cout << "🔌" << st->at(current_position_st).name << ", " << st->at(current_position_st).scope.name << ", " << st->at(current_position_st).value << endl;
    cout << "TABELA DE SIMBOLOS - SEMANTICO: \n";
    cout << "name"<< " | " << "value"<< " | " << "scope name"<< " [" << "scope type"<< "]\n";
    for (auto entry: tabela) {
        cout << entry.name << " | " << entry.value << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
    }
}