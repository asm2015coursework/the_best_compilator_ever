#ifndef RETURNTOKEN_H
#define RETURNTOKEN_H

#include "Token.h"

class ReturnToken : public Token {
public:
    ReturnToken(Token* expr);

    virtual string toString();
    virtual string getType();

    Token* expr;
};

#endif // RETURNTOKEN_H
