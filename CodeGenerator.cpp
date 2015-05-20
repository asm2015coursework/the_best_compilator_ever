#include "CodeGenerator.h"
#include "lib/Utils.h"

#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <utility>

using std::make_pair;

#define firstcheck(tokenType) if (token->getType() == #tokenType) {\
    println(#tokenType);\
    handle##tokenType ((tokenType##Token *)token);\
}

#define check(tokenType) else if (token->getType() == #tokenType) {\
    println(#tokenType);\
    handle##tokenType ((tokenType##Token *)token);\
}

#define err(text) error = text;\
        gotError = 1;\
        return

#define types CodeGenerator::typeSize

map<string, size_t> types;

CodeGenerator::CodeGenerator() {
    /*gotError = 0;
    error.clear();
    code.clear();
    depth = 0;
    vars.clear();
    globals.clear();*/
    gotError = 0;
    if (types.size() == 0) {
        types.insert(make_pair("int", 4));
        types.insert(make_pair("char", 1));
        types.insert(make_pair("long", 8));
        types.insert(make_pair("int", 4));
    }
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
    append("global main");
    append("section .text");
    for (size_t i = 0; i < tokens.size() && !gotError; i++) {
        handleToken(tokens[i]);
    }
    makeGlobalVariables();

}

void CodeGenerator::handleToken(Token* token) {
    firstcheck(Address)
            check(Add)
            check(And)
            check(Assignment)
            check(Block)
            check(ConstInt)
            check(Dereference)
            check(Divide)
            check(Equality)
            //check(For)
            check(FunctionCall)
            check(Function)
            //check(If)
            check(Initialization)
            check(Multiply)
            check(Or)
            check(Return)
            check(Subtract)
            check(UnaryMinus)
            check(Variable)
    else {
        err("Unknown token type: " + token->getType());
    }
}

void CodeGenerator::makeGlobalVariables() {
    append("section .bss");
    string res;
    for (map<string, long long>::iterator i = globals.begin(); i != globals.end(); i++) {
        if (i->second == 1) {
            res = "resb";
        } else if (i->second == 2) {
            res = "resw";
        } else if (i->second == 4) {
            res = "resd";
        } else if (i->second == 8) {
            res = "resq";
        }/* else if (i->second == 10) {
            res = "rest";
        }*/ else {
            err("Bad type size: " + sizeToString(i->second));/// нужно что-то делать с другими типами
        }
        append(i->first + ": " + res + " 1");
    }
}

void CodeGenerator::handleAddress(AddressToken* token) {

}

void CodeGenerator::handleAdd(AddToken* token) {
    ///нужно сделать проверку типов
    handleToken(token->right);
    append("push rax");
    handleToken(token->left);
    append("pop rdx");
    append("add rax, rdx");
}

void CodeGenerator::handleAnd(AndToken* token) {
    ///нужно сделать проверку типов
    handleToken(token->left);
    append("push rax");
    handleToken(token->right);
    append("pop rdx");
    append("and rax, rdx");
}

void CodeGenerator::handleAssignment(AssignmentToken* token) {
///нужно запилить другие типы (в частности пользовательские структуры)
    handleToken(token->right);
    if (token->left->getType() == "Variable") {
        ///нужно запилить другие типы
        long long var_offset;
        string type;
        string name = ((VariableToken*)(token->left))->_name;
        for (int i = (int)vars.size() - 1; i >= 0; i--) {
            if (vars[i].count(name) == 1) {
                var_offset = vars[i][name].first;
                type = vars[i][name].second;
                if (types[type] == 1) {
                    append("mov byte[rbp " + offsetToString(var_offset) + "], al");
                } else if (types[type] == 2) {
                    append("mov word[rbp " + offsetToString(var_offset) + "], ax");
                } else if (types[type] == 4) {
                    append("mov dword[rbp " + offsetToString(var_offset) + "], eax");
                } else if (types[type] == 8) {
                    append("mov qword[rbp " + offsetToString(var_offset) + "], rax");
                } else {
                    err("Wrong type's size of variable: " + name);
                }
                return;
            }
        }
        if (globals.count(name) == 1) {
            if (types[type] == 1) {
                append("mov byte[" + name + "], al");
            } else if (types[type] == 2) {
                append("mov word[" + name + "], ax");
            } else if (types[type] == 4) {
                append("mov dword[" + name + "], eax");
            } else if (types[type] == 8) {
                append("mov qword[" + name+ "], rax");
            } else {
                err("Wrong type's size of variable: " + name);
            }
            return;
        }
        err("Unknow variable: " + name);
    } else {
        err("Ask Artur to finish CodeGenerator::handleAssignment function");///ну понятно
    }
}

void CodeGenerator::handleBlock(BlockToken* token) {
    size_t vars_depth = vars.size();
    vars.push_back(map<string, pair<long long, string> >());
    for (size_t i = 0; i < token->_commands.size(); i++) {
        handleToken(token->_commands[i]);
    }
    vars.resize(vars_depth);
}

void CodeGenerator::handleConstInt(ConstIntToken* token) {
    /// что-то сделать с типом нужно
    append("mov rax, " + intToString(token->value));
}

void CodeGenerator::handleDereference(DereferenceToken* token) {

}

