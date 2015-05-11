#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <string>

class Preprocessor
{
public:
    Preprocessor();
    static std::string preprocess(std::string file_name);
};

#endif // PREPROCESSOR_H
