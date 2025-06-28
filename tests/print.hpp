// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include "assert.hpp"

void test_print()
{
    std::cout << "========== PRINT TEST BEGIN ==========\n";

    // empty
    SafePtr<int> ptr0(0);
    ptr0.print_all("it is empty");

    // non const
    SafePtr<int> ptr1 = {4,3,2};
    ptr1.print_all();
    ptr1.print_all("name");

    // const
    const SafePtr<int> ptr2 = {7,8,9};
    ptr2.print_all();
    ptr2.print_all("something");

    // free memory
    ptr0.free();
    ptr1.free();
    ptr2.free();

    std::cout << "========== PRINT TEST END ==========\n";
}