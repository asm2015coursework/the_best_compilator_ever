#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <vector>

#include "tokens/Token.h"
#include "tokens/InitializationToken.h"
#include "tokens/FunctionToken.h"
#include "tokens/EqualityToken.h"

using std::string;
using std::vector;

class CodeGenerator {
    bool gotError;
    string error;
    string code;
    void makeGlobalVariables();
    void handleCode(const vector<Token*>&);
    void handleToken(Token*);
    void handleInitialization(InitializationToken*);
    void handleFunction(FunctionToken*);
    void handleEquality(EqualityToken*);


    CodeGenerator();

public:
    static string generate(const vector<Token*>&);
};

#endif // CODE_GENERATOR_H
