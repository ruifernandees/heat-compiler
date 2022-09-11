#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "keywords.h"
#include "types.h"

using namespace std;

regex keywords ("do|end|undef|alias|if|then|else|elsif|case|while|for|in|begin|rescue|ensure|class|def|unless|until|return|yield|and|or|not|super|defined?|nil|self");

bool acceptIdentifier(string word) {
  return !!regex_match(word, keywords);
}