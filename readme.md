# `fz::SafePtr`

![Static Badge](https://img.shields.io/badge/C%2B%2B_standard-11_or_above-blue?logo=c%2B%2B)

`fz::SafePtr` is a C++ container type for memory control and safety. It can store any type needed in a contiguous fixed size heap allocated segment. Below, there is an example of usage.
```c++
#include "SafePtr.hpp"

int main() {
    fz::SafePtr<int> ptr = {0, 2, 3};
    ptr[0] = 1;

    for (auto& p : ptr) {
        std::cout << p << "\n";
    }
    // output: 1 2 3

    ptr.free();
}
```
A `fz::SafePtr` of any type has only two members variables, a pointer to the first element stored and another to the byte after the last byte of the last element stored. This means that, for any 64 bit machine, `sizeof(fz::SafePtr<T>)` will always return 16 bytes for any type `T`.

As can be seen in the example above, `fz::SafePtr` requires you to manually call the method `free()` to deallocate memory. However, `fz::SafePtr` remains reliable.

## Why is `fz::SafePtr` called "safe"?

`fz::SafePtr` has a preprocessor macro called `SAFE_PTR_DEBUG`. If it is defined, warnings will be printed at runtime when:
- memory is leaked;
- data is accessed after been freed.

This is possible by using a thread-safe reference counter of `fz::SafePtr` instances that point to each heap allocated segment. If this counter goes to `0` and the `free()` method was not called, a memory leak is detected. The reference counting mechanism is similar to the way `std::shared_ptr` works. However when `SAFE_PTR_DEBUG` is not defined, `fz::SafePtr` has **zero overhead** when compared to using raw pointers, unlike `std::shared_ptr`.

The macro must be defined **BEFORE** `fz::SafePtr` is included.
```c++
#define SAFE_PTR_DEBUG
#include "SafePtr.hpp"
```

Also, `fz::SafePtr` throws exceptions when:
- memory out of bounds is tried to be accessed with the `at()` method;
- memory is freed twice;
- allocation fails.

## When `fz::SafePtr` might be useful:

- if contiguous heap allocation is needed in a size that is constant at runtime, but unknown at compile time;
- if you want to have control of memory like manually calling `new` and `delete`, but also want to make sure there will be no segfaults or memory leaks;
- if performance is critical.

## When `fz::SafePtr` **won't** be useful:

- if a container that can grow dynamically is needed, similar to `std::vector`;
- if the data size is known at compile time (just use `std::array` instead).

## Methods

`fz::SafePtr` has the following methods.
- `free()`: Frees the memory pointed by a `fz::SafePtr`.
- `size()`: Returns the number of elements a `fz::SafePtr` is storing.
- `begin()`: Returns a raw pointer to the first stored element.
- `cbegin()`: The same as `begin`, but returns `const`.
- `end()`: Returns a raw pointer to the byte after the last byte of the last element stored (**not** the last element).
- `cend()`: The same as `end`, but returns `const`.
- `operator[idx]`: Returns a reference to the element with the `idx` index **without** bounds checking.
- `at(idx)`: Returns a reference to the element with the `idx` index **with** bounds checking.
- `empty()`: Returns `true` if the number of elements is zero and `false` if not.
- `data()`: Returns a raw pointer to the first stored element.
- `front()`: Returns a reference to the first element.
- `back()`: Returns a reference to the last element.
- `fill(value)`: Assigns `value` to all the stored elements.
- `print(label)`: Prints the elements. `label` is an optional string. The stored type must be printable with `std::cout`. For large `size`, might not print all elements.
- `print_all(label)`: The same as `print`, but always prints **all** elements.

## Constructor

A `fz::SafePtr` can be constructed by passing the number of elements or a `std::initializer_list`.
```c++
fz::SafePtr<int> a(5);
std::cout << a.size() << "\n"; // prints 5
a.free();

fz::SafePtr<int> b = {1, 2, 3};
std::cout << b[0] << "," << b[1] << "," << b[2] << "\n"; // prints 1 2 3
b.free();
```

## Copying and moving

A `fz::SafePtr` can be copied and moved by either constructing a new `fz::SafePtr` or assigning it to an existing one. However, this operations require attention, because `fz::SafePtr` will **never** free memory automatically.

### Copy constructor example:
```c++
fz::SafePtr<int> a = {1, 2, 3};
auto b = a;
// "a" and "b" point to different addresses, so both need to be freed
a.free();
b.free();
```

### Move constructor example:
```c++
fz::SafePtr<int> a = {1, 2, 3};
auto b = std::move(a);
// "a" and "b" point to the same address, so only one must be freed
a.free(); // freeing "b" instead also works
```

### Copy assigning example:
```c++
fz::SafePtr<int> a = {1, 2, 3, 4, 5};
fz::SafePtr<int> b = {1, 2, 3};
b.free(); // "b" needs to be freed before it points to the same as "a"
b = a;
// "a" and "b" point to different addresses, so both need to be freed
a.free();
b.free();
```

### Move assigning example:
```c++
fz::SafePtr<int> a = {1, 2, 3, 4, 5};
fz::SafePtr<int> b = {1, 2, 3};
b.free(); // "b" needs to be freed before it points to the same as "a"
b = std::move(a);
// "a" and "b" point to the same address, so only one must be freed
a.free(); // freeing "b" instead also works
```

If any memory leak happens during these kind of operations due to mistakes, warnings will be printed.

## How to install

`fz::SafePtr` is a header-only library, having only **one** source file: [`include/SafePtr.hpp`](./include/SafePtr.hpp). So, if you want to use it, you just need to have this file anywhere in your machine and then set your compiler include path to find it while compiling your code. Below, there is an example using [GCC](https://gcc.gnu.org/).
```
g++ -o my_program -I path/to/SafePtr/include/ my_code.cpp
```

## How to compile and run the examples

Go to the root directory of the repository and run:
```
rm -rf build && \
cmake -S . -B build -DBUILD_EXAMPLES=ON && \
cmake --build build && \
./build/basic-usage
```

## How to compile and run the tests

Go to the root directory of the repository and run:
```
rm -rf build && \
cmake -S . -B build -DBUILD_TESTS=ON && \
cmake --build build && \
./build/test-all
```

<!--
## To do:
- change the warning to differentiate when memory was freed twice vs. when it was freed before alocation
- test id overflow
- add recursive print method
- add better examples
- add find()
- add contains()
- add swap
-->
