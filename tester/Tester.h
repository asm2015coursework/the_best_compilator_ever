#ifndef TESTER_H
#define TESTER_H

#include <string>

class Tester{
public:
    int test(std::string);
    int run_all();
    int run_tests(int*, int);
};

#endif // TESTER_H
