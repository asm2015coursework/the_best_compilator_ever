#ifndef ORTOKEN_H
#define ORTOKEN_H

#include "Token.h"

class OrToken : public Token {
public:
    OrToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // ORTOKEN_H
