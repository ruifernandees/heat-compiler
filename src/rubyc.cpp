#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "./utils/read-file.cpp"
#include "./analyzer/lexical/lexical-analyzer.h"
#include "./analyzer/syntactic/main.cpp"
#include "./analyzer/semantic/main.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        cout << "Please provide a file name!" << endl;
        return 1;
    }
    string filename = argv[1];
    vector<string> script = readFile(filename);
    lexicalAnalyzer(script);
    syntacticAnalyzer();
    semanticAnalyzer();
    return 0;
}