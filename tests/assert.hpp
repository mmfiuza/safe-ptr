// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

# pragma once

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        std::cerr << "FAIL: " << #expr << " (line " << __LINE__ << ")\n"; \
    }
 
#define ASSERT_EQ(a, b) \
    if ((a) != (b)) { \
        std::cerr << "FAIL: " << #a << " != " << #b << \
            " (line " << __LINE__ << ")\n"; \
        std::cerr << "  " << (a) << " vs " << (b) << "\n"; \
    }

#define ASSERT_DIFF(a, b) \
    if ((a) == (b)) { \
        std::cerr << "FAIL: " << #a << " = " << #b << \
            " (line " << __LINE__ << ")\n"; \
        std::cerr << "  " << (a) << " vs " << (b) << "\n"; \
    }

#define ASSERT_THROWS(expr) \
    try { \
        expr; \
        std::cerr << "FAIL: No exception thrown (line " << __LINE__ << ")\n"; \
    } catch (...) { \
    }
