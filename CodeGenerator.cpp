#include "CodeGenerator.h"

#include <stdio.h>
#include <typeinfo>
#include <iostream>

#define check(tokenType) if (token->getType() == #tokenType) {\
                            handle##tokenType ((tokenType##Token *)token);\
                         }

#define println(s) std::cout << s << std::endl;


CodeGenerator::CodeGenerator() {
    gotError = 0;
}

string CodeGenerator::generate(const vector<Token*>& tokens) {
    CodeGenerator codeGenerator;
    codeGenerator.handleCode(tokens);
    if (codeGenerator.gotError) {
        printf("%s\n", codeGenerator.error.c_str());
        return "";
    }
    return codeGenerator.code;
}

void CodeGenerator::handleCode(const vector<Token*>& tokens) {
    code += "global main\n"
            "section .text\n";
    for (size_t i = 0; i < tokens.size() && !gotError; i++) {
        handleToken(tokens[i]);
    }
    makeGlobalVariables();

}

void CodeGenerator::handleToken(Token* token) {
    /*if (typeid(token) == typeid(InitializationToken)) {
        handleInitialization((InitializationToken*)token);
    }
    else if (typeid(token) == typeid(FunctionToken)) {
        handleFunction((FunctionToken*)token);
    }
    else if (typeid(token) == typeid(EqualityToken)) {
        handleEquality((EqualityToken*)token);
    }
    else {
        gotError = 1;
        error = "Unknown token\n";
    }*/
    check(Initialization)
    else check(Function)
    else check(Equality)
    else {
        gotError = 1;
        error = "Unknown token\n";
    }
}

void CodeGenerator::makeGlobalVariables() {
    code += "section .bss\n";
    //put your code here ^_^
}

void CodeGenerator::handleInitialization(InitializationToken* token) {
    println("got initialization");
    //put your code here ^_^
}

void CodeGenerator::handleFunction(FunctionToken* token) {
    println("got function");
    //put your code here ^_^
}

void CodeGenerator::handleEquality(EqualityToken* token) {
    println("got equality");
    //put your code here ^_^
}




