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

class CodeGenerator {
    static map<string, size_t> typeSize;
    bool gotError;
    string error;
    string code;
    int depth;
    map<string, long long> globals;
    vector<map<string, pair<long long, string> > > vars;//<name, <offset from rsb, type> >
    map<string, string> strings;//<string, name in .data section>
    long long offset;
    map<string, Type> functions;

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
    //void handleArrayCall(ArrayCAllToken*);
    void handleAsm(AsmToken*);
    Type handleAssignment(AssignmentToken*);
    void handleBlock(BlockToken*);
    //void handleBreak(BreakToken*);
    //void handleConstChar(ConstCharToken*);
    Type handleConstInt(ConstIntToken*);
    //void handleContinue(ContinueToken*);
    Type handleDereference(DereferenceToken*);
    Type handleDivide(DivideToken*);//result in RAX
    Type handleEquality(EqualityToken*);//result in RAX
    //void handleFor(ForToken*);
    Type handleFunctionCall(FunctionCallToken*);
    void handleFunction(FunctionToken*);
    void handleIf(IfToken*);
    void handleInitialization(InitializationToken*);
    //void handleLowerEquality(LowerEqualityToken*);
    //void handleLower(LowerToken*);
    Type handleMod(ModToken*);
    Type handleMultiply(MultiplyToken*);
    //void handleNotEquality(NotEqualityToken*);
    //void handleNot(NotToken*);
    Type handleOr(OrToken*);//result in RAX
    void handleReturn(ReturnToken*);
    Type handleString(StringToken*);
    //void handleStructFunction(StructFunctionToken);
    //void handleStructPtrFunction(StructPtrFunctionToken);
    //void handleStructPtrVariable(StructPtrVariableToken);
    //void handleStruct(StructToken);
    //void handleStructVariable(StructFunctionVarialbe);
    Type handleSubtract(SubtractToken*);
    Type handleUnaryMinus(UnaryMinusToken*);//result in RAX
    Type handleUnaryPlus(UnaryPlusToken*);//do nothing, just handle next token
    Type handleVariable(VariableToken*);//result in RAX
    //void handleWhile(WhileToken);
    Type handleXor(XorToken*);

public:
    static string generate(const vector<Token*>&);
};

#endif // CODE_GENERATOR_H
