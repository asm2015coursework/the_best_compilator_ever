#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <vector>
#include <map>

#include "parser/Parser.h"

using std::string;
using std::vector;
using std::map;

class CodeGenerator {
    static map<string, size_t> types;
    bool gotError;
    string error;
    string code;
    int depth;
    map<string, long long> globals;
    vector<map<string, long long> > vars;
    long long offset;

    CodeGenerator();

    void append(const string&);
    void makeGlobalVariables();
    void handleCode(const vector<Token*>&);
    void handleToken(Token*);
    void handleAddress(AddressToken*);
    void handleAdd(AddToken*);
    void handleAnd(AndToken*);
    void handleAssignment(AssignmentToken*);
    void handleBlock(BlockToken*);
    void handleConstInt(ConstIntToken*);
    void handleDereference(DereferenceToken*);
    void handleDivide(DivideToken*);
    void handleEquality(EqualityToken*);
    //void handleFor(ForToken*);
    void handleFunction(FunctionToken*);
    //void handleIf(IfToken*);
    void handleInitialization(InitializationToken*);
    void handleMultiply(MultiplyToken*);
    void handleOr(OrToken*);
    void handleReturn(ReturnToken*);
    void handleSubtract(SubtractToken*);
    void handleUnaryMinus(UnaryMinusToken*);
    void handleUnaryPlus(UnaryPlusToken*);
    void handleVariable(VariableToken*);

public:
    static string generate(const vector<Token*>&);
};

#endif // CODE_GENERATOR_H
