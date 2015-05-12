#ifndef PARSER_H
#define PARSER_H

#include <tokens/Token.h>
#include "Result.h"
#include "ParsingException.h"
#include "../tokens/InitializationToken.h"
#include "../tokens/FunctionToken.h"
#include "../tokens/EqualityToken.h"

using std::pair;

class Parser {
public:
    Parser();
    vector<Token*> parse(string code);
private:
    pair<string, int> nameParse(size_t x);
    Result commandParse(size_t x);
    bool nameSymbol(char c);
    bool nameFirstSymbol(char c);
    bool letter(char c);

    vector<Token*> ans;
    string str;
};

#endif // PARSER_H
