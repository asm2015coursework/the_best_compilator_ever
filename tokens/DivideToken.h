#ifndef DIVIDETOKEN_H
#define DIVIDETOKEN_H

#include "Token.h"

class DivideToken : public Token {
public:
    DivideToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // DIVIDETOKEN_H
