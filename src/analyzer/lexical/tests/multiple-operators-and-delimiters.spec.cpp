#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "../lexical-analyzer.cpp"
#include "../utils/factories.cpp"
#include "../../../bnf/types.h"

vector<Token> expectedVectorMultipleOperatorsFactory() {
    vector<Token> allTokens;
    allTokens.push_back(identifierTokenObjectFactory("age"));
    allTokens.push_back(operatorsTokenObjectFactory("+="));
    allTokens.push_back(operatorsTokenObjectFactory("-"));
    allTokens.push_back(numberTokenObjectFactory("1"));
    allTokens.push_back(keywordTokenObjectFactory("when"));
    allTokens.push_back(numberTokenObjectFactory("1"));
    allTokens.push_back(operatorsTokenObjectFactory("..."));
    allTokens.push_back(operatorsTokenObjectFactory("@"));
    allTokens.push_back(identifierTokenObjectFactory("size"));
    allTokens.push_back(keywordTokenObjectFactory("until"));
    allTokens.push_back(identifierTokenObjectFactory("iter"));
    allTokens.push_back(operatorsTokenObjectFactory("."));
    allTokens.push_back(keywordTokenObjectFactory("nil")); // TTT
    allTokens.push_back(operatorsTokenObjectFactory("?")); // TTT
    allTokens.push_back(delimiterTokenObjectFactory(";"));
    allTokens.push_back(identifierTokenObjectFactory("insert"));
    allTokens.push_back(delimiterTokenObjectFactory("("));
    allTokens.push_back(identifierTokenObjectFactory("iter"));
    allTokens.push_back(delimiterTokenObjectFactory(","));
    allTokens.push_back(identifierTokenObjectFactory("Node"));
    allTokens.push_back(operatorsTokenObjectFactory(".")); 
    allTokens.push_back(identifierTokenObjectFactory("new")); 
    allTokens.push_back(delimiterTokenObjectFactory("("));
    allTokens.push_back(identifierTokenObjectFactory("val"));
    allTokens.push_back(delimiterTokenObjectFactory(")"));
    allTokens.push_back(delimiterTokenObjectFactory(")"));
    allTokens.push_back(identifierTokenObjectFactory("remove"));
    allTokens.push_back(delimiterTokenObjectFactory("("));
    allTokens.push_back(operatorsTokenObjectFactory("@"));
    allTokens.push_back(identifierTokenObjectFactory("head"));
    allTokens.push_back(delimiterTokenObjectFactory(")"));
    allTokens.push_back(identifierTokenObjectFactory("age"));
    allTokens.push_back(operatorsTokenObjectFactory("="));
    allTokens.push_back(keywordTokenObjectFactory("nil"));
    allTokens.push_back(keywordTokenObjectFactory("def"));
    allTokens.push_back(operatorsTokenObjectFactory("[]="));
    allTokens.push_back(delimiterTokenObjectFactory("("));
    allTokens.push_back(identifierTokenObjectFactory("key"));
    allTokens.push_back(delimiterTokenObjectFactory(","));
    allTokens.push_back(identifierTokenObjectFactory("val"));
    allTokens.push_back(delimiterTokenObjectFactory(")"));
    allTokens.push_back(keywordTokenObjectFactory("end"));
    return allTokens;
}

bool shouldRecognizeMultipleOperatorsAndDelimitersCorrectly(vector<string> script) {
    try
    {
        vector<Token> expectedTokens = expectedVectorMultipleOperatorsFactory();
        vector<Token> tokens = lexicalAnalyzer(script);
        for (int i = 0; i < tokens.size(); i++) {
            // cout << tokens[i].content << " vs " << expectedTokens[i].content << endl << tokens[i].type << " vs " << expectedTokens[i].type << endl;
            // cout << "< " << tokens[i].content << ", " << tokens[i].type << " >" << endl;
            if (
                tokens[i].content.compare(expectedTokens[i].content) != 0
                || tokens[i].type.compare(expectedTokens[i].type) != 0
            ) {
                return false;
            }
        }
        cout << endl;
        return true;        
    }
    catch (const runtime_error& error)
    {
        cout << error.what() << endl;
        return false;
    }

}