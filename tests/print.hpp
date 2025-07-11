// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include "assert.hpp"

void test_print()
{
    std::cout << "\033[34m========== PRINT TEST BEGIN ==========\033[0m\n";

    // empty
    SafePtr<int> ptr0(0);
    ptr0.print_all("print_all: it is empty");
    ptr0.print("print: it is empty");

    // non const
    SafePtr<int> ptr1 = {4,3,2};
    ptr1.print_all();
    ptr1.print_all("name");
    ptr1.print("print");

    // const
    const SafePtr<int> ptr2 = {7,8,9};
    ptr2.print_all();
    ptr2.print_all("something");

    SafePtr<int> ptr4(30);
    int i = 0;
    for (auto& p : ptr4) {
        p = i;
        ++i;
    }
    ptr4.print("ptr4 print()");
    ptr4.print_all("ptr4 print_all()");

    // free memory
    ptr0.free();
    ptr1.free();
    ptr2.free();
    ptr4.free();

    std::cout << "\033[34m========== PRINT TEST END ==========\033[0m\n";
}