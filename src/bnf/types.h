#include <string>
#include <cstring>

#define KEYWORD "KEYWORD"
#define IDENTIFIER "IDENTIFIER"
#define OPERATOR "OPERATOR"
#define DELIMITER "DELIMITER"
#define NUMBER "NUMBER"

#define ONE_LINE_COMMENT '#'



#pragma once

using namespace std;

const string MULTIPLE_LINE_COMMENT_BEGIN = "=begin";
const string MULTIPLE_LINE_COMMENT_END = "=end";

typedef struct aux {
  string content;
  string type;    
} Token;