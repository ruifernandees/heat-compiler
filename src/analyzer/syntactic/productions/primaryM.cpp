#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
// include "./index.cpp"

#pragma once

using namespace std;



bool funcaoPrimaryMComAsterisco(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare("elsif") == 0) {
        if (eat(tokens, currentToken)) {
            if (expr(tokens, currentToken)) {
                if (then(tokens, currentToken)) {
                    if (compstmt(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    return false;
}

void tentarPrimaryMLer2(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        if (eat(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}
void tentarPrimaryMLer1(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        tentarPrimaryMLer2(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}


void tentarPrimaryMLer3(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (assocs(tokens, currentToken)) {
        tentarPrimaryMLer2(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryMLer5(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (call_args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryMLer4(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("(") == 0) {
        if (eat(tokens, currentToken)) {
            tentarPrimaryMLer5(tokens, currentToken);
            if (tokens[*currentToken].content.compare(")") == 0) {
                if (eat(tokens, currentToken)) {
                    return;
                }
            }
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryMLer7(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (block_var(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}
void tentarPrimaryMLer6(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("|") == 0) {
        if (eat(tokens, currentToken)) {
            tentarPrimaryMLer7(tokens, currentToken);
            if (tokens[*currentToken].content.compare("|") == 0) {
                if (eat(tokens, currentToken)) {
                    return;
                }
            }
        }
    }

    *currentToken = pstToken;
    return;
}


void tentarPrimaryMLer8(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("else") == 0) {
        if (eat(tokens, currentToken)) {
            if (compstmt(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryMLer9(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}


bool funcaoPrimaryMComMais(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare("rescue") == 0) {
        if (eat(tokens, currentToken)) {
            tentarPrimaryMLer9(tokens, currentToken);
            if (_do(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    return false;
}



void tentarPrimaryMLer10(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("ensure") == 0) {
        if (eat(tokens, currentToken)) {
            if (compstmt(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarPrimaryMLer11(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("<") == 0) {
        if (eat(tokens, currentToken)) {
            if (identifier(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

bool primaryM(vector<Token> tokens, int* currentToken) 
{
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 PRIMARY" << endl;
    int pastToken = *currentToken;

    // possibilidade 1
    if (tokens[*currentToken].content.compare("(") == 0) {
        if (eat(tokens, currentToken)) {
            if (compstmt(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare(")") == 0) {
                    if (eat(tokens, currentToken)) {
                        if (primaryL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 2
    //cout << "[PRIMARY CALLS] LITERAL" << endl;
    if (literal(tokens, currentToken)) {
        //cout << "[PRIMARY CALLS] PRIMARYL" << endl;
        
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    }
    
    *currentToken = pastToken;

    // possibilidade 3
    if (variable(tokens, currentToken)) {
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    };

    *currentToken = pastToken;

    // possibilidade 4
    if (tokens[*currentToken].content.compare("::") == 0) {
        if (eat(tokens, currentToken)) {
            if (identifier(tokens, currentToken)) {
                if (primaryL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 5
    if (tokens[*currentToken].content.compare("[") == 0) {
        if (eat(tokens, currentToken)) {
            tentarPrimaryMLer1(tokens, currentToken);
            
            if (tokens[*currentToken].content.compare("]") == 0) {
                if (eat(tokens, currentToken)) {
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }

                }
            }
        }
    }


    *currentToken = pastToken;

    // possibilidade 6
    if (tokens[*currentToken].content.compare("{") == 0) {
        if (eat(tokens, currentToken)) {
            tentarPrimaryMLer1(tokens, currentToken);
            if (tokens[*currentToken].content.compare("}") == 0) {
                if (eat(tokens, currentToken)) {
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }
    
    *currentToken = pastToken;

    // possibilidade 7
    if (tokens[*currentToken].content.compare("{") == 0) {
        if (eat(tokens, currentToken)) {
            tentarPrimaryMLer3(tokens, currentToken);
            if (tokens[*currentToken].content.compare("}") == 0) {
                if (eat(tokens, currentToken)) {
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 8
    if (tokens[*currentToken].content.compare("return") == 0) {
        if (eat(tokens, currentToken)) {
            tentarPrimaryMLer4(tokens, currentToken);
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }

    // // possibilidade 9
    // if (Function(tokens, currentToken)) {
    //     if (primaryL(tokens, currentToken)) {
    //         return true;
    //     }
    // }

    // *currentToken = pastToken;

    // // possibilidade 10
    // if (Function(tokens, currentToken)) {
    //     if (tokens[*currentToken].content.compare("{") == 0) {
    //         if (eat(tokens, currentToken)) {
    //             tentarPrimaryMLer6(tokens, currentToken);
    //             if (compstmt(tokens, currentToken)) {
    //                 if (tokens[*currentToken].content.compare("}") == 0) {
    //                     if (eat(tokens, currentToken)) {
    //                         if (primaryL(tokens, currentToken)) {
    //                             return true;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    *currentToken = pastToken;
    
    // possiblidade 11
    if (tokens[*currentToken].content.compare("if") == 0) {
        if (eat(tokens, currentToken)) {
            if (expr(tokens, currentToken)) {
                if (then(tokens, currentToken)) {
                    if (compstmt(tokens, currentToken)) {
                        while (funcaoPrimaryMComAsterisco(tokens, currentToken)) {}

                        tentarPrimaryMLer8(tokens, currentToken);

                        if (tokens[*currentToken].content.compare("end") == 0) {
                            if (eat(tokens, currentToken)) {
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
    
    *currentToken = pastToken;

    // possibilidade 11
    if (tokens[*currentToken].content.compare("while") == 0) {
        if (eat(tokens, currentToken)) {
            if (expr(tokens, currentToken)) {
                if (_do(tokens, currentToken)) {
                    if (compstmt(tokens, currentToken)) {
                        if (tokens[*currentToken].content.compare("end") == 0) {
                            if (eat(tokens, currentToken)) {
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

    *currentToken = pastToken;

    // possibilidade 11 -- REMOVIDA
    
    // possibilidade 12 
    if (tokens[*currentToken].content.compare("for") == 0) {
        if (eat(tokens, currentToken)) {
            if (block_var(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare("in") == 0) {
                    if (eat(tokens, currentToken)) {
                        if (expr(tokens, currentToken)) {
                            if (_do(tokens, currentToken)) {
                                if (compstmt(tokens, currentToken)) {
                                    if (tokens[*currentToken].content.compare("end") == 0) {
                                        if (eat(tokens, currentToken)) {
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
            }
        }
    }
    

    *currentToken = pastToken;

    // possibilidade 13
    if (tokens[*currentToken].content.compare("begin") == 0) {
        if (eat(tokens, currentToken)) {
            if (compstmt(tokens, currentToken)) {
                // bloco do + abaixo
                if (funcaoPrimaryMComMais(tokens, currentToken)) {

                    while (funcaoPrimaryMComMais(tokens, currentToken)) {}

                    tentarPrimaryMLer8(tokens, currentToken);
                    tentarPrimaryMLer10(tokens, currentToken);

                    if (tokens[*currentToken].content.compare("end") == 0) {
                        if (eat(tokens, currentToken)) {
                            if (primaryL(tokens, currentToken)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;
        
    // [rescue [ARGS] DO COMPSTMT]+

    // possibilidade 14
    if (tokens[*currentToken].content.compare("class") == 0) {
        if (eat(tokens, currentToken)) {
            if (identifier(tokens, currentToken)) {
                tentarPrimaryMLer11(tokens, currentToken);
                if (compstmt(tokens, currentToken)) {
                    if (tokens[*currentToken].content.compare("end") == 0) {
                        if (eat(tokens, currentToken)) {
                            if (primaryL(tokens, currentToken)) {
                                return true;
                            }
                        }
                    } 
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 15 
    if (tokens[*currentToken].content.compare("module") == 0) {
        if (eat(tokens, currentToken)) {
            if (identifier(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    if (tokens[*currentToken].content.compare("end") == 0) {
                        if (eat(tokens, currentToken)) {
                            if (primaryL(tokens, currentToken)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 16 aleluia
    if (tokens[*currentToken].content.compare("def") == 0) {
        if (eat(tokens, currentToken)) {
            if (fname(tokens, currentToken)) {
                if (argdecl(tokens, currentToken)) {
                    if (compstmt(tokens, currentToken)) {
                        if (tokens[*currentToken].content.compare("end") == 0) {
                            if (eat(tokens, currentToken)) {
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
    
    *currentToken = pastToken;

    return false;
}
