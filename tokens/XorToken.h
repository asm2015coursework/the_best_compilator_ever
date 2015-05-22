#ifndef XORTOKEN_H
#define XORTOKEN_H

#include "Token.h"

class XorToken : public Token {
public:
    XorToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // XORTOKEN_H
