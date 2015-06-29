#ifndef TESTER_H
#define TESTER_H

#include <string>

class Tester{
    int test(std::string, bool = true);
    void remove_log();
public:
    int run_all(bool = true);
    int run_tests(int*, bool = true);
    int run_one(std::string, bool = true);
};

#endif // TESTER_H
