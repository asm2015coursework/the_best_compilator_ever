#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "lib/Utils.h"

class Preprocessor
{
public:
    Preprocessor();
    static string preprocess(string file_name);
private:
    string deleteComments(string code);
    string applyIncludes(string code);
    bool inBrackets(string code, int position);
};

#endif // PREPROCESSOR_H