void CodeGenerator::handleDivide(DivideToken* token) {
    ///нужно сделать проверку типов!!!
    handleToken(token->left);
    append("push rax");
    handleToken(token->right);
    append("pop rbx");
    append("xor rdx, rdx");
    append("idiv rbx");
}

void CodeGenerator::handleEquality(EqualityToken* token) {

}

//void CodeGenerator::handleFor(ForToken* token);

void CodeGenerator::handleFunctionCall(FunctionCallToken *token) {

}

void CodeGenerator::handleFunction(FunctionToken* token) {
    if (vars.size() > 0) {
        err("Can't initializate function here");
    }
    if (types.count(token->_type) == 0) {
        err("wrong function type: " + token->_type);
    }
    for (size_t i = 0; i < token->_args.size(); i++) {
        if (types.count(token->_args[i]._type) == 0) {
            err("wrong function's parameter type: " + token->_args[i]._type);
        }
    }
    offset = 8;
    append(token->_name + ":");
    append("mov rbp, rsp");
    vars.push_back(map<string, pair<long long, string> >());
    for (size_t i = 0; i < token->_args.size(); i++) {
        if (vars[0].count(token->_args[i]._name) > 0) {
            err("function's argument is already used: " + token->_type);
        }
        vars[0].insert(make_pair(token->_args[i]._name, make_pair(offset, token->_args[i]._type)));
        offset += types[token->_args[i]._type];
    }
    offset = 0;
    handleBlock(token->_body);
    if (token->_body->_commands.back()->getType() != "Return") {
        append("mov rsp, rbp");
        append("ret");
    }
    vars.clear();
}

//void CodeGenerator::handleIf(IfToken* token);

void CodeGenerator::handleInitialization(InitializationToken* token) {/// не хватает присвоения
    if (vars.size() == 0) {
        if (globals.count(token->_name) > 0) {
            err("Global variable already exists: " + token->_name);
        }
        globals.insert(make_pair(token->_name, types[token->_type]));
    } else {
        if (vars.back().count(token->_name) > 0) {
            err("Variable already exists: " + token->_name);
        }
        offset += types[token->_type];
        append("add rsp, " + sizeToString(types[token->_type]));
        vars.back().insert(make_pair(token->_name, make_pair(offset, token->_type)));
    }
}

void CodeGenerator::handleMultiply(MultiplyToken* token) {
    ///нужно сделать проверку типов!!!
    handleToken(token->left);
    append("push rax");
    handleToken(token->right);
    append("pop rdx");
    append("imul rdx");
}

void CodeGenerator::handleOr(OrToken* token) {
    ///нужно сделать проверку типов
    handleToken(token->left);
    append("push rax");
    handleToken(token->right);
    append("pop rdx");
    append("or rax, rdx");
}

void CodeGenerator::handleReturn(ReturnToken* token) {
    ///нужно сделать проверку типов
    handleToken(token->expr);
    append("mov rsp, rbp");
    append("ret");
}

void CodeGenerator::handleSubtract(SubtractToken* token) {
    ///нужно сделать проверку типов
    handleToken(token->right);
    append("push rax");
    handleToken(token->left);
    append("pop rdx");
    append("sub rax, rdx");
}

void CodeGenerator::handleUnaryMinus(UnaryMinusToken* token) {
    ///нужно сделать проверку типов
    handleToken(token->expr);
    append("neg rax");
}

void CodeGenerator::handleUnaryPlus(UnaryPlusToken* token) {
    ///ну хз
    handleToken(token->expr);
}

void CodeGenerator::handleVariable(VariableToken* token) {
    ///нужно запилить другие типы
    long long var_offset;
    string type;
    for (int i = (int)vars.size() - 1; i >= 0; i--) {
        if (vars[i].count(token->_name) == 1) {
            var_offset = vars[i][token->_name].first;
            type = vars[i][token->_name].second;
            if (types[type] == 1) {
                append("xor rax, rax");
                append("mov al, byte[rbp " + offsetToString(var_offset) + "]");
            } else if (types[type] == 2) {
                append("xor rax, rax");
                append("mov ax, word[rbp " + offsetToString(var_offset) + "]");
            } else if (types[type] == 4) {
                append("xor rax, rax");
                append("mov eax, dword[rbp " + offsetToString(var_offset) + "]");
            } else if (types[type] == 8) {
                append("mov rax, qword[rbp " + offsetToString(var_offset) + "]");
            } else {
                err("Wrong type's size of variable: " + token->_name);
            }
            return;
        }
    }
    if (globals.count(token->_name) == 1) {
        if (types[type] == 1) {
            append("xor rax, rax");
            append("mov al, byte[" + token->_name + "]");
        } else if (types[type] == 2) {
            append("xor rax, rax");
            append("mov ax, word[" + token->_name + "]");
        } else if (types[type] == 4) {
            append("xor rax, rax");
            append("mov eax, dword[" + token->_name + "]");
        } else if (types[type] == 8) {
            append("mov rax, qword[" + token->_name+ "]");
        } else {
            err("Wrong type's size of variable: " + token->_name);
        }
        return;
    }
    err("Unknow variable: " + token->_name);
}




