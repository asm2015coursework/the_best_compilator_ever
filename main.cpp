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



int main(int argc, char *argv[]) {  
 /*
    if (!(argc == 2 || (argc == 4 && strcmp(argv[2], "-o") == 0))) {
        printf("Usage: ./the_best_compilator_ever <file to compile> -o <name of asm file>\n");
        return 1;
    }
    std::string output_file = "a.out";
    if (argc == 4) {
        output_file = argv[3];
    }

    std::string code = Preprocessor::preprocess(argv[0]);
    std::vector<Token*> parsed_code = (new Parser)->parse(code); //don't do like that!!!
    std::string asm_code = CodeGenerator::generate(parsed_code);

    printf("Compiled to %s \n", output_file.data());
    freopen(output_file.data(), "w", stdout);
    std::cout << asm_code;
*/
    Parser parser;
    Preprocessor preproc;
    vector<Token*> tokens = parser.parse(preproc.preprocess("../the_best_compilator_ever/tests/test0.cmm"));

    string output = CodeGenerator::generate(tokens);

    /*for (size_t i = 0; i < tokens.size(); i++) {
        output += tokens[i]->toString() + ";\n";
    }
    output += '\n';

    for (size_t i = 0; i < tokens.size(); i++) {
        output += tokens[i]->getType() + ";\n";
    }
    output += '\n';*/
    println(output);

    //FileFromString("output", output);


    return 0;
}
