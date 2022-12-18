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
    for (i = 0; i < symbols_table.size(); i++) {
        if (symbols_table[i].name.compare(var_name) == 0 && symbols_table[i].scope.name.compare(scope_name) == 0) 
            return i;
    }
    
    return -1;
}

int search_function(vector<function_scope> functions_table, string function_name, string scope_name, int qnt_argumentos) {
    int i = 0;
    for (i = 0; i < functions_table.size(); i++) {
        if (functions_table[i].name.compare(function_name) == 0 && functions_table[i].scope.name.compare(scope_name) == 0 && functions_table[i].qnt_argumentos == qnt_argumentos) 
            return i;
    }
    
    return -1;
}

void atribuir(vector<var_scope>* st, vector<Token> tokens, Scope escopo_atual, int i)
{
    // x = 23
    int idx = search_var(*st, tokens[i-1].content, escopo_atual.name);

    vector<string> value;
    
    for (int j = i + 1; j < tokens.size(); j++)
    {
        if (tokens[j].type.compare(IDENTIFIER) == 0)
        {
            int id = search_var(*st, tokens[j].content, escopo_atual.name);

            if (id == -1) {
                cout << "erro atribuindo variavel nao existente" << endl;
                exit(0);
            } else {
                // vetor vazio, nao aconteceu atribuicao
                if (st->at(id).value.size() == 0)
                {
                    cout << "erro atribuindo variavel nao existente" << endl;
                    exit(0);
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

void scope_type_semantic(vector<Token> tokens, vector<Scope> keywords, stack<Scope> *escopos, int* i, vector<function_scope> *functions, int linha) {
    for (auto key: keywords) {
        if (tokens[*i].content.compare(key.name) == 0) {
            if (key.name.compare("def") == 0) {

                int qnt_parametros = 0;
                int a = *i + 2;
                while (tokens[a].content.compare(")") != 0)
                {
                    if (tokens[a].type.compare(IDENTIFIER) == 0)
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

bool existe(vector<function_scope> *functions, string name_function, int linha, Scope escopo_atual, int qnt_argumentos)
{
    //cout << "qnt: " << qnt_argumentos << endl;
    int idf = search_function(*functions, name_function, escopo_atual.name, qnt_argumentos);
    //cout << "IDF " << idf << endl;

    if (idf == -1)  return false;
    return functions->at(idf).linha != -1;
}

vector<string> executar_funcao(vector<var_scope> *st, function_scope function, vector<var_scope> parametros, vector<vector<Token>> comandos, int linha_funcao)
{
    Scope escopo_atual = {function.name, "function"};
    cout << "funcao: " << function.name << endl;

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
                st->push_back({c.content, parametros[parametro].value, escopo_atual, 0});
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
                    int id = search_var(*st, comandos[i][j].content, escopo_atual.name);

                    if (id == -1) {
                        cout << "variavel nao existente no retorno da funcao" << endl;
                        exit(0);
                    } else {
                        // vetor vazio, nao aconteceu atribuicao
                        if (st->at(id).value.size() == 0)
                        {
                            cout << "variavel nao existente no retorno da funcao" << endl;
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
                atribuir(st, comandos[i], escopo_atual, j);
            }
            else if (comandos[i][j].content.compare("return") == 0)
            {
                retorno = true;
            }
            else if (comandos[i][j].content.compare("end") == 0)
            {
                cout << "end function" << endl;
                cout << "return value: ";

                for (auto v : value)
                {
                    cout << v << " ";
                }
                cout << endl;

                return value;
            }
            cout << comandos[i][j].content << " ";
        }
        cout << endl;
    }

    return value;
}

void call_fn(vector<Token> tokens, vector<vector<Token>> comandos, vector<function_scope> *functions, vector<var_scope> *st, int linha, int current_token, Scope escopo_atual)
{
    int qnt_parametros = 0;
    vector<var_scope> parametros;

    int i = current_token + 1;
    while (i < tokens.size())
    {
        if (tokens[i].type.compare(IDENTIFIER) == 0)
        {
            int id = search_var(*st, tokens[i].content, escopo_atual.name);
            if (id == -1) {
                cout << "variavel " << tokens[i].content << " nao existente passada na funcao" << endl;
                exit(0);
            }
            qnt_parametros++;
            parametros.push_back(st->at(id));
        }
        i = i + 1;
    }

    if (existe(functions, tokens[current_token].content, linha, escopo_atual, qnt_parametros))
    {
        cout << "existe a funcao " << tokens[current_token].content << endl;

        int idf = search_function(*functions, tokens[current_token].content, escopo_atual.name, qnt_parametros);
        executar_funcao(st, functions->at(idf), parametros, comandos, idf);
    }
    else
    {
        // ERRO
        cout << "nao existe a funcao " << tokens[current_token].content << endl;
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
            atribuir(st, tokens, escopos->top(), i);
        }

        else if (tokens[i].type.compare(IDENTIFIER) == 0)
        {
            if (i + 1 < tokens.size() && tokens[i+1].type.compare(IDENTIFIER) == 0)
            {
                call_fn(tokens, comandos, functions, st, linha, i, escopos->top());
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