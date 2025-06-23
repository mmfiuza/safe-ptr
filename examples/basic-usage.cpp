// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#include <iostream>

#define SAFE_PTR_DEBUG 1
#define SAFE_PTR_NAMESPACE foo
#define SAFE_PTR_DISABLE_BOUNDS_CHECKING
#define SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
#include "SafePtr.hpp"

int main()
{
    foo::SafePtr<int> my_ptr(5);

    for (auto& s : my_ptr) {
        s = 3;
    }

    my_ptr.print_all("my_ptr");

    std::cout << my_ptr[3] << "\n";

    my_ptr.free();
}