#ifndef INITIALIZATIONTOKEN_H
#define INITIALIZATIONTOKEN_H

#include "Token.h"

class InitializationToken : public Token {
public:
    InitializationToken(string type, string name, Token* expr, Token* size);

    virtual string toString();
    virtual string getType();

    string _name;
    string _type;
    Token *_expr;
    Token *_size;
};

#endif // INITIALIZATIONTOKEN_H
