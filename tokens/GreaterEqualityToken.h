#ifndef GREATEREQUALITYTOKEN_H
#define GREATEREQUALITYTOKEN_H

#include "Token.h"

class GreaterEqualityToken : public Token {
public:
    GreaterEqualityToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // GREATEREQUALITYTOKEN_H
