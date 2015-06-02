#ifndef PARSER_H
#define PARSER_H

#include <set>
#include <tokens/Token.h>
#include "ParsingException.h"
#include "../tokens/InitializationToken.h"
#include "../tokens/FunctionToken.h"
#include "../tokens/EqualityToken.h"
#include "../tokens/NotEqualityToken.h"
#include "../tokens/NotToken.h"
#include "../tokens/VariableToken.h"
#include "../tokens/BlockToken.h"
#include "../tokens/IfToken.h"
#include "../tokens/ForToken.h"
#include "../tokens/ConstIntToken.h"
#include "../tokens/ConstCharToken.h"
#include "../tokens/AddToken.h"
#include "../tokens/ModToken.h"
#include "../tokens/SubtractToken.h"
#include "../tokens/MultiplyToken.h"
#include "../tokens/DivideToken.h"
#include "../tokens/AssignmentToken.h"
#include "../tokens/OrToken.h"
#include "../tokens/XorToken.h"
#include "../tokens/AndToken.h"
#include "../tokens/DereferenceToken.h"
#include "../tokens/AddressToken.h"
#include "../tokens/UnaryMinusToken.h"
#include "../tokens/UnaryPlusToken.h"
#include "../tokens/ReturnToken.h"
#include "../tokens/AsmToken.h"
#include "../tokens/FunctionCallToken.h"
#include "../tokens/ArrayCallToken.h"
#include "../tokens/StringToken.h"
#include "../tokens/GreaterToken.h"
#include "../tokens/LowerToken.h"
#include "../tokens/BreakToken.h"
#include "../tokens/ContinueToken.h"
#include "../tokens/WhileToken.h"
#include "../tokens/StructToken.h"
#include "../tokens/StructFunctionCallToken.h"
#include "../tokens/StructVariableToken.h"
#include "../tokens/StructPtrVariableToken.h"
#include "../tokens/StructPtrFunctionCallToken.h"

using std::pair;
using std::set;

class Parser {
public:
    Parser();
    vector<Token*> parse(string code);
private:    
    pair<BlockToken*, size_t> blockParse(size_t x);
    pair<InitializationToken*, size_t> initializationParse(size_t x);
    pair<FunctionToken*, size_t> functionParse(size_t x);
    pair<Token*, size_t> commandParse(size_t x);
    pair<Token*, size_t> expressionParse(size_t x);
    pair<Token*, size_t> orParse(size_t x);
    pair<Token*, size_t> andParse(size_t x);
    pair<Token*, size_t> greaterLowerParse(size_t x);
    pair<Token*, size_t> xorParse(size_t x);
    pair<Token*, size_t> equalityParse(size_t x);
    pair<Token*, size_t> addSubtractParse(size_t x);
    pair<Token*, size_t> multiplyDivideParse(size_t x);
    pair<Token*, size_t> unaryParse(size_t x);
    pair<Token*, size_t> variableParse(size_t x);
    pair<Token*, size_t> constIntParse(size_t x);
    pair<Token*, size_t> constCharParse(size_t x);
    pair<Token*, size_t> constStringParse(size_t x);
    pair<Token*, size_t> structVariableOrFunctionParse(size_t x);
    pair<Token*, size_t> constOrVariableOrFunctionParse(size_t x);

    pair<string, size_t> nameParse(size_t x);
    bool nameSymbol(char c);
    bool nameFirstSymbol(char c);
    bool letter(char c);

    vector<Token*> ans;
    set<string> types;
    string str;
};

#endif // PARSER_H
