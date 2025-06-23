// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#include <iostream>

#define SAFE_PTR_DEBUG 1
#define SAFE_PTR_NAMESPACE foo
#define SAFE_PTR_DISABLE_BOUNDS_CHECKING
#define SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
#include "SafePtr.hpp"

int main()
{
    foo::SafePtr<int> ptr1(5);
    int i = 0;
    for (auto& s : ptr1) {
        s = i;
        i += 2;
    }
    ptr1.print_all();
    ptr1.free();

    foo::SafePtr<float> ptr2 = {1.0, 1.2, 1.5, 1.7};
    ptr2.print_all("second_ptr");
    ptr2.free();
}