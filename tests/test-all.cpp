// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#define SAFE_PTR_DEBUG
#define SAFE_PTR_TEST
#include "SafePtr.hpp"

#include "rule-of-5.hpp"
#include "methods.hpp"
#include "ref-count.hpp"
#include "print.hpp"

#define TEST_PRINT 0

int main()
{
    try {
        test_rule_of_5();
        test_methods();
        test_ref_count();
        #if TEST_PRINT
            test_print();
        #endif
    } catch (const fz::_SafePtrWarning& e) {
        std::cerr << COLOR_RED << "FAILED TEST: " << COLOR_RESET <<
            "An unexpected warning was triggered\n";
    }

    std::cout << "Test finished\n";
}