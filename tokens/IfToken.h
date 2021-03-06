#ifndef IFTOKEN_H
#define IFTOKEN_H

#include "Token.h"

class IfToken : public Token {
public:
    IfToken(Token* expr, Token* block1, Token* block2);

    virtual string toString();
    virtual string getType();

    Token* expr;
    Token* block1;
    Token* block2;
};

#endif // IFTOKEN_H
