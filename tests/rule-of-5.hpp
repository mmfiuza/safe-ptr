// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include "assert.hpp"

void test_rule_of_5()
{
    // regular constructors //
    fz::SafePtr<double> ptr12(0);
    ptr12.free();
    #ifdef SAFE_PTR_DEBUG
        ASSERT_THROWS(ptr12.free());
    #endif
    fz::SafePtr<double> ptr11(6);
    ptr11.free();
    fz::SafePtr<double> ptr3 = {1.0, 1.2, 1.5};
    ptr3.free();
    fz::SafePtr<double> ptr13;
    ptr13 = fz::SafePtr<double>(4);
    ptr13.free();
    
    // copy constructor //
    fz::SafePtr<double> ptr0(0);
    auto ptr7 = ptr0;
    ptr0.free();
    ptr7.free();
    fz::SafePtr<double> ptr4 = {1.5, 7.3, 9.7, 1.4};
    auto ptr8 = ptr4;
    ASSERT_EQ(ptr8[0], ptr4[0]);
    ASSERT_EQ(ptr8[1], ptr4[1]);
    ASSERT_EQ(ptr8[2], ptr4[2]);
    ASSERT_EQ(ptr8[3], ptr4[3]);
    ASSERT_DIFF(ptr8.data(), ptr4.data());
    ASSERT_DIFF(ptr8.begin(), ptr4.begin());
    ASSERT_DIFF(ptr8.end(), ptr4.end());
    ptr4.free();
    ptr8.free();
    
    // move constructor //
    fz::SafePtr<double> ptr10 = {0.3, 4.7, 9.2, 3.4};
    fz::SafePtr<double> ptr9 = std::move(ptr10);
    ASSERT_EQ(ptr9[0], ptr10[0]);
    ASSERT_EQ(ptr9[1], ptr10[1]);
    ASSERT_EQ(ptr9[2], ptr10[2]);
    ASSERT_EQ(ptr9[3], ptr10[3]);
    ASSERT_EQ(ptr9.data(), ptr10.data());
    ASSERT_EQ(ptr9.begin(), ptr10.begin());
    ASSERT_EQ(ptr9.end(), ptr10.end());
    ptr9.free();
    #ifdef SAFE_PTR_DEBUG
        ASSERT_THROWS(ptr10.free());
    #endif
    
    // copy assignment operator
    fz::SafePtr<double> ptr2(5);
    fz::SafePtr<double> ptr6 = {9.9, 1.7, 6.7, 8.4};
    #ifdef SAFE_PTR_DEBUG
        ASSERT_WARNS(ptr2 = ptr6);
    #endif
    ptr2.free();
    ptr2 = ptr6;
    ASSERT_EQ(ptr2[0], ptr6[0]);
    ASSERT_EQ(ptr2[1], ptr6[1]);
    ASSERT_EQ(ptr2[2], ptr6[2]);
    ASSERT_EQ(ptr2[3], ptr6[3]);
    ASSERT_DIFF(ptr2.data(), ptr6.data());
    ASSERT_DIFF(ptr2.begin(), ptr6.begin());
    ASSERT_DIFF(ptr2.end(), ptr6.end());
    ptr2.free();
    ptr6.free();
    
    // move assignment operator
    fz::SafePtr<double> ptr1(5);
    fz::SafePtr<double> ptr5 = {1.4, 1.4, 8.7, 5.3};
    #ifdef SAFE_PTR_DEBUG
        ASSERT_WARNS(ptr1 = std::move(ptr5));
    #endif
    ptr1.free();
    ptr1 = std::move(ptr5);
    ASSERT_EQ(ptr1[0], ptr5[0]);
    ASSERT_EQ(ptr1[1], ptr5[1]);
    ASSERT_EQ(ptr1[2], ptr5[2]);
    ASSERT_EQ(ptr1[3], ptr5[3]);
    ASSERT_EQ(ptr1.data(), ptr5.data());
    ASSERT_EQ(ptr1.begin(), ptr5.begin());
    ASSERT_EQ(ptr1.end(), ptr5.end());
    ptr1.free();
    #ifdef SAFE_PTR_DEBUG
        ASSERT_THROWS(ptr5.free());
    #endif
}
