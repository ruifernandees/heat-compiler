#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

#define FILE_READING_ERROR "FILE_READING_ERROR"

using namespace std;


string readFile(string filename) {
    string line;
    string script;
    ifstream fileToRead(filename);
    if (fileToRead.is_open()) {
        while (getline(fileToRead, line)) {
            script += line + '\n';
        }
        fileToRead.close();
        return script;
    }
    return FILE_READING_ERROR;
}

int main(int argc, char *argv[]) {
    string filename = argv[1];
    string script = readFile(filename);
    if (script == FILE_READING_ERROR) {
        cout << "Reading file error!" << '\n';
        return 1;
    }
    cout << script << "\n";
    return 0;
}