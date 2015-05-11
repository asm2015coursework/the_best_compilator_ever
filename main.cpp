#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include "Preprocessor.h"
#include "Parser.h"
#include "CodeGenerator.h"

int main(int argc, char *argv[]) {
    if (!(argc == 2 || (argc == 4 && strcmp(argv[2], "-o") == 0))) {
        printf("Usage: ./the_best_compilator_ever <file to compile> -o <name of asm file>\n");
        return 1;
    }
    std::string output_file = "a.out";
    if (argc == 4) {
        output_file = argv[3];
    }

    std::string code = Preprocessor::preprocess(argv[0]);
    std::vector<std::string> parsed_code = Parser::parse(code);
    std::string asm_code = CodeGenerator::generate(parsed_code);

    printf("Compiled to %s \n", output_file.data());
    freopen(output_file.data(), "w", stdout);
    std::cout << asm_code;

    return 0;
}
