#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <wait.h>

#include "tokens/Token.h"
#include "Preprocessor.h"
#include "parser/Parser.h"
#include "CodeGenerator.h"
#include "lib/Utils.h"
#include "tester/Tester.h"

#include <iostream>

int main(int argc, char *argv[]) {

    Tester tester;
    tester.run_one(argv[1]);

    return 0;
}
