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
    std::vector<Token*> parsed_code = (new Parser)->parse(code); //don't do like that!!!
    std::string asm_code = CodeGenerator::generate(parsed_code);

    printf("Compiled to %s \n", output_file.data());
    freopen(output_file.data(), "w", stdout);
    std::cout << asm_code;
*/
    Parser p;
    //когда-нибудь Тимур сделает так, что этого не будет, но, видимо, не сегодня
    vector<Token*> ans = p.parse("int f(int x, int y) {return x + y;\n}\nchar character;\n int main() {\nlong lol;{int c; char kek;\nkek = c = olo / hehe + ajgs * priv | a - kek & lol = omg;   x = lil | xoxo & artur & noob | pipka;} +++++a----b; k = 1 + -2 * 3254 / (c = 1); *&*&*&*&*&c; return 0;\n}");

    for (size_t i = 0; i < ans.size(); i++) {
        std::cout << ans[i]->toString() + ";\n";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < ans.size(); i++) {
        std::cout << ans[i]->getType() + ";\n";
    }
    std::cout << std::endl;

    return 0;
}
