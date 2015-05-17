#ifndef PARSER_H
#define PARSER_H

#include <tokens/Token.h>
#include "ParsingException.h"
#include "../tokens/InitializationToken.h"
#include "../tokens/FunctionToken.h"
#include "../tokens/EqualityToken.h"
#include "../tokens/VariableToken.h"
#include "../tokens/BlockToken.h"
#include "../tokens/ConstIntToken.h"
#include "../tokens/AddToken.h"
#include "../tokens/SubtractToken.h"
#include "../tokens/MultiplyToken.h"
#include "../tokens/DivideToken.h"
#include "../tokens/AssignmentToken.h"
#include "../tokens/OrToken.h"
#include "../tokens/AndToken.h"
#include "../tokens/DereferenceToken.h"
#include "../tokens/AddressToken.h"
#include "../tokens/UnaryMinusToken.h"
#include "../tokens/UnaryPlusToken.h"
#include "../tokens/ReturnToken.h"

using std::pair;

class Parser {
public:
    Parser();
    vector<Token*> parse(string code);
private:    
    pair<Token*, size_t> blockParse(size_t x);
    pair<Token*, size_t> commandParse(size_t x);
    pair<Token*, size_t> expressionParse(size_t x);
    pair<Token*, size_t> orParse(size_t x);
    pair<Token*, size_t> andParse(size_t x);
    pair<Token*, size_t> addSubtractParse(size_t x);
    pair<Token*, size_t> multiplyDivideParse(size_t x);
    pair<Token*, size_t> unaryParse(size_t x);
    pair<Token*, size_t> variableParse(size_t x);
    pair<Token*, size_t> constParse(size_t x);

    pair<string, size_t> nameParse(size_t x);
    bool nameSymbol(char c);
    bool nameFirstSymbol(char c);
    bool letter(char c);

    vector<Token*> ans;
    string str;
};

#endif // PARSER_H
