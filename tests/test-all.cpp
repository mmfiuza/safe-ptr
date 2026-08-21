// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#define SAFE_PTR_DEBUG
#define SAFE_PTR_TEST
#include "SafePtr.hpp"

#include "rule-of-5.hpp"
#include "view.hpp"
#include "methods.hpp"
#include "ref-count.hpp"
#include "print.hpp"

#define TEST_PRINT 0

int main()
{
    try {
        test_rule_of_5();
        test_view();
        test_methods();
        test_ref_count();
        #if TEST_PRINT
            test_print();
        #endif
        std::cout << COLOR_GREEN << "Test passed" << COLOR_RESET << "\n";
    } catch (const fz::_SafePtrWarning& e) {
        std::cerr << COLOR_RED << "TEST FAILED: " << COLOR_RESET <<
            "An unexpected warning was triggered\n";
    } catch (...) {
        std::cerr << COLOR_RED << "TEST FAILED: " << COLOR_RESET <<
            "Unexpected exception thrown\n";
    }
}