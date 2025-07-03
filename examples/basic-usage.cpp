// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#include <iostream>

#define SAFE_PTR_DEBUG
#define SAFE_PTR_NAMESPACE foo
#include "SafePtr.hpp"

int main()
{
    foo::SafePtr<int> ptr1(5);
    int i = 0;
    for (auto& s : ptr1) {
        s = i;
        i += 2;
    }
    const foo::SafePtr<float> ptr2 = {1.0, 1.2, 1.5};
    foo::SafePtr<float> ptr3(0);
    foo::SafePtr<int> ptr4(5);
    ptr4.fill(9);
    
    ptr1.print_all();
    ptr2.print_all("second_ptr");
    ptr3.print_all("ptr3");
    ptr4.print_all("ptr4");

    std::cout << "ptr1.begin(): " << ptr1.begin() << "\n";
    std::cout << "ptr2.begin(): " << ptr2.begin() << "\n";
    std::cout << "ptr3.begin(): " << ptr3.begin() << "\n";

    std::cout << "ptr1.end(): " << ptr1.end() << "\n";
    std::cout << "ptr2.end(): " << ptr2.end() << "\n";
    std::cout << "ptr3.end(): " << ptr3.end() << "\n";

    std::cout << "ptr1.data(): " << ptr1.data() << "\n";
    std::cout << "ptr2.data(): " << ptr2.data() << "\n";
    std::cout << "ptr3.data(): " << ptr3.data() << "\n";
    
    std::cout << "ptr1.empty(): " << ptr1.empty() << "\n";
    std::cout << "ptr2.empty(): " << ptr2.empty() << "\n";
    std::cout << "ptr3.empty(): " << ptr3.empty() << "\n";

    std::cout << "ptr1.front(): " << ptr1.front() << "\n";
    std::cout << "ptr2.front(): " << ptr2.front() << "\n";
    std::cout << "ptr3.front(): " << ptr3.front() << "\n";

    std::cout << "ptr1.back(): " << ptr1.back() << "\n";
    std::cout << "ptr2.back(): " << ptr2.back() << "\n";
    std::cout << "ptr3.back(): " << ptr3.back() << "\n";
    
    std::cout << "ptr1[1]: " << ptr1[1] << "\n";
    std::cout << "ptr2[2]: " << ptr2[2] << "\n";

    std::cout << "ptr1.at(1): " << ptr1.at(1) << "\n";
    std::cout << "ptr2.at(2): " << ptr2.at(2) << "\n";
    try { ptr2.at(3); } catch (std::out_of_range e) {
        std::cout << "ptr2.at(3): out of range!\n";
    }
    
    ptr1.free();
    ptr2.free();
    ptr3.free();
    ptr4.free();
}
