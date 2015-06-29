#include "CodeGenerator.h"
#include "lib/Utils.h"
#include "Globals.h"
map<std::string, Struct> structs;

#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <utility>

using std::make_pair;

#define firstcheck(tokenType) if (token->getType() == #tokenType) {\
    println(#tokenType  " start");\
    handle##tokenType ((tokenType##Token *)token);\
    println(#tokenType  " end");\
}

#define check(tokenType) else if (token->getType() == #tokenType) {\
    println(#tokenType " start");\
    handle##tokenType ((tokenType##Token *)token);\
    println(#tokenType  " end");\
}

#define type_firstcheck(tokenType) if (token->getType() == #tokenType) {\
    println(#tokenType " start");\
    Type t = handle##tokenType ((tokenType##Token *)token);\
    println(#tokenType  " end");\
    return t;\
}

#define type_check(tokenType) else if (token->getType() == #tokenType) {\
    println(#tokenType " start");\
    Type t = handle##tokenType ((tokenType##Token *)token);\
    println(#tokenType  " end");\
    return t;\
}


#define err(text) error = text;\
        gotError = 1;\
        std::cout << text << std::endl;\
        exit(1);\
        return

#define type_err(text) error = text;\
        gotError = 1;\
        std::cout << text << std::endl;\
        exit(1);\
        return Type()


CodeGenerator::CodeGenerator() {
    gotError = 0;
    if_count = 0;
    cycle_count = 0;
    cpy_count = 0;
    structs.clear();
    functions.insert(make_pair("malloc", Type("char*")));
    functions.insert(make_pair("free", Type("char*")));

}

void CodeGenerator::append(const string& s) {
    code += s + '\n';
}

string CodeGenerator::generate(const vector<Token*>& tokens) {
    CodeGenerator codeGenerator;
    codeGenerator.handleCode(tokens);
    if (codeGenerator.gotError == 1) {
        std::cout << "Error:\n" << codeGenerator.error;
        return "";

    }
    return codeGenerator.code;
}

void CodeGenerator::handleCode(const vector<Token*>& tokens) {
    string mm_path = "../the_best_compilator_ever/memorymanager/";
    string mm_head = fileToString(mm_path + "head.asm");
    string mm_data = fileToString(mm_path + "data.asm");
    string mm_text = fileToString(mm_path + "text.asm");

    append(mm_head);
    append("global main");
    append("section .text");
    append(mm_text);
    for (size_t i = 0; i < tokens.size() && !gotError; i++) {
        handleToken(tokens[i]);
    }
    makeGlobalVariables();
    makeStrings();
    append(mm_data);
}

void CodeGenerator::handleToken(Token* token) {
    if (token == 0) {
        return;
    }
    firstcheck(Address)
            check(Add)
            check(And)
            check(ArrayCall)
            check(Asm)
            check(Assignment)
            check(Block)
            else if (token->getType() == "Break") {\
                println("Break start");\
                handleBreak();\
                println("Break end");\
            }
            //check(ConstChar)
            check(ConstInt)
            else if (token->getType() == "Continue") {\
                println("Continue start");\
                handleContinue();\
                println("Continue end");\
            }
            check(Dereference)
            check(Divide)
            check(Equality)
            check(For)
            check(FunctionCall)
            check(Function)
            check(GreaterEquality)
            check(Greater)
            check(If)
            check(Initialization)
            check(LowerEquality)
            check(Lower)
            //check(Mod)
            check(Multiply)
            check(Or)
            check(Return)
            check(String)
            check(StructFunctionCall)
            check(StructPtrFunctionCall)
            check(StructPtrVariable)
            check(Struct)
            check(StructVariable)
            check(Subtract)
            check(UnaryMinus)
            check(UnaryPlus)
            check(Variable)
            check(While)
            check(Xor)
    else {
        err("Unknown token type: " + token->getType());
    }
}

Type CodeGenerator::handleTypeToken(Token* token) {
    type_firstcheck(Address)
            type_check(Add)
            type_check(And)
            type_check(ArrayCall)
            type_check(Assignment)
            //type_check(ConstChar)
            type_check(ConstInt)
            check(Dereference)
            type_check(Divide)
            type_check(Equality)
            type_check(FunctionCall)
            type_check(GreaterEquality)
            type_check(Greater)
            type_check(LowerEquality)
            type_check(Lower)
            //type_check(Mod)
            type_check(Multiply)
            type_check(NotEquality)
            type_check(Not)
            type_check(Or)
            type_check(String)
            type_check(StructFunctionCall)
            type_check(StructPtrFunctionCall)
            type_check(StructPtrVariable)
            type_check(StructVariable)
            type_check(Subtract)
            type_check(UnaryMinus)
            type_check(UnaryPlus)
            type_check(Variable)
            type_check(Xor)

    type_err("Unknown token type: " + token->getType());
}


void CodeGenerator::makeGlobalVariables() {
    append("section .bss");
    string res;
    for (map<string, Type>::iterator i = globals.begin(); i != globals.end(); i++) {
        //if (i->second)
        if (i->second.size == 1) {
            res = "resb";
        } else if (i->second.size == 2) {
            res = "resw";
        } else if (i->second.size == 4) {
            res = "resd";
        } else if (i->second.size == 8) {
            res = "resq";
        } else {
            err("Bad type size: " + sizeToString(i->second.size));/// нужно что-то делать с другими типами
        }
        append(i->first + ": " + res + " 1");
    }
}

void CodeGenerator::makeStrings() {
    append("section .data");
    for (map<string, string>::iterator i = strings.begin(); i != strings.end(); i++) {
        append(i->second + ": db \'" + i->first + "\', 0");
    }
}

void CodeGenerator::genCpy(size_t size) {
    append("mov rdx, rdi");
    if (size < 100) {
        size_t j;
        for (j = 0; j + 7 < size; j += 8) {
            append("mov rax, qword[rsi]");
            append("mov qword[rdi], rax");
            append("add rsi, 8");
            append("add rdi, 8");
        }
        for (; j < size; j++) {
            append("mov al, byte[rsi]");
            append("mov byte[rdi], al");
            append("inc rsi");
            append("inc rdi");
        }
    }
    else {
        append("mov rcx, " + sizeToString(size));
        append(".$cpy" + sizeToString(cpy_count) + ":");
        cpy_count++;
        append("mov rax, qword[rsi]");
        append("mov qword[rdi], rax");
        append("add rsi, 8");
        append("add rdi, 8");
        append("sub rcx, 8");
        append("cmp rcx, 7");
        append("jg .$cpy" + sizeToString(cpy_count));
        append("mov rcx, " + sizeToString(size));

        append(".$cpy" + sizeToString(cpy_count) + ":");
        cpy_count++;
        append("mov al, byte[rsi]");
        append("mov byte[rdi], al");
        append("inc rsi");
        append("inc rdi");
        append("dec rcx");
        append("cmp rcx, 0");
        append("jg .$cpy" + sizeToString(cpy_count));
    }
    append("mov rax, rdx");
}


Type CodeGenerator::handleAddress(AddressToken* token) {
    if (token->expr->getType() == "Variable") {
        VariableToken* vartoken = (VariableToken*)token->expr;
        for (int i = (int)vars.size() - 1; i >= 0; i--) {
            if (vars[i].count(vartoken->_name) == 1) {
                long long var_offset = vars[i][vartoken->_name].first;
                Type type = vars[i][vartoken->_name].second;
                append("mov rax, rbp");
                append("add rax, " + offsetToString(var_offset));
                return Type(type.toPointer());
            }
        }
        if (globals.count(vartoken->_name) == 1) {
            append("mov rax, " + vartoken->_name);
            return Type(globals[vartoken->_name].toPointer());
        }
        type_err("handleAddress: Unknow variable: " + vartoken->_name);
    }
    else if (token->expr->getType() == "Dereference") {
        DereferenceToken* token = (DereferenceToken*)(token->expr);
        if (token->getType() == "Variable") {
            return handleVariable((VariableToken*)token->expr);
        }
        type_err("handleAddress: Wrong token of Dereference");
    }
    else if (token->expr->getType() == "StructVariable") {
        StructVariableToken* stoken = (StructVariableToken*)(token->expr);
        if (stoken->expr->getType() == "Variable") {
            VariableToken* var = (VariableToken*)(stoken->expr);
            long long var_offset;
            Type type;
            for (int i = (int)vars.size() - 1; i >= 0; i--) {
                if (vars[i].count(var->_name) == 1) {
                    var_offset = vars[i][var->_name].first;
                    type = vars[i][var->_name].second;
                    if (structs.count(type.name) == 0) {
                        type_err("handleAddress: handleStructVariable: unknown struct");
                    }
                    if (structs[type.name].vars.count(stoken->name) == 0) {
                        type_err("handleAddress: handleStructVariable: unknown struct member");
                    }
                    var_offset -= structs[type.name].vars[stoken->name].first;
                    type = structs[type.name].vars[stoken->name].second;
                    append("mov rax, rbp");
                    append("add rax, " + offsetToString(var_offset));
                    return Type(type);
                }
            }
            if (globals.count(var->_name) == 1) {
                Type type = globals[var->_name];
                var_offset = -structs[type.name].vars[stoken->name].first;
                if (structs.count(type.name) == 0) {
                    type_err("handleAddress: handleStructVariable: unknown struct");
                }
                if (structs[type.name].vars.count(stoken->name) == 0) {
                    type_err("handleAddress: handleStructVariable: unknown struct member");
                }
                append("mov rax, " + stoken->name);
                append("add rax, " + offsetToString(var_offset));
                return Type(type);
            }
            type_err("handleAddress: Unknow variable: " + var->_name);
        }
    }
    else if (token->expr->getType() == "StructVariablePtr") {
        StructPtrVariableToken* stoken = (StructPtrVariableToken*)(token->expr);
        Type type = handleTypeToken(token->expr);
        if (type.isPointer() == 0) {
            type_err("handleStructPtrVariable: wrong expr");
        }
        type.dereference();
        if (structs.count(type.name) == 0) {
            type_err("handleStructPtrVariable: unknown struct");
        }
        if (structs[type.name].vars.count(stoken->name) == 0) {
            type_err("handleStructPtrVariable: unknown struct member");
        }
        long long var_offset = -structs[type.name].vars[stoken->name].first;
        type = structs[type.name].vars[stoken->name].second;
        append("add rax, " + offsetToString(var_offset));
        return Type(type);
    }
    type_err("handleAddress: Wrong token");

}

Type CodeGenerator::handleAdd(AddToken* token) {
    Type r = handleTypeToken(token->right);
    append("push rax");
    Type l = handleTypeToken(token->left);
    append("pop rdx");
    append("add rax, rdx");
    Type res;
    if (res.setMax(l, r) == 0) {
        type_err("handleAdd: Wrong types");
    }
    return res;
}

Type CodeGenerator::handleAnd(AndToken* token) {
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("and rax, rdx");
    Type res;
    if (res.setMax(l, r) == 0) {
        type_err("handleAnd: Wrong types");
    }
    return res;
}

Type CodeGenerator::handleArrayCall(ArrayCallToken* token) {
    if (token->name->getType() == "Variable") {
        VariableToken* vtoken = (VariableToken*)(token->name);
        long long var_offset;
        Type type;
        for (int i = (int)vars.size() - 1; i >= 0; i--) {
            if (vars[i].count(vtoken->_name) == 1) {
                var_offset = vars[i][vtoken->_name].first;
                type = vars[i][vtoken->_name].second;
                if (type.length > 0) {
                    type.setLength(0);
                    type.dereference();
                    Type index = handleTypeToken(token->expr);
                    if (!index.isDefault()) {
                        type_err("handleArrayCall: wrong type of index");
                    }
                    append("mov rdx, " + sizeToString(type.size));
                    append("mul rdx");
                    append("add rax, rbp");
                    append("add rax, " + offsetToString(var_offset));
                    append("mov rax, qword[rax]");
                    return Type(type);
                }
                type_err("handleArrayCall: it's not an array" + token->toString());
            }
        }
        if (globals.count(vtoken->_name) == 1) {
            Type type = globals[vtoken->_name];
            if (type.length > 0) {
                type.setLength(0);
                type.dereference();
                Type index = handleTypeToken(token->expr);
                if (!index.isDefault()) {
                    type_err("handleArrayCall: wrong type of index");
                }
                append("mov rdx, " + sizeToString(type.size));
                append("mul rdx");
                append("add rax, qword[" + vtoken->_name + "]");
                append("mov rax, qword[rax]");
                return Type(type);
            }
            type_err("handleArrayCall: it's not an array");

        }
        type_err("handleArrayCall: Unknow variable: " + vtoken->_name);
    }
    else if (token->name->getType() == "StructPtrVariable") {
        StructPtrVariableToken* stoken = (StructPtrVariableToken*)(token->name);
        Type index = handleTypeToken(token->expr);
        append("push rax");
        Type type = handleTypeToken(stoken->expr);
        if (type.isPointer() == 0) {
            type_err("handleArrayCall: handleStructPtrVariable: wrong expr");
        }
        type.dereference();
        if (structs.count(type.name) == 0) {
            type_err("handleArrayCall: handleStructPtrVariable: unknown struct: " + type.name + " " + token->toString());
        }
        if (structs[type.name].vars.count(stoken->name) == 0) {
            type_err("handleArrayCall: handleStructPtrVariable: unknown struct member");
        }
        long long var_offset = -structs[type.name].vars[stoken->name].first;
        type = structs[type.name].vars[stoken->name].second;
        append("mov rdx, rax");
        append("add rdx, " + offsetToString(var_offset));
        append("pop rax");
        append("add rdx, rax");
        if (!type.isDefault()) {
            append("mov rax, rdx");
        } else if (type.size == 1) {
            append("xor rax, rax");
            append("mov al, byte[rdx]");
        } else if (type.size == 2) {
            append("xor rax, rax");
            append("mov ax, word[rdx]");
        } else if (type.size == 4) {
            append("xor rax, rax");
            append("mov eax, dword[rdx]");
        } else if (type.size == 8) {
            append("mov rax, qword[rdx]");
        } else {
            type_err("handleArrayCall: handleStructPtrVariable: wrong type");
        }
        return Type(type);
    }
    type_err("handleArrayCall: wrong token " + token->toString());
}

void CodeGenerator::handleAsm(AsmToken* token) {
    append(token->code);
}

Type CodeGenerator::handleAssignment(AssignmentToken* token) {
///нужно запилить другие типы (в частности пользовательские структуры)
    Type res = handleTypeToken(token->right);
    if (token->left->getType() == "Variable") {
        ///нужно запилить другие типы
        long long var_offset;
        Type type;
        string name = ((VariableToken*)(token->left))->_name;
        for (int i = (int)vars.size() - 1; i >= 0; i--) {
            if (vars[i].count(name) == 1) {
                var_offset = vars[i][name].first;
                type = vars[i][name].second;
                if (type.name != res.name && type.setMax(type, res) == 0) {
                    type_err("handleAssigment: wrong types");
                }

                if (!type.isDefault()) {
                    ///cpy [rbp + offsetToString(var_offset)], rax, type.size
                    append("mov rdi, rbp");
                    append("add rdi, " + offsetToString(var_offset));
                    append("mov rsi, rax");
                    genCpy(type.size);//rdi, rsi, size
                } else if (type.size == 1) {
                    append("mov byte[rbp " + offsetToString(var_offset) + "], al");
                } else if (type.size == 2) {
                    append("mov word[rbp " + offsetToString(var_offset) + "], ax");
                } else if (type.size == 4) {
                    append("mov dword[rbp " + offsetToString(var_offset) + "], eax");
                } else if (type.size == 8) {
                    append("mov qword[rbp " + offsetToString(var_offset) + "], rax");
                }
                return res;
            }
        }
        if (globals.count(name) == 1) {
            Type type = globals[name];
            if (type.name != res.name && type.setMax(type, res) == 0) {
                type_err("handleAssigment: wrong types");
            }
            if (!type.isDefault()) {
                append("mov rdi, " + name);
                append("mov rsi, rax");
                genCpy(type.size);//rdi, rsi, size
            } else if (type.size == 1) {
                append("mov byte[" + name + "], al");
            } else if (type.size == 2) {
                append("mov word[" + name + "], ax");
            } else if (type.size == 4) {
                append("mov dword[" + name + "], eax");
            } else if (type.size == 8) {
                append("mov qword[" + name+ "], rax");
            }
            return res;
        }
        type_err("handleAssignment: Unknow variable: " + name);
    }
    else if (token->left->getType() == "ArrayCall") {
        //нужно проверить типы
        ArrayCallToken* atoken = (ArrayCallToken*)(token->left);
        if (atoken->name->getType() == "Variable") {
            VariableToken* vtoken = (VariableToken*)(atoken->name);
            long long var_offset;
            Type atype;
            for (int i = (int)vars.size() - 1; i >= 0; i--) {
                if (vars[i].count(vtoken->_name) == 1) {
                    var_offset = vars[i][vtoken->_name].first;
                    atype = vars[i][vtoken->_name].second;
                    if (atype.length > 0) {
                        atype.setLength(0);
                        atype.dereference();
                        append("push rax");
                        Type index = handleTypeToken(atoken->expr);
                        if (!index.isDefault()) {
                            type_err("handleAssignment: handleArrayCall: wrong type of index");
                        }
                        append("mov rdx, " + sizeToString(atype.size));
                        append("mul rdx");
                        append("add rax, rbp");
                        append("add rax, " + offsetToString(var_offset));
                        append("pop rdx");
                        if (atype.name != atype.name && atype.setMax(atype, res) == 0) {
                            type_err("handleAssignment: handleArrayCall: wrong types");
                        }
                        if (!atype.isDefault()){
                            append("mov rdi, qword[rax]");
                            append("mov rsi, rdx");
                            genCpy(atype.size);
                        } else if (atype.size == 1) {
                            append("mov byte[rax], dl");
                            append("mov rax, rdx");
                        } else if (atype.size == 2) {
                            append("mov word[rax], dx");
                            append("mov rax, rdx");
                        } else if (atype.size == 4) {
                            append("mov dword[rax], edx");
                            append("mov rax, rdx");
                        } else if (atype.size == 8) {
                            append("mov qword[rax], rdx");
                            append("mov rax, rdx");
                        }
                        return Type(atype);
                    }
                    type_err("handleAssignment: handleArrayCall: it's not an array" + token->toString());
                }
            }
            if (globals.count(vtoken->_name) == 1) {
                Type atype = globals[vtoken->_name];
                if (atype.length > 0) {
                    atype.setLength(0);
                    atype.dereference();
                    append("push rax");
                    Type index = handleTypeToken(atoken->expr);
                    if (!index.isDefault()) {
                        type_err("handleAssignment: handleArrayCall: wrong type of index");
                    }
                    append("mov rdx, " + sizeToString(atype.size));
                    append("mul rdx");
                    append("add rax, qword[" + vtoken->_name + "]");
                    append("pop rdx");
                    append("mov qword[rax], rdx");
                    append("mov rax, rdx");
                    return Type(atype);
                }
                type_err("handleAssignment: handleArrayCall: it's not an array");

            }
            type_err("handleAssignment: Unknow variable: " + vtoken->_name);
        }
    }
    else if (token->left->getType() == "Dereference") {
        DereferenceToken* dtoken = (DereferenceToken*)(token->left);
        append("push rax");
        Type type = handleTypeToken(dtoken->expr);
        if (type.isPointer() == 0) {
            type_err("handleAssignment: handleDereference: in is not a pointer");
        }
        type.dereference();
        if (res.name != type.name && type.setMax(type, res) == 0) {
            type_err("handleAssignment: handleDereference: wrong types");
        }
        append("pop rsi");
        if (!type.isDefault()) {
            append("mov rdi, rax");
            genCpy(type.size);
        } else if (type.size == 1) {
            append("mov rdx, rsi");
            append("byte[rax], dl");
            append("mov rax, rdx");
        } else if (type.size == 2) {
            append("mov rdx, rsi");
            append("worg[rax], dx");
            append("mov rax, rdx");
        } else if (type.size == 4) {
            append("mov rdx, rsi");
            append("dword[rax], edx");
            append("mov rax, rdx");
        } else if (type.size == 8) {
            append("qword[rax], rsi");
            append("mov rax, rsi");
        }
        return type;
    }
    else if (token->left->getType() == "StructPtrVariable") {
        StructPtrVariableToken* stoken = (StructPtrVariableToken*)(token->left);
        append("push rax");
        Type type = handleTypeToken(stoken->expr);
        if (type.isPointer() == 0) {
            type_err("handleAssignment: handleStructPtrVariable: wrong expr");
        }
        type.dereference();
        if (structs.count(type.name) == 0) {
            type_err("handleAssignment: handleStructPtrVariable: unknown struct");
        }
        if (structs[type.name].vars.count(stoken->name) == 0) {
            type_err("handleAssignment: handleStructPtrVariable: unknown struct member");
        }
        long long var_offset = -structs[type.name].vars[stoken->name].first;
        type = structs[type.name].vars[stoken->name].second;
        if (res.name != res.name && type.setMax(type, res) == 0) {
            type_err("handleAssignment: handleStructPtrVariable: wrong types");
        }
        append("mov rdi, rax");
        append("add rdi, " + offsetToString(var_offset));//rdi is an address
        append("pop rsi");
        if (!type.isDefault()) {
            append("mov rdi, qword[rdi]");
            genCpy(type.size);
        } else if (type.size == 1) {
            append("xor rax, rax");
            append("mov rdx, rsi");
            append("mov al, dl");
            append("mov byte[rdi], al");
        } else if (type.size == 2) {
            append("xor rax, rax");
            append("mov rdx, rsi");
            append("mov ax, dx");
            append("mov word[rdi], ax");
        } else if (type.size == 4) {
            append("xor rax, rax");
            append("mov rdx, rsi");
            append("mov eax, edx");
            append("mov dword[rdi], eax");
        } else if (type.size == 8) {
            append("mov rax, rsi");
            append("mov qword[rdi], rax");
        }
        return Type(type);
    }
    else if (token->left->getType() == "StructVariable") {
        type_err("ask artur to do a.a = bla");
    }
    type_err("handleAssignment: wrong left token" + token->left->getType() + " " + token->left->toString());
}

void CodeGenerator::handleBlock(BlockToken* token) {
    size_t vars_depth = vars.size();
    vars.push_back(map<string, pair<long long, Type> >());
    for (size_t i = 0; i < token->_commands.size(); i++) {
        handleToken(token->_commands[i]);
    }
    vars.resize(vars_depth);
}

void CodeGenerator::handleBreak() {
    if (cycles.size() == 0) {
        err("handleBreak: can't find any cycle");
    }
    append("jmp ._cycle_end" + sizeToString(cycles.back()));
}

Type CodeGenerator::handleConstInt(ConstIntToken* token) {
    /// что-то сделать с типом нужно
    append("mov rax, " + intToString(token->value));
    return Type("int");
}

void CodeGenerator::handleContinue() {
    if (cycles.size() == 0) {
        err("handleContinue: can't find any cycle");
    }
    append("jmp ._cycle_start" + sizeToString(cycles.back()));
}

Type CodeGenerator::handleDereference(DereferenceToken* token) {
    Type l = handleTypeToken(token);
    if (l.isPointer() == 0) {
        type_err("handleDereference: there is no pointer");
    }
    if (l.size == 1) {
        append("xor rax, rax");
        append("mov al, byte[rax]");
    }
    else if (l.size == 2) {
        append("xor rax, rax");
        append("mov ax, word[rax]");
    }
    else if (l.size == 4) {
        append("xor rax, rax");
        append("mov eax, dword[rax]");
    }
    else if (l.size == 8) {
        append("mov rax, qword[rax]");
    }
    else {

    }
    l.dereference();
    return l;
}

Type CodeGenerator::handleDivide(DivideToken* token) {
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rbx");
    append("xor rdx, rdx");
    append("idiv rbx");
    Type res;
    if (res.setMax(l, r) == 0) {
        type_err("handleDivide: Wrong types");
    }
    return res;
}

Type CodeGenerator::handleEquality(EqualityToken* token) {
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("mov rbx, rax");
    append("xor rax, rax");
    append("cmp rdx, rbx");
    append("sete al");
    if (l.setMax(l, r) == 0) {
        type_err("handleEquality: Wrong types");
    }
    return Type("int");
}

void CodeGenerator::handleFor(ForToken* token) {
   string postfix = sizeToString(cycle_count);
   handleToken(token->expr1);
   append("._cycle_start_next" + postfix + ":");
   Type type = handleTypeToken(token->expr2);
   if (!type.isDefault()) {
       err("handleFor: wrong expr");
   }
   append("cmp rax, 0");
   append("je ._cycle_end" + postfix);
   cycles.push_back(cycle_count);
   cycle_count++;
   handleToken(token->cmd);
   cycles.pop_back();
   append("._cycle_start" + postfix + ":");//just for continue
   handleToken(token->expr3);
   append("jmp ._cycle_start_next" + postfix);
   append("._cycle_end" + postfix + ":");
}

Type CodeGenerator::handleFunctionCall(FunctionCallToken *token) {
    Type t;
    size_t total_size = 0;
    for (int i = (int)token->args.size() - 1; i >= 0; i--) {
        t = handleTypeToken(token->args[i]);
        std::cout << "--" << t.name << "--" << std::endl;
        if (t.size == 1) {
            append("sub rsp, 1");
            append("mov byte[rsp], al");
            total_size += 1;
        } else if (t.size == 2) {
            append("sub rsp, 2");
            append("mov word[rsp], ax");
            total_size += 2;
        } else if (t.size == 4) {
            append("sub rsp, 4");
            append("mov dword[rsp], eax");
            total_size += 4;
        } else if (t.size == 8) {
            append("sub rsp, 8");
            append("mov qword[rsp], rax");
            total_size += 8;
        } else {
            type_err("handleFunctionCall: wrong type");
        }
    }
    append("call " + token->name);
    append("add rsp, " + sizeToString(total_size));
    if (functions.count(token->name) == 0) {
        type_err("handleFunctionCall: Unknown function " + token->name + " " + token->toString());
    }
    return functions[token->name];
}

void CodeGenerator::handleFunction(FunctionToken* token) {
    if (vars.size() > 0) {
        err("Can't initializate function here");
    }
    functions.insert(make_pair(token->_name, Type(token->_type)));
    offset = 16;
    append(token->_name + ":");
    append("push rbp");
    append("mov rbp, rsp");
    vars.push_back(map<string, pair<long long, Type> >());
    for (size_t i = 0; i < token->_args.size(); i++) {
        if (vars[0].count(token->_args[i]._name) > 0) {
            err("handleFunction: function's argument is already used: " + token->_type);
        }
        vars[0].insert(make_pair(token->_args[i]._name, make_pair(-offset, token->_args[i]._type)));
        offset += Type(token->_args[i]._type).size;
    }
    offset = 0;
    handleBlock(token->_body);
    if (token->_body->_commands.back()->getType() != "Return") {
        append("mov rsp, rbp");
        append("pop rbp");
        append("ret");
    }
    vars.clear();
}

Type CodeGenerator::handleGreaterEquality(GreaterEqualityToken* token) {
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("mov rbx, rax");
    append("xor rax, rax");
    append("cmp rdx, rbx");
    append("setnle al");
    if (l.setMax(l, r) == 0) {
        type_err("handleGreaterEquality: Wrong types");
    }
    return Type("int");
}

Type CodeGenerator::handleGreater(GreaterToken* token) {
    ///нужно сделать нормальную проверку типов
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("mov rbx, rax");
    append("xor rax, rax");
    append("cmp rdx, rbx");
    append("setnl al");
    return Type("int");
}


void CodeGenerator::handleIf(IfToken* token) {
    Type type = handleTypeToken(token->expr);
    if (!type.isDefault()) {
        err("handleIfToken: wrong expression");
    }
    string postfix = sizeToString(if_count);
    if_count++;
    append("cmp rax, 0");
    append("je ._else" + postfix);
    if (token->block1 != 0) {
        handleToken(token->block1);
    }
    append("jmp ._end" + postfix);
    append("._else" + postfix + ":");
    if (token->block2 != 0) {
        handleToken(token->block2);
    }
    append("._end" + postfix + ":");

}

void CodeGenerator::handleInitialization(InitializationToken* token) {/// не хватает присвоения
    if (vars.size() == 0) {//global
        if (globals.count(token->_name) > 0) {
            err("handleInitialization: Global variable already exists: " + token->_name);
        }
        if (token->_expr != 0) {
            err("handleInitialization: Can't initializate global variable");
        }
        if (token->_size == 0) {
            globals.insert(make_pair(token->_name, Type(token->_type)));
        }
        else if (token->_size->getType() == "ConstInt" && ((ConstIntToken*)(token->_size))->value > 0){
            globals.insert(make_pair(token->_name, Type(token->_type).toPointer().setLength(((ConstIntToken*)(token->_size))->value)));
        }
        else {
            err("handleInitialization: wrong size of array:" + token->_name);
        }
    }
    else {//not global
        if (vars.back().count(token->_name) > 0) {
            err("handleInitialization: Variable already exists: " + token->_name);
        }
        if (token->_size == 0) {
            offset += Type(token->_type).size;
            vars.back().insert(make_pair(token->_name, make_pair(offset, Type(token->_type))));
            append("sub rsp, " + sizeToString(Type(token->_type).size));
            if (token->_expr != 0) {
                Type r = handleTypeToken(token->_expr);
                Type l(token->_type);
                Type res = l;
                if (l.name != r.name && res.setMax(l, r) == 0) {
                    err("handleInitialization: wrong types: " + l.name + ", " + r.name);
                }
                if (!res.isDefault()) {
                    append("mov rdi, rsp");
                    append("mov rsi, rax");
                    genCpy(res.size);
                } else if (res.size == 1) {
                    append("mov byte[rsp], al");
                } else if (res.size == 2) {
                    append("mov word[rsp], ax");
                } else if (res.size == 4) {
                    append("mov dword[rsp], eax");
                } else if (res.size == 8) {
                    append("mov qword[rsp], rax");
                } else {
                    err("handleInitialization: Wrong type's size of variable: " + token->_name);
                }
            }
        }
        else {//array
            if (token->_expr != 0) {
                err("handleInitialization: can't init array");
            }
            if (token->_size->getType() == "ConstInt" && ((ConstIntToken*)(token->_size))->value > 0){
                size_t cursize = Type(token->_type).size * ((ConstIntToken*)(token->_size))->value;
                offset += cursize;
                append("sub rsp, " + sizeToString(cursize));

                vars.back().insert(make_pair(token->_name, make_pair(offset, Type(token->_type).toPointer().setLength(((ConstIntToken*)(token->_size))->value))));
            }
            else {
                err("handleInitialization: wrong size of array:" + token->_name);
            }
        }
    }
}

Type CodeGenerator::handleLowerEquality(LowerEqualityToken* token) {
    ///нужно сделать нормальную проверку типов
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("mov rbx, rax");
    append("xor rax, rax");
    append("cmp rdx, rbx");
    append("setle al");
    if (l.setMax(l, r) == 0) {
        type_err("handleLowerEquality: Wrong types");
    }
    return Type("int");
}

Type CodeGenerator::handleLower(LowerToken* token) {
    ///нужно сделать нормальную проверку типов
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("mov rbx, rax");
    append("xor rax, rax");
    append("cmp rdx, rbx");
    append("setl al");
    if (l.setMax(l, r) == 0) {
        type_err("handleLower: Wrong types");
    }
    return Type("int");
}
Type CodeGenerator::handleMod(ModToken* token) {

}

Type CodeGenerator::handleMultiply(MultiplyToken* token) {
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("imul rdx");
    Type res;
    if (res.setMax(l, r) == 0) {
        type_err("handleMultiply: Wrong types");
    }
    return res;
}

Type CodeGenerator::handleNotEquality(NotEqualityToken* token) {
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("mov rbx, rax");
    append("xor rax, rax");
    append("cmp rdx, rbx");
    append("setne al");
    if (l.setMax(l, r) == 0) {
        type_err("handleNotEquality: Wrong types");
    }
    return Type("int");
}

Type CodeGenerator::handleNot(NotToken* token) {
    Type l = handleTypeToken(token->expr);
    if (!l.isDefault()) {
        type_err("handleNot: wrong type");
    }
    append("xor rax, 0");
    return Type("int");
}

Type CodeGenerator::handleOr(OrToken* token) {
    ///нужно сделать нормальную проверку типов
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("or rax, rdx");
    Type res;
    if (res.setMax(l, r) == 0) {
        type_err("handleOr: Wrong types");
    }
    return res;
}

void CodeGenerator::handleReturn(ReturnToken* token) {
    ///нужно сделать проверку типов
    if (token->expr != 0) {
        handleToken(token->expr);
    }
    append("mov rsp, rbp");
    append("pop rbp");
    append("ret");
}

Type CodeGenerator::handleString(StringToken* token) {
    if (strings.count(token->str) == 0) {
        strings.insert(make_pair(token->str, "$str" + sizeToString(strings.size())));
    }
    append("mov rax, " + strings[token->str]);
    return Type("char*");
}


Type CodeGenerator::handleStructFunctionCall(StructFunctionCallToken* token) {

}

Type CodeGenerator::handleStructPtrFunctionCall(StructPtrFunctionCallToken* token) {
    Type type;
    size_t total_size = 0;
    for (long long i = (long long)token->args.size() - 1; i >= 0; i--) {
        type = handleTypeToken(token->args[i]);
        if (type.size == 1) {
            append("sub rsp, 1");
            append("mov byte[rsp], al");
            total_size += 1;
        } else if (type.size == 2) {
            append("sub rsp, 2");
            append("mov word[rsp], ax");
            total_size += 2;
        } else if (type.size == 4) {
            append("sub rsp, 4");
            append("mov dword[rsp], eax");
            total_size += 4;
        } else if (type.size == 8) {
            append("sub rsp, 8");
            append("mov qword[rsp], rax");
            total_size += 8;
        } else {
            type_err("handleStructPtrFunctionCall: wrong type");
        }
    }

    type = handleTypeToken(token->expr);
    if (type.isPointer() == 0) {
        type_err("handleStructPtrFunctionCall: wrong expr");
    }
    type.dereference();
    if (structs.count(type.name) == 0) {
        type_err("handleStructPtrFunctionCall: unknown struct");
    }
    if (structs[type.name].functions.count(token->name) == 0) {
        type_err("handleStructPtrFunctionCall: unknown struct method: " + token->name);
    }

    append("sub rsp, 8");
    append("mov qword[rsp], rax");
    total_size += 8;
    append("call " + type.name + "." + token->name);
    append("add rsp, " + sizeToString(total_size));
    return structs[type.name].functions[token->name];
}

Type CodeGenerator::handleStructPtrVariable(StructPtrVariableToken* token) {
    Type type = handleTypeToken(token->expr);
    if (type.isPointer() == 0) {
        type_err("handleStructPtrVariable: wrong expr");
    }
    type.dereference();
    if (structs.count(type.name) == 0) {
        type_err("handleStructPtrVariable: unknown struct");
    }
    if (structs[type.name].vars.count(token->name) == 0) {
        type_err("handleStructPtrVariable: unknown struct member");
    }
    long long var_offset = -structs[type.name].vars[token->name].first;
    type = structs[type.name].vars[token->name].second;
    append("mov rdx, rax");
    append("add rdx, " + offsetToString(var_offset));
    if (!type.isDefault()) {
        append("mov rax, rdx");
    } else if (type.size == 1) {
        append("xor rax, rax");
        append("mov al, byte[rdx]");
    } else if (type.size == 2) {
        append("xor rax, rax");
        append("mov ax, word[rdx]");
    } else if (type.size == 4) {
        append("xor rax, rax");
        append("mov eax, dword[rdx]");
    } else if (type.size == 8) {
        append("mov rax, qword[rdx]");
    } else {
        type_err("handleStructPtrVariable: wrong type");
    }
    return Type(type);
}

void CodeGenerator::handleStruct(StructToken* token) {
    if (structs.count(token->name) > 0) {
        err("handleStruct: struct aleady exists" + token->name);
    }
    structs.insert(make_pair(token->name, Struct()));
    Struct& cur_struct = structs[token->name];
    InitializationToken* var;
    size_t struct_offset = 0;
    Type type;
    size_t array_size;
    for (size_t i = 0; i < token->variables.size(); i++) {
        var = token->variables[i];
        if (var->_expr != 0) {
            err("handleStruct: wrong struct member: " + var->_name);
        }
        if (cur_struct.vars.count(var->_name) > 0) {
            err("handleStruct: member already exists");
        }
        if (var->_size == 0) {
            type = Type(var->_type);
            cur_struct.vars.insert(make_pair(var->_name, make_pair(struct_offset, type)));
            struct_offset += type.size;
        }
        else if (var->_size->getType() == "ConstInt") {
            type = Type(var->_type);
            array_size = ((ConstIntToken*)(var->_size))->value;
            type.setLength(array_size);
            cur_struct.vars.insert(make_pair(var->_name, make_pair(struct_offset, type.toPointer())));
            struct_offset += array_size * type.size;
        }
        else {
            err("handleStruct: wrong array size");
        }
    }
    cur_struct.size = struct_offset;

    FunctionToken* function;
    vector<Variable> args;

    for (size_t i = 0; i < token->functions.size(); i++) {
        args.push_back(Variable(token->name + "*", "this"));
        for (size_t j = 0; j < token->functions[i]->_args.size(); j++) {
            args.push_back(token->functions[i]->_args[j]);
        }
        function = new FunctionToken(token->functions[i]->_type, token->name + "." + token->functions[i]->_name, args, token->functions[i]->_body);
        cur_struct.functions.insert(make_pair(token->functions[i]->_name, Type(token->functions[i]->_type)));
        handleFunction(function);
        ///delete function;
        args.clear();
    }

}


Type CodeGenerator::handleStructVariable(StructVariableToken* token) {
    if (token->expr->getType() == "Variable") {
        VariableToken* var = (VariableToken*)(token->expr);
        long long var_offset;
        Type type;
        for (int i = (int)vars.size() - 1; i >= 0; i--) {
            if (vars[i].count(var->_name) == 1) {
                var_offset = vars[i][var->_name].first;
                type = vars[i][var->_name].second;
                if (structs.count(type.name) == 0) {
                    type_err("handleStructVariable: unknown struct");
                }
                if (structs[type.name].vars.count(token->name) == 0) {
                    type_err("handleStructVariable: unknown struct member");
                }
                var_offset -= structs[type.name].vars[token->name].first;
                type = structs[type.name].vars[token->name].second;
                if (!type.isDefault()) {
                    append("mov rax, rbp");
                    append("add rax, " + offsetToString(var_offset));
                } else if (type.size == 1) {
                    append("xor rax, rax");
                    append("mov al, byte[rbp " + offsetToString(var_offset) + "]");
                } else if (type.size == 2) {
                    append("xor rax, rax");
                    append("mov ax, word[rbp " + offsetToString(var_offset) + "]");
                } else if (type.size == 4) {
                    append("xor rax, rax");
                    append("mov eax, dword[rbp " + offsetToString(var_offset) + "]");
                } else if (type.size == 8) {
                    append("mov rax, qword[rbp " + offsetToString(var_offset) + "]");
                } else {
                    type_err("handleStructVariable: wrong type");
                }
                return Type(type);
            }
        }
        if (globals.count(var->_name) == 1) {
            Type type = globals[var->_name];
            var_offset = -structs[type.name].vars[token->name].first;
            if (structs.count(type.name) == 0) {
                type_err("handleStructVariable: unknown struct");
            }
            if (structs[type.name].vars.count(token->name) == 0) {
                type_err("handleStructVariable: unknown struct member");
            }
            append("mov rdx, " + token->name);
            append("add rdx, " + offsetToString(var_offset));
            if (!type.isDefault()) {
                append("mov rax, rdx");
            } else if (type.size == 1) {
                append("xor rax, rax");
                append("move al, byte[rdx]");
            } else if (type.size == 2) {
                append("xor rax, rax");
                append("mov ax, word[rdx]");
            } else if (type.size == 4) {
                append("xor rax, rax");
                append("mov eax, dword[rdx]");
            } else if (type.size == 8) {
                append("mov rax, qword[rdx]");
            } else {
                type_err("handleStructVariable: Wrong type's size of variable");
            }
            return Type(type);
        }
        type_err("handleStructVariable: Unknow variable: " + var->_name);
    }
    type_err("handleStructVariable: wrong token");
}

Type CodeGenerator::handleSubtract(SubtractToken* token) {
    Type r = handleTypeToken(token->right);
    append("push rax");
    Type l = handleTypeToken(token->left);
    append("pop rdx");
    append("sub rax, rdx");
    Type res;
    if (res.setMax(l, r) == 0) {
        type_err("handleSubstract: Wrong types");
    }
    return res;
}

Type CodeGenerator::handleUnaryMinus(UnaryMinusToken* token) {
    ///нужно сделать проверку типов
    Type res = handleTypeToken(token->expr);
    append("neg rax");
    return res;
}

Type CodeGenerator::handleUnaryPlus(UnaryPlusToken* token) {
    ///ну хз
    Type res = handleTypeToken(token->expr);
    return res;
}

Type CodeGenerator::handleVariable(VariableToken* token) {
    long long var_offset;
    Type type;
    for (int i = (int)vars.size() - 1; i >= 0; i--) {
        if (vars[i].count(token->_name) == 1) {
            var_offset = vars[i][token->_name].first;
            type = vars[i][token->_name].second;
            if (type.length > 0) {
                append("mov rax, rbp");
                append("add rax, " + offsetToString(var_offset));
                type.setLength(0);///now it is just a pointer
            }
            else {
                if (!type.isDefault()) {
                    append("mov rax, rbp");
                    append("add rax, " + offsetToString((var_offset)));
                }
                if (type.size == 1) {
                    append("xor rax, rax");
                    append("mov al, byte[rbp " + offsetToString(var_offset) + "]");
                } else if (type.size == 2) {
                    append("xor rax, rax");
                    append("mov ax, word[rbp " + offsetToString(var_offset) + "]");
                } else if (type.size == 4) {
                    append("xor rax, rax");
                    append("mov eax, dword[rbp " + offsetToString(var_offset) + "]");
                } else if (type.size == 8) {
                    append("mov rax, qword[rbp " + offsetToString(var_offset) + "]");
                } else {
                    type_err("handleVariable: Wrong type's size of variable: " + token->_name);
                }
            }
            return Type(type);
        }
    }
    if (globals.count(token->_name) == 1) {
        Type type = globals[token->_name];
        if (!type.isDefault()) {
            append("mov rax, " + token->_name);
        } else if (type.size == 1) {
            append("xor rax, rax");
            append("mov al, byte[" + token->_name + "]");
        } else if (type.size == 2) {
            append("xor rax, rax");
            append("mov ax, word[" + token->_name + "]");
        } else if (type.size == 4) {
            append("xor rax, rax");
            append("mov eax, dword[" + token->_name + "]");
        } else if (type.size == 8) {
            append("mov rax, qword[" + token->_name+ "]");
        } else {
            type_err("handleVariable: Wrong type's size of variable: " + token->_name);
        }
        return Type(type);
    }
    type_err("handleVariable: Unknown variable: " + token->_name);
}

void CodeGenerator::handleWhile(WhileToken* token) {
    string postfix = sizeToString(cycle_count);
    append("._cycle_start" + postfix + ":");
    Type type = handleTypeToken(token->expr);
    append("cmp rax, 0");
    append("je ._cycle_end" + postfix);
    if (!type.isDefault()) {
        err("handleWhile: wrong type of expr");
    }
    cycles.push_back(cycle_count);
    cycle_count++;
    handleToken(token->cmd);
    cycles.pop_back();
    append("jmp ._cycle_start" + postfix);
    append("._cycle_end" + postfix + ":");

}

Type CodeGenerator::handleXor(XorToken *token) {
    Type l = handleTypeToken(token->left);
    append("push rax");
    Type r = handleTypeToken(token->right);
    append("pop rdx");
    append("xor rax, rdx");
    Type res;
    if (res.setMax(l, r) == 0) {
        type_err("handleXor: Wrong types");
    }
    return res;
}




