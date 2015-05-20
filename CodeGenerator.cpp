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

map<string, size_t>CodeGenerator::types;

CodeGenerator::CodeGenerator() {
    /*gotError = 0;
    error.clear();
    code.clear();
    depth = 0;
    vars.clear();
    globals.clear();*/
    gotError = 0;
    if (CodeGenerator::types.size() == 0) {
        CodeGenerator::types.insert(make_pair("int", 4));
        CodeGenerator::types.insert(make_pair("char", 1));
        CodeGenerator::types.insert(make_pair("long", 8));
        CodeGenerator::types.insert(make_pair("int", 4));
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
        gotError = 1;
        error = "Unknown token\n";
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
        } else if (i->second == 10) {
            res = "rest";
        } else {
            err("Bad type size: " + sizeToString(i->second));//////////////////////////////////////////////////////
        }
        append(i->first + ": " + res + " 1");
    }
}

void CodeGenerator::handleAddress(AddressToken* token) {

}

void CodeGenerator::handleAdd(AddToken* token) {

}

void CodeGenerator::handleAnd(AndToken* token) {

}

void CodeGenerator::handleAssignment(AssignmentToken* token) {

}

void CodeGenerator::handleBlock(BlockToken* token) {
    size_t vars_depth = vars.size();
    vars.push_back(map<string, long long>());
    for (size_t i = 0; i < token->_commands.size(); i++) {
        handleToken(token->_commands[i]);
    }
    vars.resize(vars_depth);
}

void CodeGenerator::handleConstInt(ConstIntToken* token) {

}

void CodeGenerator::handleDereference(DereferenceToken* token) {

}

void CodeGenerator::handleDivide(DivideToken* token) {

}

void CodeGenerator::handleEquality(EqualityToken* token) {

}

//void CodeGenerator::handleFor(ForToken* token);

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
    vars.push_back(map<string, long long>());
    for (size_t i = 0; i < token->_args.size(); i++) {
        if (vars[0].count(token->_args[i]._name) > 0) {
            err("function's argument is already used: " + token->_type);
        }
        vars[0].insert(make_pair(token->_args[i]._name, offset));
        offset += types[token->_args[i]._type];
    }
    offset = 0;
    handleBlock((BlockToken*)token->_body);//////////////////////////////////////////////////////////////////////////////
    append("mov rsp, rbp");
    append("ret");
    vars.clear();
}

//void CodeGenerator::handleIf(IfToken* token);

void CodeGenerator::handleInitialization(InitializationToken* token) {///////////////////////////////////////////////////
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
        vars.back().insert(make_pair(token->_name, offset));
    }
}

void CodeGenerator::handleMultiply(MultiplyToken* token) {

}

void CodeGenerator::handleOr(OrToken* token) {

}

void CodeGenerator::handleReturn(ReturnToken* token) {

}

void CodeGenerator::handleSubtract(SubtractToken* token) {

}

void CodeGenerator::handleUnaryMinus(UnaryMinusToken* token) {

}

void CodeGenerator::handleUnaryPlus(UnaryPlusToken* token) {

}

void CodeGenerator::handleVariable(VariableToken* token) {

}




