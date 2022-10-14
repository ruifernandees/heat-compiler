#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "keywords.h"
#include "types.h"

using namespace std;

regex keywords ("do|end|when|if|then|else|elsif|case|while|for|in|begin|rescue|ensure|class|def|return|super|nil|self|private|public|protected");

bool isAKeyword(string word) {
  return !!regex_match(word, keywords);
}
