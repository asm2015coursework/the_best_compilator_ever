#ifndef GREATERTOKEN_H
#define GREATERTOKEN_H

#include "Token.h"

class GreaterToken : public Token {
public:
    GreaterToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // GREATERTOKEN_H
