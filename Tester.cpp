#include "Tester.h"

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>

#include "tokens/Token.h"
#include "Preprocessor.h"
#include "parser/Parser.h"
#include "CodeGenerator.h"
#include "lib/Utils.h"

#include <iostream>

int Tester::test(string name) {
    Parser parser;
    Preprocessor preproc;

    vector<Token*> tokens = parser.parse(preproc.preprocess("../the_best_compilator_ever/tests/" + name +".cmm"));

    string output = "";//CodeGenerator::generate(tokens);

    for (size_t i = 0; i < tokens.size(); i++) {
        output += tokens[i]->toString() + ";\n";
    }
    output += '\n';

    (*tokens[0]).toString();

    for (size_t i = 0; i < tokens.size(); i++) {
        output += tokens[i]->getType() + ";\n";
    }
    output += '\n';
    println(output);
    if (output != "") {
        fileFromString(name + ".asm", output);
        //println(exec("yasm -felf64 -dgwarf2 "+ name + ".asm -o  "+ name + ".o"));
        //println(exec("gcc "+ name + ".o -o " + name));
    }
    return 0;
}

int Tester::run_tests(int* a, int test_num){
    for (int i = 0; i < test_num; ++i){
        Tester::test("test" + std::to_string(a[i]));
    }
    return 0;
}

int Tester::run_one(int test_id){
    Tester::test("test" + std::to_string(test_id));
    return 0;
}

const int test_num = 3;

int Tester::run_all(){
    for (int i = 0; i < test_num; ++i){
        Tester::test("test" + std::to_string(i));
    }
    return 0;
}
