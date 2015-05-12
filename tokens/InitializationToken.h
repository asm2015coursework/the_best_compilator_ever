#ifndef INITIALIZATIONTOKEN_H
#define INITIALIZATIONTOKEN_H

#include "Token.h"

class InitializationToken : public Token {
public:
    InitializationToken(string type, string name, Token* expr);

    virtual string toString();

    string _name;
    string _type;
    Token *_expr;
};

#endif // INITIALIZATIONTOKEN_H
