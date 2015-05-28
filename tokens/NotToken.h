#ifndef NOTTOKEN_H
#define NOTTOKEN_H

#include "Token.h"

class NotToken : public Token {
public:
    NotToken(Token *expr);

    virtual string toString();
    virtual string getType();

    Token* expr;
};
#endif // NOTTOKEN_H
