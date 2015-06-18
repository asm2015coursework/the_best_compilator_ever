#ifndef FORTOKEN_H
#define FORTOKEN_H

#include "Token.h"

class ForToken : public Token {
public:
    ForToken(Token* expr1, Token* expr2, Token* expr3, Token* cmd);

    virtual string toString();
    virtual string getType();

    Token *expr1;
    Token *expr2;
    Token *expr3;
    Token *cmd;
};

#endif // FORTOKEN_H
