#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "lexical-analyzer.h"

using namespace std;

vector<string> recognize(vector<string> script) {
        vector<string> words;
        for (int i = 0; i < script.size(); i++)
        {
            stringstream ss(script[i]);
            char delim=';';
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