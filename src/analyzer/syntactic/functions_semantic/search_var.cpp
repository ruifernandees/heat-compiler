#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../semantic-analyzer.h"

int search_var(vector<var_scope> symbols_table, string var_name, string scope_name) {
    int i = 0;
    for (i = 0; i < symbols_table.size(); i++) {
        if (symbols_table[i].name.compare(var_name) == 0 && symbols_table[i].scope.name.compare(scope_name) == 0) 
            return i;
    }
    
    return -1;
}