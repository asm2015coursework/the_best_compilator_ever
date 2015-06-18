#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "lib/Utils.h"

class Preprocessor
{
public:
    Preprocessor();
    Preprocessor(string includeDirectory);
    static string preprocess(string file_name);
    int setIncludeDirectory(string includeDirectory);
private:
    string includeDirectory;
    string deleteComments(string code);
    string applyIncludes(string code);
    bool inBrackets(string code, int position);
};

#endif // PREPROCESSOR_H
