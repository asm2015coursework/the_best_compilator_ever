#include "Tester.h"

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>

#include "../tokens/Token.h"
#include "../Preprocessor.h"
#include "../parser/Parser.h"
#include "../CodeGenerator.h"
#include "../lib/Utils.h"

#include <iostream>
#include <fstream>
#include <typeinfo>

int Tester::test(string name) {
    try {
        Parser parser;
        Preprocessor preproc;

        vector<Token*> tokens = parser.parse(preproc.preprocess(name + ".cmm"));

        std::ofstream log;
        log.open ("../the_best_compilator_ever/tester/log.txt",  std::ios_base::app);

        log << "======TESTING::" + name + "\n\n---TOKENS:";


         string output = CodeGenerator::generate(tokens);

         log << output;
         log << "\n";

         if (output != "") {
             fileFromString(name + ".asm", output);

             log << "-----EXECUTION\n";
             log << (exec("yasm -felf64 -dgwarf2 "+ name + ".asm -o  "+ name + ".o"));
             log << (exec("gcc "+ name + ".o -o " + name));
             log << "\n";

         } else {
             std::cout << "\n------output == "", " + name + "\n";
             return 1;
         }
    }  catch (ParsingException& ignored){
        std::cout << "\n------Exception " + std::string(ignored.what()) + "\n";
        return 1;
    }

    return 0;
}

void Tester::remove_log(){
    remove ("../the_best_compilator_ever/tester/log.txt");
}

int Tester::run_tests(int* a, int test_num){
    int failed = 0;
    Tester::remove_log();
    for (int i = 0; i < test_num; ++i){
        failed += Tester::test("../the_best_compilator_ever/tests/test" + std::to_string(a[i]));
    }
    return failed;
}

int Tester::run_once(string name){
    Tester::remove_log();
    return Tester::test("../the_best_compilator_ever/tests/" + name);
}

int Tester::run_all(){
    int failed = 0;
    Tester::remove_log();
    for (int i = 0; i < 4 ; ++i){
        string name = "../the_best_compilator_ever/tests/test" + std::to_string(i);
        if (FILE *file = fopen((name+".cmm").c_str(), "r")) {
            fclose(file);
            failed += Tester::test(name);
        } else{
            break;
        }
    }

    return failed;
}
