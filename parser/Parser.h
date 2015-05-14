#ifndef PARSER_H
#define PARSER_H

#include <tokens/Token.h>
#include "ParsingException.h"
#include "../tokens/InitializationToken.h"
#include "../tokens/FunctionToken.h"
#include "../tokens/EqualityToken.h"
#include "../tokens/VariableToken.h"
#include "../tokens/BlockToken.h"
#include "../tokens/ConstToken.h"
#include "../tokens/AddToken.h"
#include "../tokens/SubtractToken.h"
#include "../tokens/MultiplyToken.h"
#include "../tokens/DivideToken.h"

using std::pair;

class Parser {
public:
    Parser();
    vector<Token*> parse(string code);
private:    
    pair<Token*, size_t> blockParse(size_t x);
    pair<Token*, size_t> commandParse(size_t x);
    pair<Token*, size_t> expressionParse(size_t x);
    pair<Token*, size_t> LexemParse(size_t x);
    pair<string, int> nameParse(size_t x);
    bool nameSymbol(char c);
    bool nameFirstSymbol(char c);
    bool letter(char c);

    vector<Token*> ans;
    string str;
};

#endif // PARSER_H
