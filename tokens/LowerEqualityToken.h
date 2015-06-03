#ifndef LOWEREQUALITYTOKEN_H
#define LOWEREQUALITYTOKEN_H

#include "Token.h"

class LowerEqualityToken : public Token {
public:
    LowerEqualityToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};
#endif // LOWEREQUALITYTOKEN_H
