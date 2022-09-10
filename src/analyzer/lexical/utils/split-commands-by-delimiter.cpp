#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#pragma once

using namespace std;

vector<string> splitCommandsByDelimiter(vector<string> script, char delim) {
    vector<string> words;
    for (int i = 0; i < script.size(); i++)
    {
        stringstream ss(script[i]);
        string tok;
        while (getline(ss, tok, delim)) 
        {
            if (!tok.empty())
            {
                words.push_back(tok);
            }
        }
    }
    return words;
}