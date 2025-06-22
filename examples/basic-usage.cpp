#include "SafePtr.hpp"

int main()
{
    SafePtr<int> my_ptr(10);

    for (auto& s : my_ptr) {
        s = 3;
    }

    my_ptr.print_all();

    std::cout << my_ptr[0] << "\n";
}