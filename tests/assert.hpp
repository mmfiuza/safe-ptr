// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

# pragma once

#define COLOR_RED "\033[31m"
#define COLOR_RESET "\033[0m"

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        std::cerr << COLOR_RED << "FAILED TEST: " << COLOR_RESET << \
            #expr << " (line " << __LINE__ << ")\n"; \
    }
 
#define ASSERT_EQ(a, b) \
    if ((a) != (b)) { \
        std::cerr << COLOR_RED << "FAILED TEST: " << COLOR_RESET << \
            #a << " != " << #b << " (line " << __LINE__ << ")\n" << \
            "    " << (a) << " vs " << (b) << "\n"; \
    }

#define ASSERT_DIFF(a, b) \
    if ((a) == (b)) { \
        std::cerr << COLOR_RED << "FAILED TEST: " << COLOR_RESET << \
            #a << " = " << #b << " (line " << __LINE__ << ")\n" << \
            "    " << (a) << " vs " << (b) << "\n"; \
    }

#define ASSERT_THROWS(expr) \
    try { \
        expr; \
        std::cerr << COLOR_RED << "FAILED TEST: " << COLOR_RESET << \
            "No exception thrown (line " << __LINE__ << ")\n"; \
    } catch (...) {}

#define ASSERT_WARNS(expr) \
    try { \
        expr; \
        std::cerr << COLOR_RED << "FAILED TEST: " << COLOR_RESET << \
            "No warning printed (line " << __LINE__ << ")\n"; \
    } catch (const _SafePtrWarning& e) { \
        /* test passed */ \
    } \
    catch (...) { \
        std::cerr << COLOR_RED << "FAILED TEST: " << COLOR_RESET << \
            "No warning printed (line " << __LINE__ << ")\n"; \
    }
