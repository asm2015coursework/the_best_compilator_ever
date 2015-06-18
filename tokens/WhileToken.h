#ifndef WHILETOKEN_H
#define WHILETOKEN_H

#include "Token.h"

class WhileToken : public Token {
public:
    WhileToken(Token* expr, Token* cmd);

    virtual string toString();
    virtual string getType();

    Token* expr;
    Token* cmd;
};

#endif // WHILETOKEN_H
