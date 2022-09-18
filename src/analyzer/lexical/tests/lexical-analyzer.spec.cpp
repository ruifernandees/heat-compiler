#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../../../utils/read-file.cpp"
#include "../../../bnf/types.h"

#include "./hello-world.spec.cpp"
#include "./unrecognized-character.spec.cpp"
#include "./multiple-operators-and-delimiters.spec.cpp"

regex HELLO_WORLD_SUITE("./src/mocks/hello-world.rb");
regex UNRECOGNIZED_CHARACTER_SUITE("./src/mocks/unrecognized-character.rb");
regex DOUBLY_LINKED_LIST("./src/mocks/doubly-linked-list.rb");
regex MULTIPLE_OPERATORS_AND_DELIMITERS("./src/mocks/multiple-operators-and-delimiters.rb");

using namespace std;

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        cout << "Please provide a file name!" << endl;
        return 1;
    }
    string filename = argv[1];
    vector<string> script = readFile(filename);
    if (regex_match(filename, HELLO_WORLD_SUITE)) {
        bool result = shouldRecognizeHelloWorldCorrectly(script);
        cout << (result ? "[PASSED ✅]" : "[FAILED ❌]") << " hello world test" << endl;
    } else if (regex_match(filename, UNRECOGNIZED_CHARACTER_SUITE)) {
        bool result = shouldThrowIfThereIsAUnrecognizedCharacter(script);
        cout << (result ? "[PASSED ✅]" : "[FAILED ❌]") << " unrecognized character test" << endl;
    } else if (regex_match(filename, MULTIPLE_OPERATORS_AND_DELIMITERS)) {
        bool result = shouldRecognizeMultipleOperatorsAndDelimitersCorrectly(script);
        cout << (result ? "[PASSED ✅]" : "[FAILED ❌]") << " Multiple operators test" << endl;
    } else {
        cout << "No tests found." << endl;
    }
    return 0;
}