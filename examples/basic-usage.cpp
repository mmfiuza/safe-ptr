// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#include <iostream>

#define SAFE_PTR_DEBUG 1
#define SAFE_PTR_NAMESPACE foo
#include "SafePtr.hpp"

int main()
{
    foo::SafePtr<int> my_ptr(10);

    for (auto& s : my_ptr) {
        s = 3;
    }

    my_ptr.print_all();

    std::cout << my_ptr[0] << "\n";

    my_ptr.free();
}