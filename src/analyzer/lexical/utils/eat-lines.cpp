#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <iostream>

#include "../../../bnf/types.h"

#pragma once

using namespace std;

vector<string> eat_first_blanks(vector<string> text) 
{
    vector<string> copia;
    int i = 0;
    do {
        i++;
    } while (text[i].size() == 0 || text[i].compare("\n") == 0);

    for (int j = i+1; j < text.size(); j++)
    {
        copia.push_back(text[j]);
    }

    return copia;
}