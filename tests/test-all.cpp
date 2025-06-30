// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#define SAFE_PTR_DEBUG 1
#include "SafePtr.hpp"
#include "rule-of-5.hpp"
#include "methods.hpp"
#include "ref-count.hpp"
#include "print.hpp"

int main()
{
    test_rule_of_5();
    test_methods();
    test_ref_count();
    // test_print();

    std::cout << "Test finished\n";
}