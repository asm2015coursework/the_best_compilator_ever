#ifndef ADDTOKEN_H
#define ADDTOKEN_H

#include "Token.h"

class AddToken : public Token {
public:
    AddToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};

#endif // ADDTOKEN_H
