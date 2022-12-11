#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

#include "./utils/read-file.cpp"
#include "./analyzer/lexical/lexical-analyzer.h"
#include "./analyzer/syntactic/syntactic-analyzer.h"
#include "./analyzer/semantic/semantic-analyzer.h"
#include "./bnf/types.h"

using namespace std;

void lexicalAndSyntatic(string filename) {

    vector<string> script = readFile(filename);
    vector<Token> tokens = lexicalAnalyzer(script);
    for (Token token : tokens) {
        if (token.content.compare("\n") == 0) {
            cout << "< " << "LB" << ", " << token.type << " >" << endl;
        } else {
            cout << "< " << token.content << ", " << token.type << " >" << endl;
        }
    }
    vector<var_scope> symbol_table;
    syntacticAnalyzer(tokens, &symbol_table);

    cout << "(0)" << endl;

    ofstream SymbolTableFile("./symbol-table.txt");
    for (auto entry: symbol_table) {
        SymbolTableFile << entry.name << "|" << entry.value << "|" << entry.scope.name  << "|" << entry.scope.type << "\n";
    }
    SymbolTableFile.close();

    ofstream TokensFile("./tokens.txt");
    for (auto entry: symbol_table) {
        // TokensFile << entry.name << " | " << entry.value << " | " << entry.scope.name  << " [" << entry.scope.type << "]\n";
        for (Token token : tokens) {
            if (token.content.compare("\n") == 0) {
                TokensFile << "< " << "LB" << ", " << token.type << " >" << endl;
            } else {
                TokensFile << "< " << token.content << ", " << token.type << " >" << endl;
            }
        }
    }
    TokensFile.close();

    cout << "sai (0)" << endl;
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        cout << "Please provide a file name!" << endl;
        return 1;
    }
    if (argv[2] == NULL) {
        cout << "Please provide a mode!" << endl;
        return 1;
    }
    string filename = argv[1];
    string mode = argv[2];
    if (mode.compare("LS") == 0) {
        lexicalAndSyntatic(filename);
    } else if (mode.compare("SEMANTIC") == 0)
    {
        string text;
        string str;
        stringstream ss(text);
        char separator = '|';
        vector <string> result;
        while(getline(str, ss, separator)){
            result.pushback(str);
        }
        cout << "SEMANTIC" << endl;
    }
    return 0;
}