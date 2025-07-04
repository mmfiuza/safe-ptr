// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include "assert.hpp"

void test_methods()
{
    // non const
    SafePtr<int> ptr0(0);
    SafePtr<int> ptr1 = {4,3,2,1};
    ASSERT_EQ(ptr1.size(), 4);
    ASSERT_EQ(ptr1.size(), 4);
    ASSERT_EQ(ptr1[0], 4);
    ASSERT_EQ(ptr1[1], 3);
    ASSERT_EQ(ptr1[2], 2);
    ASSERT_EQ(ptr1[3], 1);
    ASSERT_EQ(ptr1.at(0), 4);
    ASSERT_EQ(ptr1.at(1), 3);
    ASSERT_EQ(ptr1.at(2), 2);
    ASSERT_EQ(ptr1.at(3), 1);
    #ifdef SAFE_PTR_DEBUG
        ASSERT_THROWS(ptr1.at(4));
    #endif
    ASSERT_EQ(ptr1.cbegin(), ptr1.begin());
    ASSERT_EQ(ptr1.cend(), ptr1.end());
    ASSERT_EQ(ptr0.empty(), true);
    ASSERT_EQ(ptr1.empty(), false);
    ASSERT_EQ(ptr1.data(), ptr1.begin());
    ASSERT_EQ(ptr1.front(), ptr1[0]);
    ASSERT_EQ(ptr1.back(), ptr1[3]);
    ASSERT_EQ(ptr1.end(), ptr1.begin() + ptr1.size());
    for (auto& p : ptr1) {
        p = 1;
    }
    ptr1.fill(2);
    ASSERT_EQ(ptr1[0], 2);
    ASSERT_EQ(ptr1[1], 2);
    ASSERT_EQ(ptr1[2], 2);
    ASSERT_EQ(ptr1[3], 2);
    ptr0.free();
    ptr1.free();
    #ifdef SAFE_PTR_DEBUG
        ASSERT_WARNS(ptr1.size());
        ASSERT_WARNS(ptr1[0]);
        ASSERT_WARNS(ptr1.at(0));
        ASSERT_WARNS(ptr1.cbegin());
        ASSERT_WARNS(ptr1.cend());
        ASSERT_WARNS(ptr1.empty());
        ASSERT_WARNS(ptr1.data());
        ASSERT_WARNS(ptr1.front());
        ASSERT_WARNS(ptr1.back());
        ASSERT_WARNS(ptr1.begin());
        ASSERT_WARNS(ptr1.end());
        ASSERT_WARNS(ptr1.fill(0));
    #endif
    
    // const
    const SafePtr<int> ptr2(0);
    const SafePtr<int> ptr3 = {4,3,2,1};
    ASSERT_EQ(ptr3.size(), 4);
    ASSERT_EQ(ptr3.size(), 4);
    ASSERT_EQ(ptr3[0], 4);
    ASSERT_EQ(ptr3[1], 3);
    ASSERT_EQ(ptr3[2], 2);
    ASSERT_EQ(ptr3[3], 1);
    ASSERT_EQ(ptr3.at(0), 4);
    ASSERT_EQ(ptr3.at(1), 3);
    ASSERT_EQ(ptr3.at(2), 2);
    ASSERT_EQ(ptr3.at(3), 1);
    #ifdef SAFE_PTR_DEBUG
        ASSERT_THROWS(ptr3.at(4));
    #endif
    ASSERT_EQ(ptr3.cbegin(), ptr3.begin());
    ASSERT_EQ(ptr3.cend(), ptr3.end());
    ASSERT_EQ(ptr2.empty(), true);
    ASSERT_EQ(ptr3.empty(), false);
    ASSERT_EQ(ptr3.data(), ptr3.begin());
    ASSERT_EQ(ptr3.front(), ptr3[0]);
    ASSERT_EQ(ptr3.back(), ptr3[3]);
    ASSERT_EQ(ptr3.end(), ptr3.begin() + ptr3.size());
    int x;
    for (const auto& p : ptr3) {
        x = p;
    }
    ptr2.free();
    ptr3.free();
    #ifdef SAFE_PTR_DEBUG
        ASSERT_WARNS(ptr2.size());
        ASSERT_WARNS(ptr2[0]);
        ASSERT_WARNS(ptr2.at(0));
        ASSERT_WARNS(ptr3.cbegin());
        ASSERT_WARNS(ptr3.cend());
        ASSERT_WARNS(ptr2.empty());
        ASSERT_WARNS(ptr2.data());
        ASSERT_WARNS(ptr2.front());
        ASSERT_WARNS(ptr2.back());
        ASSERT_WARNS(ptr2.begin());
        ASSERT_WARNS(ptr2.end());
    #endif
}