#ifndef TESTER_H
#define TESTER_H

#include <string>

class Tester{
    int test(std::string);
    void remove_log();
public:
    int run_all();
    int run_tests(int*, int);
    int run_once(std::string name);
};

#endif // TESTER_H
