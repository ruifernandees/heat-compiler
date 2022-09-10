#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "../lexical-analyzer.cpp"
#include "../utils/factories.cpp"
#include "../../../bnf/types.h"


bool shouldThrowIfThereIsAUnrecognizedCharacter(vector<string> script) {
    try
    {
        vector<Token> tokens = lexicalAnalyzer(script);
        return false;
    }
    catch(const std::exception& e)
    {
        return true;
    }
}