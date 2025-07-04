# SafePtr

![Static Badge](https://img.shields.io/badge/C%2B%2B_standard-11_or_above-blue?logo=c%2B%2B)

SafePtr is a C++ container type for memory control and safety. It can store any type you need in a contiguous fixed size heap allocated segment. Below, there is an example of usage.
```c++
#include "SafePtr.hpp"

int main() {
    SafePtr<int> ptr = {0, 2, 3};
    ptr[0] = 1;

    for (auto& p : ptr) {
        std::cout << p << "\n";
    }
    // output: 1 2 3

    ptr.free();
}
```
A SafePtr of any type has only two members variables, a pointer to the first element stored and another to the byte after the last byte of the last element stored. This means that, for any 64 bit machine, `sizeof(SafePtr<T>)` will always return 16 bytes for any type `T`.

As can be seen in the example above, SafePtr requires you to manually call the method `free()` to deallocate memory. However, SafePtr can still be reliable.

## Why is SafePtr called "safe"?

SafePtr has a macro called `SAFE_PTR_DEBUG`. If it is defined, warnings will be printed on the console when:
- memory is leaked;
- data is accessed after been freed.

This is possible by using a thread-safe reference counter of SafePtr instances that point to each heap allocated segment. If this counter goes to `0` and the `free()` method was not called, a memory leak is detected. The reference counting mechanism is similar to the way `std::shared_ptr` works. However when `SAFE_PTR_DEBUG` is not defined, SafePtr has **zero overhead** when compared to using raw pointers, unlike `std::shared_ptr`.

The macro must be defined **BEFORE** SafePtr is included.
```c++
#define SAFE_PTR_DEBUG
#include "SafePtr.hpp"
```

Also, SafePtr throws exceptions when:
- memory out of bounds is tried to be accessed with the `at()` method;
- memory is freed twice;
- allocation fails.

## When SafePtr might be useful

- If contiguous heap allocation is needed in a size that is constant at runtime, but unknown at compile time.
- If you want to have control of memory like manually calling `new` and `delete`, but also want to make sure there will be no segfaults or memory leaks.
- If performance is critical.

## When SafePtr **won't** be useful

- If a container that can grow dynamically is needed, similar to `std::vector`.
- If the data size is known at compile time (just use `std::array` instead).

## Methods

SafePtr has the following methods:
- `free()`: frees the memory pointed by a SafePtr;
- `size()`: returns the number of elements a SafePtr is storing;
- `begin()`: returns a raw pointer to the first stored element;
- `end()`: returns a raw pointer to the byte after the last byte of the last element stored (**not** the last element);
- `operator[idx]`: allows access to read or write data to the element in the `idx` index **without** bounds checking;
- `at(idx)`: allows access to read or write data to the element in the `idx` index **with** bounds checking;
- `empty()`: returns `true` if the number of elements is zero and `false` if not;
- `data()`: returns a raw pointer to the first stored element;
- `front()`: returns a reference to the first element;
- `back()`: returns a reference to the last element;
- `fill(value)`: assigns `value` to all the stored elements;
- `print_all(name)`: prints all the elements if the stored type is printable with `std::cout` (`name` is an optional string).

## Constructor

A SafePtr can be constructed by passing the number of elements or a `std::initializer_list`.
```c++
SafePtr<int> a(5);
std::cout << a.size() << "\n"; // prints 5
a.free();

SafePtr<int> b = {1, 2, 3};
std::cout << a[0] << "," << a[1] << "," << a[2] << "\n"; // prints 1,2,3
b.free();
```

## Copying and moving

A SafePtr can be copied and moved by either constructing a new SafePtr or assigning it to an existing one. However, this operations require attention, because SafePtr will **never** free memory automatically.

### Copy constructor example:
```c++
SafePtr<int> a = {1, 2, 3};
auto b = a;
// "a" and "b" point to different addresses, so both need to be freed
a.free();
b.free();
```

### Move constructor example:
```c++
SafePtr<int> a = {1, 2, 3};
auto b = std::move(a);
// "a" and "b" point to the same address, so only one must be freed
a.free(); // freeing "b" instead also works
```

### Copy assigning example:
```c++
SafePtr<int> a = {1, 2, 3, 4, 5};
SafePtr<int> b = {1, 2, 3};
b.free(); // "b" needs to be freed before it points to the same as "a"
b = a;
// "a" and "b" point to different addresses, so both need to be freed
a.free();
b.free();
```

### Move assigning example:
```c++
SafePtr<int> a = {1, 2, 3, 4, 5};
SafePtr<int> b = {1, 2, 3};
b.free(); // "b" needs to be freed before it points to the same as "a"
b = std::move(a);
// "a" and "b" point to the same address, so only one must be freed
a.free(); // freeing "b" instead also works
```

If any memory leak happens during these kind of operations due to mistakes, warnings will be printed.

## How to install

SafePtr is a header-only library, having only **one** source file: [`include/SafePtr.hpp`](./include/SafePtr.hpp). So, if you want to use it, you just need to have this file anywhere in your machine and them set your compile include path to find it while compiling your code. Below, there is an example using [GCC](https://gcc.gnu.org/).
```
g++ -o my_program -I path/to/SafePtr/dir/include/ my_code.cpp
```

SafePtr is a **lightweight** library, having only the SafePtr class defined. Because of that, the library is **not** defined inside any namespace, since naming conflicts would be extremely unlikely. However, if you want to have SafePtr defined in some namespace, you can use the `SAFE_PTR_NAMESPACE` macro like below.
```c++
#define SAFE_PTR_NAMESPACE foo
#include "SafePtr.hpp"

int main() {
    foo::SafePtr<int> ptr(4);
    ptr.free();
}
```

## How to compile and run the examples

Go to the root directory of the repository and run:
```
rm -rf build && \
cmake -S . -B build && \
cmake --build build && \
./build/basic-usage
```

## How to compile and run the tests

Go to the root directory of the repository and run:
```
rm -rf build && \
cmake -S . -B build && \
cmake --build build && \
./build/test-all
```

<!--
## To do:
- test id overflow
- search for a solution to make initializer_list not copy
- add better examples
- improve cmake
- add find()
- add contains()
- add print()
- add swap
- check if cbegin and cend is needed
-->
