#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    string foo = "YES";
    // foo.push_back(1);
    // foo.push_back(2);
    // foo.push_back(3);
    // foo.push_back(4);
    for (char a : foo) {
        cout << a << endl;
    }
    cout << "======" << endl;
    foo.pop_back();
    for (char a : foo) {
        cout << a << endl;
    }
    return 0;
}