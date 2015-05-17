#ifndef EXPRESSIONTOKEN_H
#define EXPRESSIONTOKEN_H

#include "Token.h"

class EqualityToken : public Token {
public:
    EqualityToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};
#endif // EXPRESSIONTOKEN_H
