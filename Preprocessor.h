#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "lib/Utils.h"

class Preprocessor
{
public:
    Preprocessor();
    Preprocessor(string includeDirectory);
    static string preprocess(string file_name);
    static string preprocess(string file_name, string filePath);
    int setIncludeDirectory(string includeDirectory);
private:
    string includeDirectory;
    string deleteComments(string code);
    string applyDefines(string code);
    string applyIncludes(string code, string filePath);
    bool inBrackets(string code, int position);
};

#endif // PREPROCESSOR_H
