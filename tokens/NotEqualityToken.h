#ifndef NOTEQUALITYTOKEN_H
#define NOTEQUALITYTOKEN_H

#include "Token.h"

class NotEqualityToken : public Token {
public:
    NotEqualityToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};
#endif // NOTEQUALITYTOKEN_H
