#ifndef LOWERTOKEN_H
#define LOWERTOKEN_H

#include "Token.h"

class LowerToken : public Token {
public:
    LowerToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // LOWERTOKEN_H
