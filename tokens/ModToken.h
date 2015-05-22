#ifndef MODTOKEN_H
#define MODTOKEN_H

#include "Token.h"

class ModToken : public Token {
public:
    ModToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // MODTOKEN_H
