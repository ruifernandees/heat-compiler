#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "identifiers.h"
#include "types.h"

using namespace std;

vector<char> identifierEndCharacters;

/**
 * @brief 
 * 
 * Com esses caracteres, o identificador é um nome de um método de uma classe
 */
void initializeEndCharactersVector() {
    identifierEndCharacters.push_back('?');
    identifierEndCharacters.push_back('!');
}

bool isAnIdentifierEndCharacter(char endCharacter) {
    if (identifierEndCharacters.size() == 0) {
        initializeEndCharactersVector();
    }
    for (int i = 0; i < identifierEndCharacters.size(); i++){
        if (identifierEndCharacters[i] == endCharacter) return true;
    }
    return false;
}