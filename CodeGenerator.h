#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <vector>
#include <map>

#include "parser/Parser.h"
#include "Type.h"

using std::string;
using std::vector;
using std::map;
//to do:
//в присваивании сделать &
class CodeGenerator {
    bool gotError;
    string error;
    string code;
    size_t if_count;
    size_t cycle_count;
    vector<size_t> cycles;
    map<string, Type> globals;
    vector<map<string, pair<long long, Type> > > vars;//<name, <offset from rsb, type> >
    map<string, string> strings;//<string, name in .data section>
    long long offset;
    map<string, Type> functions;

    map<string, Struct> structs;

    CodeGenerator();
    void append(const string&);
    void makeGlobalVariables();
    void makeStrings();
    void handleCode(const vector<Token*>&);
    void handleToken(Token*);
    Type handleTypeToken(Token*);

    Type handleAddress(AddressToken*);
    Type handleAdd(AddToken*);//result in RAX
    Type handleAnd(AndToken*);//result in RAX
    Type handleArrayCall(ArrayCallToken*);
    void handleAsm(AsmToken*);
    Type handleAssignment(AssignmentToken*);
    void handleBlock(BlockToken*);
    void handleBreak(BreakToken*);
    //Type handleConstChar(ConstCharToken*);
    Type handleConstInt(ConstIntToken*);
    void handleContinue(ContinueToken*);
    Type handleDereference(DereferenceToken*);
    Type handleDivide(DivideToken*);//result in RAX
    Type handleEquality(EqualityToken*);//result in RAX
    void handleFor(ForToken*);
    Type handleFunctionCall(FunctionCallToken*);
    void handleFunction(FunctionToken*);
    Type handleGreaterEquality(GreaterEqualityToken*);
    Type handleGreater(GreaterToken*);
    void handleIf(IfToken*);
    void handleInitialization(InitializationToken*);
    Type handleLowerEquality(LowerEqualityToken*);
    Type handleLower(LowerToken*);
    Type handleMod(ModToken*);
    Type handleMultiply(MultiplyToken*);
    Type handleNotEquality(NotEqualityToken*);
    Type handleNot(NotToken*);
    Type handleOr(OrToken*);//result in RAX
    void handleReturn(ReturnToken*);
    Type handleString(StringToken*);
    Type handleStructFunctionCall(StructFunctionCallToken*);
    Type handleStructPtrFunctionCall(StructPtrFunctionCallToken*);
    Type handleStructPtrVariable(StructPtrVariableToken*);
    void handleStruct(StructToken*);
    Type handleStructVariable(StructVariableToken*);
    Type handleSubtract(SubtractToken*);
    Type handleUnaryMinus(UnaryMinusToken*);//result in RAX
    Type handleUnaryPlus(UnaryPlusToken*);//do nothing, just handle next token
    Type handleVariable(VariableToken*);//result in RAX
    void handleWhile(WhileToken*);
    Type handleXor(XorToken*);

public:
    static string generate(const vector<Token*>&);
};

#endif // CODE_GENERATOR_H
