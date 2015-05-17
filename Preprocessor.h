#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "lib/Utils.h"

class Preprocessor
{
public:
    Preprocessor();
    static string preprocess(string file_name);
};

#endif // PREPROCESSOR_H
