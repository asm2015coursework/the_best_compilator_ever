#include "Tester.h"

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <wait.h>

#include "../tokens/Token.h"
#include "../Preprocessor.h"
#include "../parser/Parser.h"
#include "../CodeGenerator.h"
#include "../lib/Utils.h"

#include <iostream>
#include <fstream>
#include <typeinfo>

int Tester::test(string name, bool withoutTokens) {
    try {
        Parser parser;
        Preprocessor preproc;

        vector<Token*> tokens = parser.parse(preproc.preprocess(name + ".cmm"));

        std::ofstream log;
        log.open ("../the_best_compilator_ever/tester/log.txt",  std::ios_base::app);

        log << "======TESTING::" + name + "\n\n---TOKENS:";

         string output = CodeGenerator::generate(tokens);

         if (withoutTokens){
            log << "KEY : WithoutTokens\nOutput is ";
            log << (output != "" ? "not " : "") << "empty\n";
         } else {
            log << output << '\n';
         }

         if (output != "") {
             fileFromString(name + ".asm", output);

             log << "-----EXECUTION\n";
             int f = fork();
             if (f == 0){
                log << (exec("yasm -felf64 -dgwarf2 "+ name + ".asm -o  "+ name + ".o")) << "\n";
                return 1;
             } else {
                 int status = 0;
                 wait(&status);
                 int f2 = fork();
                 if (f2 == 0){
                    log << (exec("gcc "+ name + ".o -o " + name)) << "\n";
                    return 1;
                 } else {
                     int status2 = 0;
                     wait(&status2);
                     log << "Execution is finished\n";
                 }
             }
             log << "\n";

         } else {
             std::cout << "\n------Parser output is empty, " + name + "\n";
             return 1;
         }
    }  catch (ParsingException& ignored) {
        std::cout << "\n------Exception " + std::string(ignored.what()) + "\n";
        return 1;
    }

    return 0;
}

void Tester::remove_log(){
    remove ("../the_best_compilator_ever/tester/log.txt");
}

int Tester::run_tests(int* a, bool withoutTokens) {
    int failed = 0;
    Tester::remove_log();
    for (int i = 0; i < sizeof(a); ++i){
        failed += Tester::test("../the_best_compilator_ever/tests/test" + std::to_string(a[i]), withoutTokens);
    }
    return failed;
}

int Tester::run_one(string name, bool withoutTokens) {
    Tester::remove_log();
    return Tester::test("../the_best_compilator_ever/tests/" + name, withoutTokens);
}

int Tester::run_all(bool withoutTokens) {
    int failed = 0;
    Tester::remove_log();
    for (int i = 0; i < 4 ; ++i){
        string name = "../the_best_compilator_ever/tests/test" + std::to_string(i);
        if (FILE *file = fopen((name+".cmm").c_str(), "r")) {
            fclose(file);
            failed += Tester::test(name, withoutTokens);
        } else {
            break;
        }
    }

    return failed;
}
