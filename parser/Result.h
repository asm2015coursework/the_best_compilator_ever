#ifndef RESULT_H
#define RESULT_H

#include <tokens/Token.h>

class Result {
public:
    Result(Token *acc, size_t rest);

    Token *acc;
    size_t rest;
};

#endif // RESULT_H
