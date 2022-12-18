#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../semantic-analyzer.h"

bool existe(vector<function_scope> *functions, string name_function, int linha, Scope escopo_atual, int qnt_argumentos)
{
    //cout << "qnt: " << qnt_argumentos << endl;
    int idf = search_function(*functions, name_function, escopo_atual.name, qnt_argumentos);
    //cout << "IDF " << idf << endl;

    if (idf == -1)  return false;
    return functions->at(idf).linha != -1;
}