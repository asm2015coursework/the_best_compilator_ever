#ifndef SUBTRACTTOKEN_H
#define SUBTRACTTOKEN_H

#include "Token.h"

class SubtractToken : public Token {
public:
    SubtractToken(Token* left, Token* right);

    virtual string toString();

    Token *left;
    Token *right;
};
#endif // SUBTRACTTOKEN_H
