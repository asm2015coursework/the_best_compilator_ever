#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "tokens/Token.h"
#include "Preprocessor.h"
#include "parser/Parser.h"
#include "CodeGenerator.h"

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
    std::vector<Token> parsed_code = (new Parser)->parse(code);
    std::string asm_code = CodeGenerator::generate(parsed_code);

    printf("Compiled to %s \n", output_file.data());
    freopen(output_file.data(), "w", stdout);
    std::cout << asm_code;
*/
    Parser p;
    vector<Token*> ans = p.parse("long f(long x, string chlen) {\n}\nchar character;\n int main() {\nlong lol;{int c; char kek;}\n}");
    for (size_t i = 0; i < ans.size(); i++) {
        std::cout << ans[i]->toString();
    }

    return 0;
}
