#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

using namespace std;

regex keywords ("do|end|undef|alias|if|then|else|elsif|case|while|for|in|begin|rescue|ensure|class|def|unless|until|return|yield|and|or|not|super|defined?|nil|self");

bool isAKeyword(string word) {
  return !!regex_match(word, keywords);
}