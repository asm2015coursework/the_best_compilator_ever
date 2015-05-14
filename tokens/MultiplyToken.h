#ifndef MULTIPLYTOKEN_H
#define MULTIPLYTOKEN_H

#include "Token.h"

class MultiplyToken : public Token {
public:
    MultiplyToken(Token* left, Token* right);

    virtual string toString();

    Token *left;
    Token *right;
};

#endif // MULTIPLYTOKEN_H
