#ifndef ANDTOKEN_H
#define ANDTOKEN_H

#include "Token.h"

class AndToken : public Token {
public:
    AndToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // ANDTOKEN_H
