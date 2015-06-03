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

        log << "======TESTING::" + name + "\n";
         string output = "";//CodeGenerator::generate(tokens);

         for (size_t i = 0; i < tokens.size(); i++) {
             output += tokens[i]->toString() + ";\n";
         }
         output += '\n';

         try{
            (*tokens[0]).toString();

         } catch(std::bad_cast& bc){
            std::cout<<"bad_cast " << name << "\n";
         }

         for (size_t i = 0; i < tokens.size(); i++) {
             output += tokens[i]->getType() + ";\n";
         }
         ;
         output += "\n";

         log << output;

         //println(output);

         if (output != "") {
             fileFromString(name + ".asm", output);

             //println(exec("yasm -felf64 -dgwarf2 "+ name + ".asm -o  "+ name + ".o"));
             //println(exec("gcc "+ name + ".o -o " + name));
         } else {
             std::cout << "\n------output == "", " + name + "\n";
         }
    }  catch (ParsingException& ignored){
        std::cout << "\n------Exception " + name + "\n";
        return 1;
    }

    return 0;
}

int Tester::run_tests(int* a, int test_num){
    int failed = 0;
    remove ("../the_best_compilator_ever/tester/log.txt");
    for (int i = 0; i < test_num; ++i){
        failed += Tester::test("../the_best_compilator_ever/tests/test" + std::to_string(a[i]));
    }
    return failed;
}

int Tester::run_once(string name){
    remove ("../the_best_compilator_ever/tester/log.txt");
    return Tester::test("../the_best_compilator_ever/tests/" + name);
}

int Tester::run_all(){
    int failed = 0;
    remove ("../the_best_compilator_ever/tester/log.txt");

    for (int i = 0;i < 3 ; ++i){
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
