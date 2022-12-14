#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
// include "./index.cpp"

#pragma once

using namespace std;

bool funcaoPrimaryComAsterisco(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    if (verify_content(tokens, currentToken, "elsif")) {
        if (expr(tokens, currentToken)) {
            if (then(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    return false;
}

void tentarPrimaryLer2(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer1(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        tentarPrimaryLer2(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer3(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (assocs(tokens, currentToken)) {
        tentarPrimaryLer2(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer5(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (call_args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer4(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "(")) {
        tentarPrimaryLer5(tokens, currentToken);
        if (verify_content(tokens, currentToken, ")")) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer7(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (block_var(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer6(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "|")) {
        tentarPrimaryLer7(tokens, currentToken);
        if (verify_content(tokens, currentToken, "|")) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer8(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;
    
    if (verify_content(tokens, currentToken, "else")) {
        if (tokens[*currentToken].content.compare("\n") == 0) {
            eat(tokens, currentToken);
        }
        if (compstmt(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer9(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

bool funcaoComMais(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (verify_content(tokens, currentToken, "rescue")) {
        tentarPrimaryLer9(tokens, currentToken);
        if (_do(tokens, currentToken)) {
            if (compstmt(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    return false;
}

void tentarPrimaryLer10(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "ensure")) {
        if (compstmt(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryLer11(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "<")) {
        if (identifier(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

bool primary1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (verify_content(tokens, currentToken, "(")) {
        if (compstmt(tokens, currentToken)) {
            if (verify_content(tokens, currentToken, ")")) {
                if (primaryL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool primary2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2
    if (literal(tokens, currentToken)) {
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool primary3(vector<Token> tokens, int* currentToken)
{
    // possibilidade 3
    if (variable(tokens, currentToken)) {
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool primary4(vector<Token> tokens, int* currentToken)
{
    // possibilidade 4
    if (verify_content(tokens, currentToken, "::")) {
        if (identifier(tokens, currentToken)) {
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool primary5(vector<Token> tokens, int* currentToken)
{
    // possibilidade 5
    if (verify_content(tokens, currentToken, "[")) {
        tentarPrimaryLer1(tokens, currentToken); 
        if (verify_content(tokens, currentToken, "]")) {
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool primary6(vector<Token> tokens, int* currentToken)
{
    // possibilidade 6
    if (verify_content(tokens, currentToken, "{")) {
        tentarPrimaryLer1(tokens, currentToken);
        if (verify_content(tokens, currentToken, "}")) {
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool primary7(vector<Token> tokens, int* currentToken)
{
    // possibilidade 7
    if (verify_content(tokens, currentToken, "{")) {
        tentarPrimaryLer3(tokens, currentToken);
        if (verify_content(tokens, currentToken, "}")) {
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }
    return false;
}

bool primary8(vector<Token> tokens, int* currentToken)
{
    // possibilidade 8
    if (verify_content(tokens, currentToken, "return")) {
        tentarPrimaryLer4(tokens, currentToken);
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool primary9(vector<Token> tokens, int* currentToken)
{
    // possibilidade 9
    if (Function(tokens, currentToken)) {
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool primary10(vector<Token> tokens, int* currentToken)
{
    // possibilidade 10
    if (Function(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, "{")) {
            tentarPrimaryLer6(tokens, currentToken);
            if (compstmt(tokens, currentToken)) {
                if (verify_content(tokens, currentToken, "}")) {
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool primary11(vector<Token> tokens, int* currentToken)
{
    // possiblidade 11
    if (verify_content(tokens, currentToken, "if")) {
        if (expr(tokens, currentToken)) {
            if (then(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    while (funcaoPrimaryComAsterisco(tokens, currentToken)) {}

                    tentarPrimaryLer8(tokens, currentToken);

                    if (verify_content(tokens, currentToken, "end")) {
                        if (primaryL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool primary12(vector<Token> tokens, int* currentToken)
{
    // possibilidade 12
    if (verify_content(tokens, currentToken, "while")) {
        if (expr(tokens, currentToken)) {
            if (_do(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    if (verify_content(tokens, currentToken, "end")) {
                        if (primaryL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool primary13(vector<Token> tokens, int* currentToken)
{
    // possibilidade 13
    if (verify_content(tokens, currentToken, "for")) {
        if (block_var(tokens, currentToken)) {
            if (verify_content(tokens, currentToken, "in")) {
                if (expr(tokens, currentToken)) {
                    if (_do(tokens, currentToken)) {
                        if (compstmt(tokens, currentToken)) {
                            if (verify_content(tokens, currentToken, "end")) {
                                if (primaryL(tokens, currentToken)) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool primary14(vector<Token> tokens, int* currentToken)
{
    // possibilidade 14
    if (verify_content(tokens, currentToken, "begin")) {
        if (compstmt(tokens, currentToken)) {
            // bloco do + abaixo
            if (funcaoComMais(tokens, currentToken)) {

                while (funcaoComMais(tokens, currentToken)) {}

                tentarPrimaryLer8(tokens, currentToken);
                tentarPrimaryLer10(tokens, currentToken);

                if (verify_content(tokens, currentToken, "end")) {
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool primary15(vector<Token> tokens, int* currentToken)
{
    // possibilidade 15
    if (verify_content(tokens, currentToken, "class")) {
        if (identifier(tokens, currentToken)) {
            if (tokens[*currentToken].content[0] == '\n') {
                if (eat(tokens, currentToken)) {
                    tentarPrimaryLer11(tokens, currentToken);
                    if (compstmt(tokens, currentToken)) {
                        if (verify_content(tokens, currentToken, "end")) {
                            if (primaryL(tokens, currentToken)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool primary16(vector<Token> tokens, int* currentToken)
{
    // possibilidade 16
    if (verify_content(tokens, currentToken, "module")) {
        if (identifier(tokens, currentToken)) {
            if (compstmt(tokens, currentToken)) {
                if (verify_content(tokens, currentToken, "end")) {
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool primary17(vector<Token> tokens, int* currentToken)
{
    // possibilidade 17 aleluia
    if (verify_content(tokens, currentToken, "def")) {
        if (fname(tokens, currentToken)) {
            if (argdecl(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    if (verify_content(tokens, currentToken, "end")) {
                        if (primaryL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool primary(vector<Token> tokens, int* currentToken)
{
    return verify_productions(tokens, currentToken, {primary1, primary2, primary3, primary4, primary5, primary6, primary7, primary8, primary9,
                                                     primary10, primary11, primary12, primary13, primary14, primary15, primary16, primary17});
}
