#ifndef STRINGTOKEN_H
#define STRINGTOKEN_H

#include "Token.h"

class StringToken : public Token {
public:
    StringToken(string str);

    virtual string toString();
    virtual string getType();

    string str;
};

#endif // STRINGTOKEN_H
