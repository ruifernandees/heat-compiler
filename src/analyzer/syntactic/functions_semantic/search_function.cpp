#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../semantic-analyzer.h"

int search_function(vector<function_scope> functions_table, string function_name, string scope_name, int qnt_argumentos) {
    int i = 0;
    for (i = 0; i < functions_table.size(); i++) {
        if (functions_table[i].name.compare(function_name) == 0 && functions_table[i].scope.name.compare(scope_name) == 0 && functions_table[i].qnt_argumentos == qnt_argumentos) 
            return i;
    }
    
    return -1;
}